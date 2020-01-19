/* pkcs11-request.c generated by valac 0.28.0, the Vala compiler
 * generated from pkcs11-request.vala, do not modify */

/*
 * Seahorse
 *
 * Copyright (C) 2008 Stefan Walter
 * Copyright (C) 2011 Collabora Ltd.
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
 * Stef Walter <stefw@redhat.com>
 */

#include <glib.h>
#include <glib-object.h>
#include "seahorse-pkcs11.h"
#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include <gck/gck.h>
#include <gcr/gcr-base.h>
#include "libseahorse/seahorse-interaction.h"
#include <gio/gio.h>
#include "seahorse-common.h"
#include <glib/gi18n-lib.h>

#define _g_object_unref0(var) ((var == NULL) ? NULL : (var = (g_object_unref (var), NULL)))
typedef struct _Block3Data Block3Data;
#define _g_error_free0(var) ((var == NULL) ? NULL : (var = (g_error_free (var), NULL)))
#define _g_free0(var) (var = (g_free (var), NULL))
typedef struct _Block4Data Block4Data;
typedef struct _Block5Data Block5Data;

struct _SeahorsePkcs11RequestPrivate {
	SeahorsePkcs11PrivateKey* _private_key;
	GtkEntry* _name_entry;
	guint8* _encoded;
	gint _encoded_length1;
	gint __encoded_size_;
};

struct _Block3Data {
	int _ref_count_;
	SeahorsePkcs11Request* self;
	GcrCertificateRequest* req;
};

struct _Block4Data {
	int _ref_count_;
	SeahorsePkcs11Request* self;
	GtkWindow* parent;
};

struct _Block5Data {
	int _ref_count_;
	Block4Data * _data4_;
	GFile* file;
};


static gpointer seahorse_pkcs11_request_parent_class = NULL;
static gchar* seahorse_pkcs11_request_BAD_FILENAME_CHARS;
static gchar* seahorse_pkcs11_request_BAD_FILENAME_CHARS = NULL;

#define SEAHORSE_PKCS11_REQUEST_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), SEAHORSE_PKCS11_TYPE_REQUEST, SeahorsePkcs11RequestPrivate))
enum  {
	SEAHORSE_PKCS11_REQUEST_DUMMY_PROPERTY,
	SEAHORSE_PKCS11_REQUEST_PRIVATE_KEY
};
static void seahorse_pkcs11_request_real_response (GtkDialog* base, gint response_id);
static Block3Data* block3_data_ref (Block3Data* _data3_);
static void block3_data_unref (void * _userdata_);
static void ___lambda5_ (Block3Data* _data3_, GObject* obj, GAsyncResult* res);
static void seahorse_pkcs11_request_save_certificate_request (SeahorsePkcs11Request* self, GcrCertificateRequest* req, GtkWindow* parent);
static void ____lambda5__gasync_ready_callback (GObject* source_object, GAsyncResult* res, gpointer self);
static void seahorse_pkcs11_request_update_response (SeahorsePkcs11Request* self);
static Block4Data* block4_data_ref (Block4Data* _data4_);
static void block4_data_unref (void * _userdata_);
static Block5Data* block5_data_ref (Block5Data* _data5_);
static void block5_data_unref (void * _userdata_);
static void ___lambda6_ (Block5Data* _data5_, GObject* obj, GAsyncResult* res);
static void ____lambda6__gasync_ready_callback (GObject* source_object, GAsyncResult* res, gpointer self);
static GObject * seahorse_pkcs11_request_constructor (GType type, guint n_construct_properties, GObjectConstructParam * construct_properties);
static void _seahorse_pkcs11_request___lambda7_ (SeahorsePkcs11Request* self);
static void __seahorse_pkcs11_request___lambda7__gtk_editable_changed (GtkEditable* _sender, gpointer self);
static void seahorse_pkcs11_request_finalize (GObject* obj);
static void _vala_seahorse_pkcs11_request_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec);
static void _vala_seahorse_pkcs11_request_set_property (GObject * object, guint property_id, const GValue * value, GParamSpec * pspec);


void seahorse_pkcs11_request_prompt (GtkWindow* parent, GckObject* private_key) {
	SeahorsePkcs11Request* dialog = NULL;
	GtkWindow* _tmp0_ = NULL;
	GckObject* _tmp1_ = NULL;
	GObject* _tmp2_ = NULL;
	GObject* _tmp3_ = NULL;
	g_return_if_fail (private_key != NULL);
	_tmp0_ = parent;
	_tmp1_ = private_key;
	_tmp2_ = g_object_new (SEAHORSE_PKCS11_TYPE_REQUEST, "transient-for", _tmp0_, "private-key", _tmp1_, NULL);
	_tmp3_ = G_IS_INITIALLY_UNOWNED (_tmp2_) ? g_object_ref_sink (_tmp2_) : _tmp2_;
	dialog = G_TYPE_CHECK_INSTANCE_CAST (_tmp3_, SEAHORSE_PKCS11_TYPE_REQUEST, SeahorsePkcs11Request);
	gtk_dialog_run ((GtkDialog*) dialog);
	_g_object_unref0 (dialog);
}


