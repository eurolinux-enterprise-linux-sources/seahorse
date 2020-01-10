/*
 * Seahorse
 *
 * Copyright (C) 2006 Stefan Walter
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the
 * Free Software Foundation, Inc.,
 * 59 Temple Place, Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#include "config.h"

#include "seahorse-service.h"
#include "seahorse-object.h"
#include "seahorse-gconf.h"
#include "seahorse-util.h"
#include "seahorse-libdialogs.h"

#include "pgp/seahorse-gpgme.h"
#include "pgp/seahorse-gpgme-dialogs.h"
#include "pgp/seahorse-gpgme-key.h"
#include "pgp/seahorse-gpgme-operation.h"

#include <string.h>

#include <glib.h>
#include <glib/gi18n.h>

/* flags from seahorse-service-cyrpto.xml */
#define FLAG_QUIET 0x01

G_DEFINE_TYPE (SeahorseServiceCrypto, seahorse_service_crypto, G_TYPE_OBJECT);

/* Note that we can't use GTK stock here, as we hand these icons off 
   to other processes in the case of notifications */
#define ICON_PREFIX     DATA_DIR "/pixmaps/seahorse/48x48/"

/**
 * SECTION:seahorse-service-crypto
 * @short_description: Seahorse service crypto DBus methods. The other
 * DBus methods can be found in other files
 *
 **/

/* -----------------------------------------------------------------------------
 * PUBLIC METHODS
 */

/**
*
* Creates and returns a new crypto service
* (SEAHORSE_TYPE_SERVICE_CRYPTO)
*/
SeahorseServiceCrypto* 
seahorse_service_crypto_new ()
{
    return g_object_new (SEAHORSE_TYPE_SERVICE_CRYPTO, NULL);
}

/* -----------------------------------------------------------------------------
 * INTERNAL HELPERS 
 */

/* Returns result in result. Frees pop and cryptdata */
/**
* pop: a seahorse operation
* gstarterr: the gpgme error that could have occured earlier
* cryptdata: gpgme cryptdata
* result: the result of the gpgme operation (out)
* error: will be set on error
*
* Finishes the gpgme processing and returns the result
*
* returns: TRUE on successful operation, FALSE else
*/
static gboolean
process_crypto_result (SeahorseGpgmeOperation *pop, gpgme_error_t gstarterr, 
                       gpgme_data_t cryptdata, gchar **result, GError **error)
{
    size_t len;
    char *data;
    
    /* Starting the operation failed? */
    if (!GPG_IS_OK (gstarterr)) {
        gpgme_data_release (cryptdata);
        
        g_set_error (error, SEAHORSE_DBUS_ERROR, SEAHORSE_DBUS_ERROR_CRYPTO,
                     "%s", gpgme_strerror (gstarterr));
        return FALSE;
    }
    
    /* Wait for it to finish (can run main loop stuff) */
    seahorse_operation_wait (SEAHORSE_OPERATION (pop));
    
    if (seahorse_operation_is_cancelled (SEAHORSE_OPERATION (pop))) {
	    
	    g_set_error (error, SEAHORSE_DBUS_CANCELLED, 0, "%s", "");
	    return FALSE;
    
    } else if (seahorse_operation_is_successful (SEAHORSE_OPERATION (pop))) {
        
        data = gpgme_data_release_and_get_mem (cryptdata, &len);
        *result = g_strndup (data, len);
        g_free (data);
        
        return TRUE;
        
    } else {
        
        /* A failed operation always has an error */
        g_assert (seahorse_operation_get_error (SEAHORSE_OPERATION (pop)));
        g_set_error (error, SEAHORSE_DBUS_ERROR, SEAHORSE_DBUS_ERROR_CRYPTO, 
                     "%s", seahorse_operation_get_error (SEAHORSE_OPERATION (pop))->message);
        
        gpgme_data_release (cryptdata);
        return FALSE;
    }
}

/**
* keys: (GList)
*
* Creates a gpgme_key_t array out of the keylist.
*
*/
static gpgme_key_t* 
keylist_to_keys (GList *keys)
{
	gpgme_key_t *recips;
	int i;

	recips = g_new0 (gpgme_key_t, g_list_length (keys) + 1);

	for (i = 0; keys != NULL; keys = g_list_next (keys), i++) {
		g_return_val_if_fail (SEAHORSE_IS_GPGME_KEY (keys->data), recips);
		recips[i] = seahorse_gpgme_key_get_public (keys->data);
		gpgme_key_ref (recips[i]);
	}

	return recips;
}


