/* pkcs11-key-deleter.c generated by valac 0.28.0, the Vala compiler
 * generated from pkcs11-key-deleter.vala, do not modify */

/*
 * Seahorse
 *
 * Copyright (C) 2013 Red Hat Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation; either version 2.1 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
 * 02111-1307, USA.
 *
 * Author: Stef Walter <stefw@redhat.com>
 */

#include <glib.h>
#include <glib-object.h>
#include "seahorse-pkcs11.h"
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include "seahorse-common.h"
#include <glib/gi18n-lib.h>
#include <gck/gck.h>


#define SEAHORSE_PKCS11_TYPE_KEY_DELETER (seahorse_pkcs11_key_deleter_get_type ())
#define SEAHORSE_PKCS11_KEY_DELETER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), SEAHORSE_PKCS11_TYPE_KEY_DELETER, SeahorsePkcs11KeyDeleter))
#define SEAHORSE_PKCS11_KEY_DELETER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), SEAHORSE_PKCS11_TYPE_KEY_DELETER, SeahorsePkcs11KeyDeleterClass))
#define SEAHORSE_PKCS11_IS_KEY_DELETER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), SEAHORSE_PKCS11_TYPE_KEY_DELETER))
#define SEAHORSE_PKCS11_IS_KEY_DELETER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), SEAHORSE_PKCS11_TYPE_KEY_DELETER))
#define SEAHORSE_PKCS11_KEY_DELETER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), SEAHORSE_PKCS11_TYPE_KEY_DELETER, SeahorsePkcs11KeyDeleterClass))

typedef struct _SeahorsePkcs11KeyDeleter SeahorsePkcs11KeyDeleter;
typedef struct _SeahorsePkcs11KeyDeleterClass SeahorsePkcs11KeyDeleterClass;
typedef struct _SeahorsePkcs11KeyDeleterPrivate SeahorsePkcs11KeyDeleterPrivate;
#define _g_object_unref0(var) ((var == NULL) ? NULL : (var = (g_object_unref (var), NULL)))
#define _g_free0(var) (var = (g_free (var), NULL))

struct _SeahorsePkcs11KeyDeleter {
	SeahorsePkcs11Deleter parent_instance;
	SeahorsePkcs11KeyDeleterPrivate * priv;
};

struct _SeahorsePkcs11KeyDeleterClass {
	SeahorsePkcs11DeleterClass parent_class;
};

struct _SeahorsePkcs11KeyDeleterPrivate {
	SeahorsePkcs11Certificate* _cert;
	SeahorsePkcs11PrivateKey* _key;
	gchar* _label;
};


static gpointer seahorse_pkcs11_key_deleter_parent_class = NULL;

GType seahorse_pkcs11_key_deleter_get_type (void) G_GNUC_CONST;
#define SEAHORSE_PKCS11_KEY_DELETER_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), SEAHORSE_PKCS11_TYPE_KEY_DELETER, SeahorsePkcs11KeyDeleterPrivate))
enum  {
	SEAHORSE_PKCS11_KEY_DELETER_DUMMY_PROPERTY
};
static GtkDialog* seahorse_pkcs11_key_deleter_real_create_confirm (SeahorseDeleter* base, GtkWindow* parent);
SeahorsePkcs11KeyDeleter* seahorse_pkcs11_key_deleter_new (GckObject* cert_or_key);
SeahorsePkcs11KeyDeleter* seahorse_pkcs11_key_deleter_construct (GType object_type, GckObject* cert_or_key);
static gboolean seahorse_pkcs11_key_deleter_real_add_object (SeahorseDeleter* base, GObject* obj);
static void seahorse_pkcs11_key_deleter_finalize (GObject* obj);


static GtkDialog* seahorse_pkcs11_key_deleter_real_create_confirm (SeahorseDeleter* base, GtkWindow* parent) {
	SeahorsePkcs11KeyDeleter * self;
	GtkDialog* result = NULL;
	SeahorseDeleteDialog* dialog = NULL;
	GtkWindow* _tmp0_ = NULL;
	const gchar* _tmp1_ = NULL;
	const gchar* _tmp2_ = NULL;
	SeahorseDeleteDialog* _tmp3_ = NULL;
	const gchar* _tmp4_ = NULL;
	self = (SeahorsePkcs11KeyDeleter*) base;
	_tmp0_ = parent;
	_tmp1_ = _ ("Are you sure you want to permanently delete %s?");
	_tmp2_ = self->priv->_label;
	_tmp3_ = (SeahorseDeleteDialog*) seahorse_delete_dialog_new (_tmp0_, _tmp1_, _tmp2_, NULL);
	g_object_ref_sink (_tmp3_);
	dialog = _tmp3_;
	_tmp4_ = _ ("I understand that this key will be permanently deleted.");
	seahorse_delete_dialog_set_check_label (dialog, _tmp4_);
	seahorse_delete_dialog_set_check_require (dialog, TRUE);
	result = (GtkDialog*) dialog;
	return result;
}