static Block3Data* block3_data_ref (Block3Data* _data3_) {
	g_atomic_int_inc (&_data3_->_ref_count_);
	return _data3_;
}


static void block3_data_unref (void * _userdata_) {
	Block3Data* _data3_;
	_data3_ = (Block3Data*) _userdata_;
	if (g_atomic_int_dec_and_test (&_data3_->_ref_count_)) {
		SeahorsePkcs11Request* self;
		self = _data3_->self;
		_g_object_unref0 (_data3_->req);
		_g_object_unref0 (self);
		g_slice_free (Block3Data, _data3_);
	}
}


static void ___lambda5_ (Block3Data* _data3_, GObject* obj, GAsyncResult* res) {
	SeahorsePkcs11Request* self;
	GError * _inner_error_ = NULL;
	self = _data3_->self;
	g_return_if_fail (res != NULL);
	{
		GcrCertificateRequest* _tmp0_ = NULL;
		GAsyncResult* _tmp1_ = NULL;
		GcrCertificateRequest* _tmp2_ = NULL;
		GtkWindow* _tmp3_ = NULL;
		GtkWindow* _tmp4_ = NULL;
		_tmp0_ = _data3_->req;
		_tmp1_ = res;
		gcr_certificate_request_complete_finish (_tmp0_, _tmp1_, &_inner_error_);
		if (G_UNLIKELY (_inner_error_ != NULL)) {
			goto __catch5_g_error;
		}
		_tmp2_ = _data3_->req;
		_tmp3_ = gtk_window_get_transient_for ((GtkWindow*) self);
		_tmp4_ = _tmp3_;
		seahorse_pkcs11_request_save_certificate_request (self, _tmp2_, _tmp4_);
	}
	goto __finally5;
	__catch5_g_error:
	{
		GError* err = NULL;
		GtkWindow* _tmp5_ = NULL;
		GtkWindow* _tmp6_ = NULL;
		const gchar* _tmp7_ = NULL;
		GError* _tmp8_ = NULL;
		const gchar* _tmp9_ = NULL;
		err = _inner_error_;
		_inner_error_ = NULL;
		_tmp5_ = gtk_window_get_transient_for ((GtkWindow*) self);
		_tmp6_ = _tmp5_;
		_tmp7_ = _ ("Couldn't create certificate request");
		_tmp8_ = err;
		_tmp9_ = _tmp8_->message;
		seahorse_util_show_error ((GtkWidget*) _tmp6_, _tmp7_, _tmp9_);
		_g_error_free0 (err);
	}
	__finally5:
	if (G_UNLIKELY (_inner_error_ != NULL)) {
		g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
		g_clear_error (&_inner_error_);
		return;
	}
}


static void ____lambda5__gasync_ready_callback (GObject* source_object, GAsyncResult* res, gpointer self) {
	___lambda5_ (self, source_object, res);
	block3_data_unref (self);
}