/**
* keys: gpgme_key_t list of keys
*
* Frees the keys
*
*/
static void
free_keys (gpgme_key_t* keys)
{
	gpgme_key_t* k = keys;
	if (!keys)
		return;
	while (*k)
		gpgme_key_unref (*(k++));
	g_free (keys);
}

/**
* data: optional, will be added to the title, can be NULL
* status: the gpgme status
*
* Basing on the status a notification is created an displayed
*
*/
static void
notify_signatures (const gchar* data, gpgme_verify_result_t status)
{
	const gchar *icon = NULL;
	SeahorseObject *object;
	gchar *title, *body;
	gboolean sig = FALSE;
	GSList *rawids;
	GList *keys;

	/* Discover the key in question */
	rawids = g_slist_append (NULL, status->signatures->fpr);
	keys = seahorse_context_discover_objects (SCTX_APP (), SEAHORSE_PGP, rawids);
	g_slist_free (rawids);

	g_return_if_fail (keys != NULL);
	object = SEAHORSE_OBJECT (keys->data);
	g_list_free (keys);

	/* Figure out what to display */
	switch (gpgme_err_code (status->signatures->status)) {
	case GPG_ERR_KEY_EXPIRED:
		/* TRANSLATORS: <key id='xxx'> is a custom markup tag, do not translate. */
		body = _("Signed by <i><key id='%s'/> <b>expired</b></i> on %s.");
		title = _("Invalid Signature");
		icon = ICON_PREFIX "seahorse-sign-bad.png";
		sig = TRUE;
		break;
		/* TRANSLATORS: <key id='xxx'> is a custom markup tag, do not translate. */
	case GPG_ERR_SIG_EXPIRED:
		body  = _("Signed by <i><key id='%s'/></i> on %s <b>Expired</b>.");
		title = _("Expired Signature");
		icon = ICON_PREFIX "seahorse-sign-bad.png";
		sig = TRUE;
		break;
		/* TRANSLATORS: <key id='xxx'> is a custom markup tag, do not translate. */
	case GPG_ERR_CERT_REVOKED:
		body = _("Signed by <i><key id='%s'/> <b>Revoked</b></i> on %s.");
		title = _("Revoked Signature");
		icon = ICON_PREFIX "seahorse-sign-bad.png";
		sig = TRUE;
		break;
	case GPG_ERR_NO_ERROR:
		/* TRANSLATORS: <key id='xxx'> is a custom markup tag, do not translate. */
		body = _("Signed by <i><key id='%s'/></i> on %s.");
		title = _("Good Signature");
		icon = ICON_PREFIX "seahorse-sign-ok.png";
		sig = TRUE;
		break;
	case GPG_ERR_NO_PUBKEY:
		body = _("Signing key not in keyring.");
		title = _("Unknown Signature");
		icon = ICON_PREFIX "seahorse-sign-unknown.png";
		break;
	case GPG_ERR_BAD_SIGNATURE:
		body = _("Bad or forged signature. The signed data was modified.");
		title = _("Bad Signature");
		icon = ICON_PREFIX "seahorse-sign-bad.png";
		break;
	case GPG_ERR_NO_DATA:
		return;
	default:
		if (!GPG_IS_OK (status->signatures->status))
			seahorse_gpgme_handle_error (status->signatures->status, 
			                             _("Couldn't verify signature."));
		return;
	};

	if (sig) {
		gchar *date = seahorse_util_get_display_date_string (status->signatures->timestamp);
		gchar *id = seahorse_context_id_to_dbus (SCTX_APP (), seahorse_object_get_id (object));
		body = g_markup_printf_escaped (body, id, date);
		g_free (date);
		g_free (id);
	} else {
		body = g_strdup (body);
	}

	if (data) {
		data = seahorse_util_uri_get_last (data);
		title = g_strdup_printf ("%s: %s", data, title);
	} else {
		title = g_strdup (title);
	}

	seahorse_notification_display (title, body, !sig, icon, NULL);

	g_free(title);
	g_free(body);
}    

/* -----------------------------------------------------------------------------
 * DBUS METHODS 
 */

/**
 * seahorse_service_crypto_encrypt_text:
 * @crypto: the crypto service (#SeahorseServiceCrypto)
 * @recipients: A list of recipients (keyids "openpgp:B8098FB063E2C811")
 * @signer: optional
 * @flags: 0, not used
 * @cleartext: the text to encrypt
 * @crypttext: the decrypted text (out)
 * @error: an error (out)
 *
 * DBus: EncryptText
 *
 *
 * Returns: TRUE on success
 */