SeahorsePkcs11KeyDeleter* seahorse_pkcs11_key_deleter_construct (GType object_type, GckObject* cert_or_key) {
	SeahorsePkcs11KeyDeleter * self = NULL;
	GckObject* _tmp0_ = NULL;
	g_return_val_if_fail (cert_or_key != NULL, NULL);
	_tmp0_ = cert_or_key;
	self = (SeahorsePkcs11KeyDeleter*) seahorse_pkcs11_deleter_construct (object_type, _tmp0_);
	return self;
}


SeahorsePkcs11KeyDeleter* seahorse_pkcs11_key_deleter_new (GckObject* cert_or_key) {
	return seahorse_pkcs11_key_deleter_construct (SEAHORSE_PKCS11_TYPE_KEY_DELETER, cert_or_key);
}


static gpointer _g_object_ref0 (gpointer self) {
	return self ? g_object_ref (self) : NULL;
}


static gboolean seahorse_pkcs11_key_deleter_real_add_object (SeahorseDeleter* base, GObject* obj) {
	SeahorsePkcs11KeyDeleter * self;
	gboolean result = FALSE;
	GObject* partner = NULL;
	GObject* _tmp0_ = NULL;
	const gchar* _tmp24_ = NULL;
	self = (SeahorsePkcs11KeyDeleter*) base;
	g_return_val_if_fail (obj != NULL, FALSE);
	_tmp0_ = obj;
	if (G_TYPE_CHECK_INSTANCE_TYPE (_tmp0_, SEAHORSE_PKCS11_TYPE_PRIVATE_KEY)) {
		SeahorsePkcs11PrivateKey* _tmp1_ = NULL;
		SeahorsePkcs11Certificate* _tmp2_ = NULL;
		GObject* _tmp8_ = NULL;
		SeahorsePkcs11PrivateKey* _tmp9_ = NULL;
		SeahorsePkcs11PrivateKey* _tmp10_ = NULL;
		GckObject* _tmp11_ = NULL;
		_tmp1_ = self->priv->_key;
		if (_tmp1_ != NULL) {
			result = FALSE;
			_g_object_unref0 (partner);
			return result;
		}
		_tmp2_ = self->priv->_cert;
		if (_tmp2_ != NULL) {
			SeahorsePkcs11Certificate* _tmp3_ = NULL;
			SeahorsePkcs11PrivateKey* _tmp4_ = NULL;
			SeahorsePkcs11PrivateKey* _tmp5_ = NULL;
			GObject* _tmp6_ = NULL;
			GObject* _tmp7_ = NULL;
			_tmp3_ = self->priv->_cert;
			_tmp4_ = seahorse_pkcs11_certificate_get_partner (_tmp3_);
			_tmp5_ = _tmp4_;
			_g_object_unref0 (partner);
			partner = (GObject*) _tmp5_;
			_tmp6_ = partner;
			_tmp7_ = obj;
			if (_tmp6_ != _tmp7_) {
				result = FALSE;
				_g_object_unref0 (partner);
				return result;
			}
		}
		_tmp8_ = obj;
		_tmp9_ = _g_object_ref0 (G_TYPE_CHECK_INSTANCE_CAST (_tmp8_, SEAHORSE_PKCS11_TYPE_PRIVATE_KEY, SeahorsePkcs11PrivateKey));
		_g_object_unref0 (self->priv->_key);
		self->priv->_key = _tmp9_;
		_tmp10_ = self->priv->_key;
		_tmp11_ = _g_object_ref0 ((GckObject*) _tmp10_);
		((SeahorsePkcs11Deleter*) self)->objects = g_list_prepend (((SeahorsePkcs11Deleter*) self)->objects, _tmp11_);
	} else {
		GObject* _tmp12_ = NULL;
		_tmp12_ = obj;
		if (G_TYPE_CHECK_INSTANCE_TYPE (_tmp12_, SEAHORSE_PKCS11_TYPE_CERTIFICATE)) {
			SeahorsePkcs11Certificate* _tmp13_ = NULL;
			SeahorsePkcs11PrivateKey* _tmp14_ = NULL;
			GObject* _tmp20_ = NULL;
			SeahorsePkcs11Certificate* _tmp21_ = NULL;
			SeahorsePkcs11Certificate* _tmp22_ = NULL;
			GckObject* _tmp23_ = NULL;
			_tmp13_ = self->priv->_cert;
			if (_tmp13_ != NULL) {
				result = FALSE;
				_g_object_unref0 (partner);
				return result;
			}
			_tmp14_ = self->priv->_key;
			if (_tmp14_ != NULL) {
				SeahorsePkcs11PrivateKey* _tmp15_ = NULL;
				SeahorsePkcs11Certificate* _tmp16_ = NULL;
				SeahorsePkcs11Certificate* _tmp17_ = NULL;
				GObject* _tmp18_ = NULL;
				GObject* _tmp19_ = NULL;
				_tmp15_ = self->priv->_key;
				_tmp16_ = seahorse_pkcs11_private_key_get_partner (_tmp15_);
				_tmp17_ = _tmp16_;
				_g_object_unref0 (partner);
				partner = (GObject*) _tmp17_;
				_tmp18_ = partner;
				_tmp19_ = obj;
				if (_tmp18_ != _tmp19_) {
					result = FALSE;
					_g_object_unref0 (partner);
					return result;
				}
			}
			_tmp20_ = obj;
			_tmp21_ = _g_object_ref0 (G_TYPE_CHECK_INSTANCE_CAST (_tmp20_, SEAHORSE_PKCS11_TYPE_CERTIFICATE, SeahorsePkcs11Certificate));
			_g_object_unref0 (self->priv->_cert);
			self->priv->_cert = _tmp21_;
			_tmp22_ = self->priv->_cert;
			_tmp23_ = _g_object_ref0 ((GckObject*) _tmp22_);
			((SeahorsePkcs11Deleter*) self)->objects = g_list_prepend (((SeahorsePkcs11Deleter*) self)->objects, _tmp23_);
		} else {
			result = FALSE;
			_g_object_unref0 (partner);
			return result;
		}
	}
	_tmp24_ = self->priv->_label;
	if (_tmp24_ == NULL) {
		GObject* _tmp25_ = NULL;
		_tmp25_ = obj;
		g_object_get (_tmp25_, "label", &self->priv->_label, NULL);
	}
	result = TRUE;
	_g_object_unref0 (partner);
	return result;
}