static void seahorse_pkcs11_request_real_response (GtkDialog* base, gint response_id) {
	SeahorsePkcs11Request * self;
	gint _tmp0_ = 0;
	self = (SeahorsePkcs11Request*) base;
	_tmp0_ = response_id;
	if (_tmp0_ == ((gint) GTK_RESPONSE_OK)) {
		Block3Data* _data3_;
		SeahorseInteraction* interaction = NULL;
		GtkWindow* _tmp1_ = NULL;
		GtkWindow* _tmp2_ = NULL;
		SeahorseInteraction* _tmp3_ = NULL;
		GckSession* session = NULL;
		SeahorsePkcs11PrivateKey* _tmp4_ = NULL;
		GckSession* _tmp5_ = NULL;
		GckSession* _tmp6_ = NULL;
		SeahorseInteraction* _tmp7_ = NULL;
		SeahorsePkcs11PrivateKey* _tmp8_ = NULL;
		GcrCertificateRequest* _tmp9_ = NULL;
		GcrCertificateRequest* _tmp10_ = NULL;
		GtkEntry* _tmp11_ = NULL;
		const gchar* _tmp12_ = NULL;
		GcrCertificateRequest* _tmp13_ = NULL;
		_data3_ = g_slice_new0 (Block3Data);
		_data3_->_ref_count_ = 1;
		_data3_->self = g_object_ref (self);
		_tmp1_ = gtk_window_get_transient_for ((GtkWindow*) self);
		_tmp2_ = _tmp1_;
		_tmp3_ = seahorse_interaction_new (_tmp2_);
		interaction = _tmp3_;
		_tmp4_ = self->priv->_private_key;
		_tmp5_ = gck_object_get_session ((GckObject*) _tmp4_);
		session = _tmp5_;
		_tmp6_ = session;
		_tmp7_ = interaction;
		gck_session_set_interaction (_tmp6_, (GTlsInteraction*) _tmp7_);
		_tmp8_ = self->priv->_private_key;
		_tmp9_ = gcr_certificate_request_prepare (GCR_CERTIFICATE_REQUEST_PKCS10, (GckObject*) _tmp8_);
		_data3_->req = _tmp9_;
		_tmp10_ = _data3_->req;
		_tmp11_ = self->priv->_name_entry;
		_tmp12_ = gtk_entry_get_text (_tmp11_);
		gcr_certificate_request_set_cn (_tmp10_, _tmp12_);
		_tmp13_ = _data3_->req;
		gcr_certificate_request_complete_async (_tmp13_, NULL, ____lambda5__gasync_ready_callback, block3_data_ref (_data3_));
		gtk_widget_hide ((GtkWidget*) self);
		_g_object_unref0 (session);
		_g_object_unref0 (interaction);
		block3_data_unref (_data3_);
		_data3_ = NULL;
	}
}


static void seahorse_pkcs11_request_update_response (SeahorsePkcs11Request* self) {
	gchar* name = NULL;
	GtkEntry* _tmp0_ = NULL;
	const gchar* _tmp1_ = NULL;
	gchar* _tmp2_ = NULL;
	g_return_if_fail (self != NULL);
	_tmp0_ = self->priv->_name_entry;
	_tmp1_ = gtk_entry_get_text (_tmp0_);
	_tmp2_ = g_strdup (_tmp1_);
	name = _tmp2_;
	gtk_dialog_set_response_sensitive ((GtkDialog*) self, (gint) GTK_RESPONSE_OK, g_strcmp0 (name, "") != 0);
	_g_free0 (name);
}


static gpointer _g_object_ref0 (gpointer self) {
	return self ? g_object_ref (self) : NULL;
}


static Block4Data* block4_data_ref (Block4Data* _data4_) {
	g_atomic_int_inc (&_data4_->_ref_count_);
	return _data4_;
}


static void block4_data_unref (void * _userdata_) {
	Block4Data* _data4_;
	_data4_ = (Block4Data*) _userdata_;
	if (g_atomic_int_dec_and_test (&_data4_->_ref_count_)) {
		SeahorsePkcs11Request* self;
		self = _data4_->self;
		_g_object_unref0 (_data4_->parent);
		_g_object_unref0 (self);
		g_slice_free (Block4Data, _data4_);
	}
}


static gchar* string_delimit (const gchar* self, const gchar* delimiters, gchar new_delimiter) {
	gchar* result = NULL;
	gchar* _result_ = NULL;
	gchar* _tmp0_ = NULL;
	const gchar* _tmp1_ = NULL;
	const gchar* _tmp2_ = NULL;
	gchar _tmp3_ = '\0';
	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (delimiters != NULL, NULL);
	_tmp0_ = g_strdup (self);
	_result_ = _tmp0_;
	_tmp1_ = _result_;
	_tmp2_ = delimiters;
	_tmp3_ = new_delimiter;
	g_strdelimit (_tmp1_, _tmp2_, _tmp3_);
	result = _result_;
	return result;
}


static Block5Data* block5_data_ref (Block5Data* _data5_) {
	g_atomic_int_inc (&_data5_->_ref_count_);
	return _data5_;
}


static void block5_data_unref (void * _userdata_) {
	Block5Data* _data5_;
	_data5_ = (Block5Data*) _userdata_;
	if (g_atomic_int_dec_and_test (&_data5_->_ref_count_)) {
		SeahorsePkcs11Request* self;
		self = _data5_->_data4_->self;
		_g_object_unref0 (_data5_->file);
		block4_data_unref (_data5_->_data4_);
		_data5_->_data4_ = NULL;
		g_slice_free (Block5Data, _data5_);
	}
}