gboolean
seahorse_service_crypto_encrypt_text (SeahorseServiceCrypto *crypto, 
                                      const char **recipients, const char *signer, 
                                      int flags, const char *cleartext, 
                                      char **crypttext, GError **error)
{
    GList *recipkeys = NULL;
    SeahorseGpgmeOperation *pop; 
    SeahorseObject *signkey = NULL;
    SeahorseObject *skey;
    gpgme_key_t *recips;
    gpgme_data_t plain, cipher;
    gpgme_error_t gerr;
    gboolean ret = TRUE;
    
    /* 
     * TODO: Once we support different kinds of keys that support encryption
     * then all this logic will need to change. 
     */
    
    /* The signer */
    if (signer && signer[0]) {
        signkey = seahorse_context_object_from_dbus (SCTX_APP (), signer);
        if (!signkey) {
            g_set_error (error, SEAHORSE_DBUS_ERROR, SEAHORSE_DBUS_ERROR_INVALID, 
                         _("Invalid or unrecognized signer: %s"), signer);
            return FALSE;
        }
        
        if (!SEAHORSE_IS_GPGME_KEY (signkey) || 
            !(seahorse_object_get_flags (signkey) & SEAHORSE_FLAG_CAN_SIGN)) {
            g_set_error (error, SEAHORSE_DBUS_ERROR, SEAHORSE_DBUS_ERROR_INVALID,
                         _("Key is not valid for signing: %s"), signer);
            return FALSE;
        }
    }
    
    /* The recipients */
    for( ; recipients[0]; recipients++)
    {
        skey = seahorse_context_object_from_dbus (SCTX_APP (), recipients[0]);
        if (!skey) {
            g_list_free (recipkeys);
            g_set_error (error, SEAHORSE_DBUS_ERROR, SEAHORSE_DBUS_ERROR_INVALID, 
                         _("Invalid or unrecognized recipient: %s"), recipients[0]);
            return FALSE;
        }
        
        if (!SEAHORSE_IS_GPGME_KEY (skey) ||
            !(seahorse_object_get_flags (skey) & SEAHORSE_FLAG_CAN_ENCRYPT)) {
            g_list_free (recipkeys);
            g_set_error (error, SEAHORSE_DBUS_ERROR, SEAHORSE_DBUS_ERROR_INVALID,
                         _("Key is not a valid recipient for encryption: %s"), recipients[0]);
            return FALSE;
        }
        
        recipkeys = g_list_prepend (recipkeys, SEAHORSE_PGP_KEY (skey));
    }
    
    if (!recipkeys) {
        g_set_error (error, SEAHORSE_DBUS_ERROR, SEAHORSE_DBUS_ERROR_INVALID,
                     _("No recipients specified"));
        return FALSE;
    }
    
    pop = seahorse_gpgme_operation_new (NULL);
    
    /* new data form text */
    gerr = gpgme_data_new_from_mem (&plain, cleartext, strlen (cleartext), FALSE);
    g_return_val_if_fail (GPG_IS_OK (gerr), FALSE);
    gerr = gpgme_data_new (&cipher);
    g_return_val_if_fail (GPG_IS_OK (gerr), FALSE);
   
    /* encrypt with armor */
    gpgme_set_textmode (pop->gctx, TRUE);
    gpgme_set_armor (pop->gctx, TRUE);

    /* Add the default key if set and necessary */
    if (seahorse_gconf_get_boolean (ENCRYPTSELF_KEY)) {
        skey = SEAHORSE_OBJECT (seahorse_context_get_default_key (SCTX_APP ()));
        if (SEAHORSE_IS_PGP_KEY (skey))
            recipkeys = g_list_append (recipkeys, skey);
    }

    /* Make keys into the right format for GPGME */
    recips = keylist_to_keys (recipkeys);
    g_list_free (recipkeys);
    
    /* Do the encryption */
    if (signkey) {
        gpgme_signers_add (pop->gctx, seahorse_gpgme_key_get_private (SEAHORSE_GPGME_KEY (signkey)));
        gerr = gpgme_op_encrypt_sign_start (pop->gctx, recips, GPGME_ENCRYPT_ALWAYS_TRUST, 
                                            plain, cipher);
    } else {
        gerr = gpgme_op_encrypt_start (pop->gctx, recips, GPGME_ENCRYPT_ALWAYS_TRUST, 
                                       plain, cipher);
    }
    
    free_keys (recips);

    /* Frees cipher */
    ret = process_crypto_result (pop, gerr, cipher, crypttext, error);
    
    g_object_unref (pop);
    gpgme_data_release (plain);
    return ret;
}