static void seahorse_pkcs11_key_deleter_class_init (SeahorsePkcs11KeyDeleterClass * klass) {
	seahorse_pkcs11_key_deleter_parent_class = g_type_class_peek_parent (klass);
	g_type_class_add_private (klass, sizeof (SeahorsePkcs11KeyDeleterPrivate));
	((SeahorseDeleterClass *) klass)->create_confirm = seahorse_pkcs11_key_deleter_real_create_confirm;
	((SeahorseDeleterClass *) klass)->add_object = seahorse_pkcs11_key_deleter_real_add_object;
	G_OBJECT_CLASS (klass)->finalize = seahorse_pkcs11_key_deleter_finalize;
}


static void seahorse_pkcs11_key_deleter_instance_init (SeahorsePkcs11KeyDeleter * self) {
	self->priv = SEAHORSE_PKCS11_KEY_DELETER_GET_PRIVATE (self);
}


static void seahorse_pkcs11_key_deleter_finalize (GObject* obj) {
	SeahorsePkcs11KeyDeleter * self;
	self = G_TYPE_CHECK_INSTANCE_CAST (obj, SEAHORSE_PKCS11_TYPE_KEY_DELETER, SeahorsePkcs11KeyDeleter);
	_g_object_unref0 (self->priv->_cert);
	_g_object_unref0 (self->priv->_key);
	_g_free0 (self->priv->_label);
	G_OBJECT_CLASS (seahorse_pkcs11_key_deleter_parent_class)->finalize (obj);
}


GType seahorse_pkcs11_key_deleter_get_type (void) {
	static volatile gsize seahorse_pkcs11_key_deleter_type_id__volatile = 0;
	if (g_once_init_enter (&seahorse_pkcs11_key_deleter_type_id__volatile)) {
		static const GTypeInfo g_define_type_info = { sizeof (SeahorsePkcs11KeyDeleterClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) seahorse_pkcs11_key_deleter_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (SeahorsePkcs11KeyDeleter), 0, (GInstanceInitFunc) seahorse_pkcs11_key_deleter_instance_init, NULL };
		GType seahorse_pkcs11_key_deleter_type_id;
		seahorse_pkcs11_key_deleter_type_id = g_type_register_static (SEAHORSE_PKCS11_TYPE_DELETER, "SeahorsePkcs11KeyDeleter", &g_define_type_info, 0);
		g_once_init_leave (&seahorse_pkcs11_key_deleter_type_id__volatile, seahorse_pkcs11_key_deleter_type_id);
	}
	return seahorse_pkcs11_key_deleter_type_id__volatile;
}