static void ___lambda6_ (Block5Data* _data5_, GObject* obj, GAsyncResult* res) {
	Block4Data* _data4_;
	SeahorsePkcs11Request* self;
	GError * _inner_error_ = NULL;
	_data4_ = _data5_->_data4_;
	self = _data4_->self;
	g_return_if_fail (res != NULL);
	{
		gchar* new_etag = NULL;
		GFile* _tmp0_ = NULL;
		GAsyncResult* _tmp1_ = NULL;
		gchar* _tmp2_ = NULL;
		_tmp0_ = _data5_->file;
		_tmp1_ = res;
		g_file_replace_contents_finish (_tmp0_, _tmp1_, &_tmp2_, &_inner_error_);
		_g_free0 (new_etag);
		new_etag = _tmp2_;
		if (G_UNLIKELY (_inner_error_ != NULL)) {
			_g_free0 (new_etag);
			goto __catch6_g_error;
		}
		_g_free0 (new_etag);
	}
	goto __finally6;
	__catch6_g_error:
	{
		GError* err = NULL;
		GtkWindow* _tmp3_ = NULL;
		const gchar* _tmp4_ = NULL;
		GError* _tmp5_ = NULL;
		const gchar* _tmp6_ = NULL;
		err = _inner_error_;
		_inner_error_ = NULL;
		_tmp3_ = _data4_->parent;
		_tmp4_ = _ ("Couldn't save certificate request");
		_tmp5_ = err;
		_tmp6_ = _tmp5_->message;
		seahorse_util_show_error ((GtkWidget*) _tmp3_, _tmp4_, _tmp6_);
		_g_error_free0 (err);
	}
	__finally6:
	if (G_UNLIKELY (_inner_error_ != NULL)) {
		g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
		g_clear_error (&_inner_error_);
		return;
	}
}


static void ____lambda6__gasync_ready_callback (GObject* source_object, GAsyncResult* res, gpointer self) {
	___lambda6_ (self, source_object, res);
	block5_data_unref (self);
}