/**
 * seahorse_service_crypto_sign_text:
 * @crypto: SeahorseServiceCrypto
 * @signer: the signer keyid
 * @flags: 0 (ignored)
 * @cleartext: the text to sign
 * @crypttext: the clear text signature (out) (GPGME_SIG_MODE_CLEAR)
 * @error: an error to return
 *
 * DBus: SignText
 *
 * Signs the @cleartext and returns the signature in @crypttext
 *
 * Returns: TRUE on success
 */
gboolean
seahorse_service_crypto_sign_text (SeahorseServiceCrypto *crypto, const char *signer, 
                                   int flags, const char *cleartext, char **crypttext,
                                   GError **error)
{
    SeahorseObject *signkey = NULL;
    gpgme_error_t gerr;
    SeahorseGpgmeOperation *pop; 
    gpgme_data_t plain, cipher;
    gboolean ret = TRUE;
    
    /* 
     * TODO: Once we support different kinds of keys that support encryption
     * then all this logic will need to change. 
     */
    
    /* The signer */
    if (!signer || !signer[0]) 
        g_set_error (error, SEAHORSE_DBUS_ERROR, SEAHORSE_DBUS_ERROR_INVALID,
                     _("No signer specified"));
    
    signkey = seahorse_context_object_from_dbus (SCTX_APP (), signer);
    if (!signkey) {
        g_set_error (error, SEAHORSE_DBUS_ERROR, SEAHORSE_DBUS_ERROR_INVALID, 
                     _("Invalid or unrecognized signer: %s"), signer);
        return FALSE;
    }
        
    if (!SEAHORSE_IS_GPGME_KEY (signkey) || 
        !(seahorse_object_get_flags (signkey) & SEAHORSE_FLAG_CAN_SIGN)) {
        g_set_error (error, SEAHORSE_DBUS_ERROR, SEAHORSE_DBUS_ERROR_INVALID,
                     _("Key is not valid for signing: %s"), signer);
        return FALSE;
    }
    
    pop = seahorse_gpgme_operation_new (NULL);
    
    /* new data from text */
    gerr = gpgme_data_new_from_mem (&plain, cleartext, strlen (cleartext), FALSE);
    g_return_val_if_fail (GPG_IS_OK (gerr), FALSE);
    gerr = gpgme_data_new (&cipher);
    g_return_val_if_fail (GPG_IS_OK (gerr), FALSE);
   
    /* encrypt with armor */
    gpgme_set_textmode (pop->gctx, TRUE);
    gpgme_set_armor (pop->gctx, TRUE);

    /* Do the signage */
    gpgme_signers_add (pop->gctx, seahorse_gpgme_key_get_private (SEAHORSE_GPGME_KEY (signkey)));
    gerr = gpgme_op_sign_start (pop->gctx, plain, cipher, GPGME_SIG_MODE_CLEAR);

    /* Frees cipher */
    ret = process_crypto_result (pop, gerr, cipher, crypttext, error);
    
    g_object_unref (pop);
    gpgme_data_release (plain);
    return ret;
}

/**
 * seahorse_service_crypto_decrypt_text:
 * @crypto: #SeahorseServiceCrypto context
 * @ktype: "openpgp"
 * @flags: FLAG_QUIET for no notification
 * @crypttext: the text to decrypt
 * @cleartext: the decrypted text (out)
 * @signer: the signer if the text is signed (out)
 * @error: a potential error (out)
 *
 * DBus: DecryptText
 *
 * Decrypts the @crypttext and returns it in @cleartext. If the text
 * was signed, the signed is returned.
 *
 * Returns: TRUE on success
 */
gboolean
seahorse_service_crypto_decrypt_text (SeahorseServiceCrypto *crypto, 
                                      const char *ktype, int flags, 
                                      const char *crypttext, char **cleartext,
                                      char **signer, GError **error)
{
    gpgme_verify_result_t status;
    gpgme_error_t gerr;
    SeahorseGpgmeOperation *pop; 
    gpgme_data_t plain, cipher;
    gboolean ret = TRUE;
    GQuark keyid;
    
    if (!g_str_equal (ktype, g_quark_to_string (SEAHORSE_PGP))) {
        g_set_error (error, SEAHORSE_DBUS_ERROR, SEAHORSE_DBUS_ERROR_INVALID,
                     _("Invalid key type for decryption: %s"), ktype);
        return FALSE;        
    }
    
    /* 
     * TODO: Once we support different kinds of keys that support encryption
     * then all this logic will need to change. 
     */
    
    pop = seahorse_gpgme_operation_new (NULL);
    
    /* new data from text */
    gerr = gpgme_data_new_from_mem (&cipher, crypttext, strlen (crypttext), FALSE);
    g_return_val_if_fail (GPG_IS_OK (gerr), FALSE);
    gerr = gpgme_data_new (&plain);
    g_return_val_if_fail (GPG_IS_OK (gerr), FALSE);
   
    /* encrypt with armor */
    gpgme_set_textmode (pop->gctx, TRUE);
    gpgme_set_armor (pop->gctx, TRUE);

    /* Do the decryption */
    gerr = gpgme_op_decrypt_verify_start (pop->gctx, cipher, plain);

    /* Frees plain */
    ret = process_crypto_result (pop, gerr, plain, cleartext, error);
    
    if (ret) {
        *signer = NULL;
        status = gpgme_op_verify_result (pop->gctx);
    
        if (status->signatures) {
            if (!(flags & FLAG_QUIET))
                notify_signatures (NULL, status);
            if (status->signatures->summary & GPGME_SIGSUM_GREEN ||
                status->signatures->summary & GPGME_SIGSUM_VALID ||
                status->signatures->summary & GPGME_SIGSUM_KEY_MISSING) {
                keyid = seahorse_pgp_key_canonize_id (status->signatures->fpr);
                *signer = seahorse_context_id_to_dbus (SCTX_APP (), keyid);
            }
        }
    }

    g_object_unref (pop);
    gpgme_data_release (cipher);
    return ret;
}