static void seahorse_pkcs11_request_save_certificate_request (SeahorsePkcs11Request* self, GcrCertificateRequest* req, GtkWindow* parent) {
	Block4Data* _data4_;
	GtkWindow* _tmp0_ = NULL;
	GtkWindow* _tmp1_ = NULL;
	GtkFileChooserDialog* chooser = NULL;
	const gchar* _tmp2_ = NULL;
	GtkWindow* _tmp3_ = NULL;
	GtkFileChooserDialog* _tmp4_ = NULL;
	GtkFileChooserDialog* _tmp5_ = NULL;
	GtkFileChooserDialog* _tmp6_ = NULL;
	GtkFileFilter* der_filter = NULL;
	GtkFileFilter* _tmp7_ = NULL;
	GtkFileFilter* _tmp8_ = NULL;
	const gchar* _tmp9_ = NULL;
	GtkFileFilter* _tmp10_ = NULL;
	GtkFileFilter* _tmp11_ = NULL;
	GtkFileFilter* _tmp12_ = NULL;
	GtkFileChooserDialog* _tmp13_ = NULL;
	GtkFileFilter* _tmp14_ = NULL;
	GtkFileFilter* _tmp15_ = NULL;
	GtkFileChooserDialog* _tmp16_ = NULL;
	GtkFileFilter* _tmp17_ = NULL;
	GtkFileFilter* pem_filter = NULL;
	GtkFileFilter* _tmp18_ = NULL;
	GtkFileFilter* _tmp19_ = NULL;
	const gchar* _tmp20_ = NULL;
	GtkFileFilter* _tmp21_ = NULL;
	GtkFileFilter* _tmp22_ = NULL;
	GtkFileChooserDialog* _tmp23_ = NULL;
	GtkFileFilter* _tmp24_ = NULL;
	GtkFileFilter* _tmp25_ = NULL;
	gchar* label = NULL;
	SeahorsePkcs11PrivateKey* _tmp26_ = NULL;
	gboolean _tmp27_ = FALSE;
	const gchar* _tmp28_ = NULL;
	gchar* filename = NULL;
	const gchar* _tmp31_ = NULL;
	gchar* _tmp32_ = NULL;
	const gchar* _tmp33_ = NULL;
	const gchar* _tmp34_ = NULL;
	gchar* _tmp35_ = NULL;
	GtkFileChooserDialog* _tmp36_ = NULL;
	const gchar* _tmp37_ = NULL;
	GtkFileChooserDialog* _tmp38_ = NULL;
	gint response = 0;
	GtkFileChooserDialog* _tmp39_ = NULL;
	gint _tmp40_ = 0;
	gint _tmp41_ = 0;
	GtkFileChooserDialog* _tmp53_ = NULL;
	g_return_if_fail (self != NULL);
	g_return_if_fail (req != NULL);
	_data4_ = g_slice_new0 (Block4Data);
	_data4_->_ref_count_ = 1;
	_data4_->self = g_object_ref (self);
	_tmp0_ = parent;
	_tmp1_ = _g_object_ref0 (_tmp0_);
	_g_object_unref0 (_data4_->parent);
	_data4_->parent = _tmp1_;
	_tmp2_ = _ ("Save certificate request");
	_tmp3_ = _data4_->parent;
	_tmp4_ = (GtkFileChooserDialog*) gtk_file_chooser_dialog_new (_tmp2_, _tmp3_, GTK_FILE_CHOOSER_ACTION_SAVE, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, GTK_STOCK_SAVE, GTK_RESPONSE_ACCEPT, NULL);
	g_object_ref_sink (_tmp4_);
	chooser = _tmp4_;
	_tmp5_ = chooser;
	gtk_dialog_set_default_response ((GtkDialog*) _tmp5_, (gint) GTK_RESPONSE_ACCEPT);
	_tmp6_ = chooser;
	gtk_file_chooser_set_local_only ((GtkFileChooser*) _tmp6_, FALSE);
	_tmp7_ = gtk_file_filter_new ();
	g_object_ref_sink (_tmp7_);
	der_filter = _tmp7_;
	_tmp8_ = der_filter;
	_tmp9_ = _ ("Certificate request");
	gtk_buildable_set_name ((GtkBuildable*) _tmp8_, _tmp9_);
	_tmp10_ = der_filter;
	gtk_file_filter_add_mime_type (_tmp10_, "application/pkcs10");
	_tmp11_ = der_filter;
	gtk_file_filter_add_pattern (_tmp11_, "*.p10");
	_tmp12_ = der_filter;
	gtk_file_filter_add_pattern (_tmp12_, "*.csr");
	_tmp13_ = chooser;
	_tmp14_ = der_filter;
	_tmp15_ = _g_object_ref0 (_tmp14_);
	gtk_file_chooser_add_filter ((GtkFileChooser*) _tmp13_, _tmp15_);
	_tmp16_ = chooser;
	_tmp17_ = der_filter;
	gtk_file_chooser_set_filter ((GtkFileChooser*) _tmp16_, _tmp17_);
	_tmp18_ = gtk_file_filter_new ();
	g_object_ref_sink (_tmp18_);
	pem_filter = _tmp18_;
	_tmp19_ = pem_filter;
	_tmp20_ = _ ("PEM encoded request");
	gtk_buildable_set_name ((GtkBuildable*) _tmp19_, _tmp20_);
	_tmp21_ = pem_filter;
	gtk_file_filter_add_mime_type (_tmp21_, "application/pkcs10+pem");
	_tmp22_ = pem_filter;
	gtk_file_filter_add_pattern (_tmp22_, "*.pem");
	_tmp23_ = chooser;
	_tmp24_ = pem_filter;
	_tmp25_ = _g_object_ref0 (_tmp24_);
	gtk_file_chooser_add_filter ((GtkFileChooser*) _tmp23_, _tmp25_);
	_tmp26_ = self->priv->_private_key;
	g_object_get ((GObject*) _tmp26_, "label", &label, NULL);
	_tmp28_ = label;
	if (_tmp28_ == NULL) {
		_tmp27_ = TRUE;
	} else {
		const gchar* _tmp29_ = NULL;
		_tmp29_ = label;
		_tmp27_ = g_strcmp0 (_tmp29_, "") == 0;
	}
	if (_tmp27_) {
		gchar* _tmp30_ = NULL;
		_tmp30_ = g_strdup ("Certificate Request");
		_g_free0 (label);
		label = _tmp30_;
	}
	_tmp31_ = label;
	_tmp32_ = g_strconcat (_tmp31_, ".csr", NULL);
	filename = _tmp32_;
	_tmp33_ = filename;
	_tmp34_ = seahorse_pkcs11_request_BAD_FILENAME_CHARS;
	_tmp35_ = string_delimit (_tmp33_, _tmp34_, '_');
	_g_free0 (filename);
	filename = _tmp35_;
	_tmp36_ = chooser;
	_tmp37_ = filename;
	gtk_file_chooser_set_current_name ((GtkFileChooser*) _tmp36_, _tmp37_);
	_tmp38_ = chooser;
	gtk_file_chooser_set_do_overwrite_confirmation ((GtkFileChooser*) _tmp38_, TRUE);
	_tmp39_ = chooser;
	_tmp40_ = gtk_dialog_run ((GtkDialog*) _tmp39_);
	response = _tmp40_;
	_tmp41_ = response;
	if (_tmp41_ == ((gint) GTK_RESPONSE_ACCEPT)) {
		Block5Data* _data5_;
		gboolean textual = FALSE;
		GtkFileChooserDialog* _tmp42_ = NULL;
		GtkFileFilter* _tmp43_ = NULL;
		GtkFileFilter* _tmp44_ = NULL;
		GcrCertificateRequest* _tmp45_ = NULL;
		gboolean _tmp46_ = FALSE;
		gsize _tmp47_;
		guint8* _tmp48_ = NULL;
		GtkFileChooserDialog* _tmp49_ = NULL;
		GFile* _tmp50_ = NULL;
		GFile* _tmp51_ = NULL;
		guint8* _tmp52_ = NULL;
		gint _tmp52__length1 = 0;
		_data5_ = g_slice_new0 (Block5Data);
		_data5_->_ref_count_ = 1;
		_data5_->_data4_ = block4_data_ref (_data4_);
		_tmp42_ = chooser;
		_tmp43_ = gtk_file_chooser_get_filter ((GtkFileChooser*) _tmp42_);
		_tmp44_ = pem_filter;
		textual = _tmp43_ == _tmp44_;
		_tmp45_ = req;
		_tmp46_ = textual;
		_tmp48_ = gcr_certificate_request_encode (_tmp45_, _tmp46_, &_tmp47_);
		self->priv->_encoded = (g_free (self->priv->_encoded), NULL);
		self->priv->_encoded = _tmp48_;
		self->priv->_encoded_length1 = _tmp47_;
		self->priv->__encoded_size_ = self->priv->_encoded_length1;
		_tmp49_ = chooser;
		_tmp50_ = gtk_file_chooser_get_file ((GtkFileChooser*) _tmp49_);
		_data5_->file = _tmp50_;
		_tmp51_ = _data5_->file;
		_tmp52_ = self->priv->_encoded;
		_tmp52__length1 = self->priv->_encoded_length1;
		g_file_replace_contents_async (_tmp51_, _tmp52_, (gsize) _tmp52__length1, NULL, FALSE, G_FILE_CREATE_NONE, NULL, ____lambda6__gasync_ready_callback, block5_data_ref (_data5_));
		block5_data_unref (_data5_);
		_data5_ = NULL;
	}
	_tmp53_ = chooser;
	gtk_widget_destroy ((GtkWidget*) _tmp53_);
	_g_free0 (filename);
	_g_free0 (label);
	_g_object_unref0 (pem_filter);
	_g_object_unref0 (der_filter);
	_g_object_unref0 (chooser);
	block4_data_unref (_data4_);
	_data4_ = NULL;
}


SeahorsePkcs11Request* seahorse_pkcs11_request_construct (GType object_type) {
	SeahorsePkcs11Request * self = NULL;
	self = (SeahorsePkcs11Request*) g_object_new (object_type, NULL);
	return self;
}


SeahorsePkcs11Request* seahorse_pkcs11_request_new (void) {
	return seahorse_pkcs11_request_construct (SEAHORSE_PKCS11_TYPE_REQUEST);
}


SeahorsePkcs11PrivateKey* seahorse_pkcs11_request_get_private_key (SeahorsePkcs11Request* self) {
	SeahorsePkcs11PrivateKey* result;
	SeahorsePkcs11PrivateKey* _tmp0_ = NULL;
	g_return_val_if_fail (self != NULL, NULL);
	_tmp0_ = self->priv->_private_key;
	result = _tmp0_;
	return result;
}


static void seahorse_pkcs11_request_set_private_key (SeahorsePkcs11Request* self, SeahorsePkcs11PrivateKey* value) {
	SeahorsePkcs11PrivateKey* _tmp0_ = NULL;
	SeahorsePkcs11PrivateKey* _tmp1_ = NULL;
	g_return_if_fail (self != NULL);
	_tmp0_ = value;
	_tmp1_ = _g_object_ref0 (_tmp0_);
	_g_object_unref0 (self->priv->_private_key);
	self->priv->_private_key = _tmp1_;
	g_object_notify ((GObject *) self, "private-key");
}


static void _seahorse_pkcs11_request___lambda7_ (SeahorsePkcs11Request* self) {
	seahorse_pkcs11_request_update_response (self);
}


static void __seahorse_pkcs11_request___lambda7__gtk_editable_changed (GtkEditable* _sender, gpointer self) {
	_seahorse_pkcs11_request___lambda7_ ((SeahorsePkcs11Request*) self);
}