/**
 * seahorse_service_crypto_verify_text:
 * @crypto: #SeahorseServiceCrypto context
 * @ktype: "openpgp"
 * @flags: FLAG_QUIET for no notification
 * @crypttext: the text to decrypt
 * @cleartext: the plaintext after verification (out)
 * @signer: the signer if the text is signed (out)
 * @error: a potential error (out)
 *
 * DBus: VerifyText
 *
 * Decrypts the @crypttext and returns it in @cleartext. If the text
 * was signed, the signed is returned.
 *
 * Returns: TRUE on success
 */
gboolean
seahorse_service_crypto_verify_text (SeahorseServiceCrypto *crypto, 
                                     const gchar *ktype, int flags, 
                                     const gchar *crypttext, gchar **cleartext,
                                     char **signer, GError **error)
{
    gpgme_verify_result_t status;
    gpgme_error_t gerr;
    SeahorseGpgmeOperation *pop; 
    gpgme_data_t plain, cipher;
    gboolean ret = TRUE;
    GQuark keyid;
    
    if (!g_str_equal (ktype, g_quark_to_string (SEAHORSE_PGP))) {
        g_set_error (error, SEAHORSE_DBUS_ERROR, SEAHORSE_DBUS_ERROR_INVALID,
                     _("Invalid key type for verifying: %s"), ktype);
        return FALSE;        
    }

    /* 
     * TODO: Once we support different kinds of keys that support encryption
     * then all this logic will need to change. 
     */

    pop = seahorse_gpgme_operation_new (NULL);
    
    /* new data from text */
    gerr = gpgme_data_new_from_mem (&cipher, crypttext, strlen (crypttext), FALSE);
    g_return_val_if_fail (GPG_IS_OK (gerr), FALSE);
    gerr = gpgme_data_new (&plain);
    g_return_val_if_fail (GPG_IS_OK (gerr), FALSE);
   
    /* encrypt with armor */
    gpgme_set_textmode (pop->gctx, TRUE);
    gpgme_set_armor (pop->gctx, TRUE);

    /* Do the decryption */
    gerr = gpgme_op_verify_start (pop->gctx, cipher, NULL, plain);

    /* Frees plain */
    ret = process_crypto_result (pop, gerr, plain, cleartext, error);
    
    if (ret) {
        *signer = NULL;
        status = gpgme_op_verify_result (pop->gctx);
    
        if (status->signatures) {
            if (!(flags & FLAG_QUIET))
                notify_signatures (NULL, status);
            if (status->signatures->summary & GPGME_SIGSUM_GREEN ||
                status->signatures->summary & GPGME_SIGSUM_VALID ||
                status->signatures->summary & GPGME_SIGSUM_KEY_MISSING) {
                keyid = seahorse_pgp_key_canonize_id (status->signatures->fpr);
                *signer = seahorse_context_id_to_dbus (SCTX_APP (), keyid);
            }
        }
    }
    
    g_object_unref (pop);
    gpgme_data_release (cipher);
    return TRUE;
}

/* -----------------------------------------------------------------------------
 * OBJECT 
 */

static void
seahorse_service_crypto_init (SeahorseServiceCrypto *crypto)
{

}

static void
seahorse_service_crypto_class_init (SeahorseServiceCryptoClass *klass)
{
    /* GObjectClass *gclass = G_OBJECT_CLASS (klass); */
    seahorse_service_crypto_parent_class = g_type_class_peek_parent (klass);
}