static GObject * seahorse_pkcs11_request_constructor (GType type, guint n_construct_properties, GObjectConstructParam * construct_properties) {
	GObject * obj;
	GObjectClass * parent_class;
	SeahorsePkcs11Request * self;
	GtkBuilder* builder = NULL;
	GtkBuilder* _tmp0_ = NULL;
	gchar* path = NULL;
	gchar* _tmp1_ = NULL;
	GtkBox* content = NULL;
	GtkBox* _tmp5_ = NULL;
	GtkBox* _tmp6_ = NULL;
	GtkWidget* widget = NULL;
	GtkBuilder* _tmp7_ = NULL;
	GObject* _tmp8_ = NULL;
	GtkWidget* _tmp9_ = NULL;
	GtkBox* _tmp10_ = NULL;
	GtkWidget* _tmp11_ = NULL;
	GtkWidget* _tmp12_ = NULL;
	GtkBuilder* _tmp13_ = NULL;
	GObject* _tmp14_ = NULL;
	GtkEntry* _tmp15_ = NULL;
	GtkEntry* _tmp16_ = NULL;
	const gchar* _tmp17_ = NULL;
	SeahorsePkcs11PrivateKey* _tmp18_ = NULL;
	GError * _inner_error_ = NULL;
	parent_class = G_OBJECT_CLASS (seahorse_pkcs11_request_parent_class);
	obj = parent_class->constructor (type, n_construct_properties, construct_properties);
	self = G_TYPE_CHECK_INSTANCE_CAST (obj, SEAHORSE_PKCS11_TYPE_REQUEST, SeahorsePkcs11Request);
	_tmp0_ = gtk_builder_new ();
	builder = _tmp0_;
	_tmp1_ = g_strdup ("/org/gnome/Seahorse/seahorse-pkcs11-request.xml");
	path = _tmp1_;
	{
		GtkBuilder* _tmp2_ = NULL;
		const gchar* _tmp3_ = NULL;
		_tmp2_ = builder;
		_tmp3_ = path;
		gtk_builder_add_from_resource (_tmp2_, _tmp3_, &_inner_error_);
		if (G_UNLIKELY (_inner_error_ != NULL)) {
			goto __catch7_g_error;
		}
	}
	goto __finally7;
	__catch7_g_error:
	{
		GError* err = NULL;
		const gchar* _tmp4_ = NULL;
		err = _inner_error_;
		_inner_error_ = NULL;
		_tmp4_ = path;
		g_warning ("pkcs11-request.vala:41: couldn't load ui file: %s", _tmp4_);
		_g_error_free0 (err);
		_g_free0 (path);
		_g_object_unref0 (builder);
		return obj;
	}
	__finally7:
	if (G_UNLIKELY (_inner_error_ != NULL)) {
		_g_free0 (path);
		_g_object_unref0 (builder);
		g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
		g_clear_error (&_inner_error_);
	}
	gtk_window_set_resizable ((GtkWindow*) self, FALSE);
	_tmp5_ = (GtkBox*) gtk_dialog_get_content_area ((GtkDialog*) self);
	_tmp6_ = _g_object_ref0 (_tmp5_);
	content = _tmp6_;
	_tmp7_ = builder;
	_tmp8_ = gtk_builder_get_object (_tmp7_, "pkcs11-request");
	_tmp9_ = _g_object_ref0 (G_TYPE_CHECK_INSTANCE_CAST (_tmp8_, gtk_widget_get_type (), GtkWidget));
	widget = _tmp9_;
	_tmp10_ = content;
	_tmp11_ = widget;
	gtk_container_add ((GtkContainer*) _tmp10_, _tmp11_);
	_tmp12_ = widget;
	gtk_widget_show (_tmp12_);
	_tmp13_ = builder;
	_tmp14_ = gtk_builder_get_object (_tmp13_, "request-name");
	_tmp15_ = _g_object_ref0 (G_TYPE_CHECK_INSTANCE_CAST (_tmp14_, gtk_entry_get_type (), GtkEntry));
	_g_object_unref0 (self->priv->_name_entry);
	self->priv->_name_entry = _tmp15_;
	_tmp16_ = self->priv->_name_entry;
	g_signal_connect_object ((GtkEditable*) _tmp16_, "changed", (GCallback) __seahorse_pkcs11_request___lambda7__gtk_editable_changed, self, 0);
	_tmp17_ = _ ("Create");
	gtk_dialog_add_buttons ((GtkDialog*) self, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, _tmp17_, GTK_RESPONSE_OK, NULL);
	gtk_dialog_set_default_response ((GtkDialog*) self, (gint) GTK_RESPONSE_OK);
	seahorse_pkcs11_request_update_response (self);
	_tmp18_ = self->priv->_private_key;
	if (!G_TYPE_CHECK_INSTANCE_TYPE (_tmp18_, gck_object_get_type ())) {
		const gchar* _tmp19_ = NULL;
		_tmp19_ = g_type_name (gck_object_get_type ());
		g_critical ("pkcs11-request.vala:62: private key is not of type %s", _tmp19_);
	}
	_g_object_unref0 (widget);
	_g_object_unref0 (content);
	_g_free0 (path);
	_g_object_unref0 (builder);
	return obj;
}


static void seahorse_pkcs11_request_class_init (SeahorsePkcs11RequestClass * klass) {
	gchar* _tmp0_ = NULL;
	seahorse_pkcs11_request_parent_class = g_type_class_peek_parent (klass);
	g_type_class_add_private (klass, sizeof (SeahorsePkcs11RequestPrivate));
	((GtkDialogClass *) klass)->response = seahorse_pkcs11_request_real_response;
	G_OBJECT_CLASS (klass)->get_property = _vala_seahorse_pkcs11_request_get_property;
	G_OBJECT_CLASS (klass)->set_property = _vala_seahorse_pkcs11_request_set_property;
	G_OBJECT_CLASS (klass)->constructor = seahorse_pkcs11_request_constructor;
	G_OBJECT_CLASS (klass)->finalize = seahorse_pkcs11_request_finalize;
	g_object_class_install_property (G_OBJECT_CLASS (klass), SEAHORSE_PKCS11_REQUEST_PRIVATE_KEY, g_param_spec_object ("private-key", "private-key", "private-key", SEAHORSE_PKCS11_TYPE_PRIVATE_KEY, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE | G_PARAM_CONSTRUCT_ONLY));
	_tmp0_ = g_strdup ("/\\<>|?*");
	seahorse_pkcs11_request_BAD_FILENAME_CHARS = _tmp0_;
}


static void seahorse_pkcs11_request_instance_init (SeahorsePkcs11Request * self) {
	self->priv = SEAHORSE_PKCS11_REQUEST_GET_PRIVATE (self);
}


static void seahorse_pkcs11_request_finalize (GObject* obj) {
	SeahorsePkcs11Request * self;
	self = G_TYPE_CHECK_INSTANCE_CAST (obj, SEAHORSE_PKCS11_TYPE_REQUEST, SeahorsePkcs11Request);
	_g_object_unref0 (self->priv->_private_key);
	_g_object_unref0 (self->priv->_name_entry);
	self->priv->_encoded = (g_free (self->priv->_encoded), NULL);
	G_OBJECT_CLASS (seahorse_pkcs11_request_parent_class)->finalize (obj);
}


GType seahorse_pkcs11_request_get_type (void) {
	static volatile gsize seahorse_pkcs11_request_type_id__volatile = 0;
	if (g_once_init_enter (&seahorse_pkcs11_request_type_id__volatile)) {
		static const GTypeInfo g_define_type_info = { sizeof (SeahorsePkcs11RequestClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) seahorse_pkcs11_request_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (SeahorsePkcs11Request), 0, (GInstanceInitFunc) seahorse_pkcs11_request_instance_init, NULL };
		GType seahorse_pkcs11_request_type_id;
		seahorse_pkcs11_request_type_id = g_type_register_static (gtk_dialog_get_type (), "SeahorsePkcs11Request", &g_define_type_info, 0);
		g_once_init_leave (&seahorse_pkcs11_request_type_id__volatile, seahorse_pkcs11_request_type_id);
	}
	return seahorse_pkcs11_request_type_id__volatile;
}


static void _vala_seahorse_pkcs11_request_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec) {
	SeahorsePkcs11Request * self;
	self = G_TYPE_CHECK_INSTANCE_CAST (object, SEAHORSE_PKCS11_TYPE_REQUEST, SeahorsePkcs11Request);
	switch (property_id) {
		case SEAHORSE_PKCS11_REQUEST_PRIVATE_KEY:
		g_value_set_object (value, seahorse_pkcs11_request_get_private_key (self));
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}


static void _vala_seahorse_pkcs11_request_set_property (GObject * object, guint property_id, const GValue * value, GParamSpec * pspec) {
	SeahorsePkcs11Request * self;
	self = G_TYPE_CHECK_INSTANCE_CAST (object, SEAHORSE_PKCS11_TYPE_REQUEST, SeahorsePkcs11Request);
	switch (property_id) {
		case SEAHORSE_PKCS11_REQUEST_PRIVATE_KEY:
		seahorse_pkcs11_request_set_private_key (self, g_value_get_object (value));
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}



