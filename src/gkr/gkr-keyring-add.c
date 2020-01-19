/* gkr-keyring-add.c generated by valac 0.28.0, the Vala compiler
 * generated from gkr-keyring-add.vala, do not modify */

/*
 * Seahorse
 *
 * Copyright (C) 2008 Stefan Walter
 * Copyright (C) 2011 Collabora Ltd.
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
 * along with this program; if not, see <http://www.gnu.org/licenses/>.
 */

#include <glib.h>
#include <glib-object.h>
#include "seahorse-gkr.h"
#include <gtk/gtk.h>
#include <glib/gi18n-lib.h>
#include "seahorse-common.h"
#include <stdlib.h>
#include <string.h>
#include <gio/gio.h>
#include <libsecret/secret.h>

typedef struct _Block7Data Block7Data;
#define _g_object_unref0(var) ((var == NULL) ? NULL : (var = (g_object_unref (var), NULL)))
#define _g_free0(var) (var = (g_free (var), NULL))
#define _g_error_free0(var) ((var == NULL) ? NULL : (var = (g_error_free (var), NULL)))

struct _Block7Data {
	int _ref_count_;
	SeahorseGkrKeyringAdd* self;
	GtkEntry* entry;
};


static gpointer seahorse_gkr_keyring_add_parent_class = NULL;

enum  {
	SEAHORSE_GKR_KEYRING_ADD_DUMMY_PROPERTY
};
static GObject * seahorse_gkr_keyring_add_constructor (GType type, guint n_construct_properties, GObjectConstructParam * construct_properties);
static Block7Data* block7_data_ref (Block7Data* _data7_);
static void block7_data_unref (void * _userdata_);
static void _seahorse_gkr_keyring_add___lambda6_ (Block7Data* _data7_, GtkEditable* editable);
static void __seahorse_gkr_keyring_add___lambda6__gtk_editable_changed (GtkEditable* _sender, gpointer self);
static void _seahorse_gkr_keyring_add___lambda7_ (Block7Data* _data7_, gint resp);
static void ___lambda9_ (SeahorseGkrKeyringAdd* self, GObject* obj, GAsyncResult* res);
static void ____lambda9__gasync_ready_callback (GObject* source_object, GAsyncResult* res, gpointer self);
static void __seahorse_gkr_keyring_add___lambda7__gtk_dialog_response (GtkDialog* _sender, gint response_id, gpointer self);


SeahorseGkrKeyringAdd* seahorse_gkr_keyring_add_construct (GType object_type, GtkWindow* parent) {
	SeahorseGkrKeyringAdd * self = NULL;
	GtkWindow* _tmp0_ = NULL;
	_tmp0_ = parent;
	self = (SeahorseGkrKeyringAdd*) g_object_new (object_type, "transient-for", _tmp0_, NULL);
	gtk_widget_show ((GtkWidget*) self);
	gtk_window_present ((GtkWindow*) self);
	return self;
}


SeahorseGkrKeyringAdd* seahorse_gkr_keyring_add_new (GtkWindow* parent) {
	return seahorse_gkr_keyring_add_construct (SEAHORSE_GKR_TYPE_KEYRING_ADD, parent);
}


static Block7Data* block7_data_ref (Block7Data* _data7_) {
	g_atomic_int_inc (&_data7_->_ref_count_);
	return _data7_;
}


static void block7_data_unref (void * _userdata_) {
	Block7Data* _data7_;
	_data7_ = (Block7Data*) _userdata_;
	if (g_atomic_int_dec_and_test (&_data7_->_ref_count_)) {
		SeahorseGkrKeyringAdd* self;
		self = _data7_->self;
		_g_object_unref0 (_data7_->entry);
		_g_object_unref0 (self);
		g_slice_free (Block7Data, _data7_);
	}
}


static gpointer _g_object_ref0 (gpointer self) {
	return self ? g_object_ref (self) : NULL;
}


static void _seahorse_gkr_keyring_add___lambda6_ (Block7Data* _data7_, GtkEditable* editable) {
	SeahorseGkrKeyringAdd* self;
	gchar* name = NULL;
	GtkEntry* _tmp0_ = NULL;
	const gchar* _tmp1_ = NULL;
	gchar* _tmp2_ = NULL;
	const gchar* _tmp3_ = NULL;
	self = _data7_->self;
	g_return_if_fail (editable != NULL);
	_tmp0_ = _data7_->entry;
	_tmp1_ = gtk_entry_get_text (_tmp0_);
	_tmp2_ = g_strdup (_tmp1_);
	name = _tmp2_;
	_tmp3_ = name;
	gtk_dialog_set_response_sensitive ((GtkDialog*) self, (gint) GTK_RESPONSE_ACCEPT, g_strcmp0 (_tmp3_, "") != 0);
	_g_free0 (name);
}


static void __seahorse_gkr_keyring_add___lambda6__gtk_editable_changed (GtkEditable* _sender, gpointer self) {
	_seahorse_gkr_keyring_add___lambda6_ (self, _sender);
}


static void ___lambda9_ (SeahorseGkrKeyringAdd* self, GObject* obj, GAsyncResult* res) {
	GError * _inner_error_ = NULL;
	g_return_if_fail (res != NULL);
	seahorse_gkr_dialog_complete_request ((GtkWidget*) self, FALSE);
	{
		GAsyncResult* _tmp0_ = NULL;
		SecretCollection* _tmp1_ = NULL;
		SecretCollection* _tmp2_ = NULL;
		_tmp0_ = res;
		_tmp1_ = secret_collection_create_finish (_tmp0_, &_inner_error_);
		_tmp2_ = _tmp1_;
		_g_object_unref0 (_tmp2_);
		if (G_UNLIKELY (_inner_error_ != NULL)) {
			goto __catch14_g_error;
		}
	}
	goto __finally14;
	__catch14_g_error:
	{
		GError* err = NULL;
		const gchar* _tmp3_ = NULL;
		GError* _tmp4_ = NULL;
		const gchar* _tmp5_ = NULL;
		err = _inner_error_;
		_inner_error_ = NULL;
		_tmp3_ = _ ("Couldn't add keyring");
		_tmp4_ = err;
		_tmp5_ = _tmp4_->message;
		seahorse_util_show_error ((GtkWidget*) self, _tmp3_, _tmp5_);
		_g_error_free0 (err);
	}
	__finally14:
	if (G_UNLIKELY (_inner_error_ != NULL)) {
		g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
		g_clear_error (&_inner_error_);
		return;
	}
	gtk_widget_destroy ((GtkWidget*) self);
}


static void ____lambda9__gasync_ready_callback (GObject* source_object, GAsyncResult* res, gpointer self) {
	___lambda9_ ((SeahorseGkrKeyringAdd*) self, source_object, res);
	g_object_unref (self);
}


static void _seahorse_gkr_keyring_add___lambda7_ (Block7Data* _data7_, gint resp) {
	SeahorseGkrKeyringAdd* self;
	gint _tmp0_ = 0;
	self = _data7_->self;
	_tmp0_ = resp;
	if (_tmp0_ == ((gint) GTK_RESPONSE_ACCEPT)) {
		gchar* name = NULL;
		GtkEntry* _tmp1_ = NULL;
		const gchar* _tmp2_ = NULL;
		gchar* _tmp3_ = NULL;
		GCancellable* cancellable = NULL;
		GCancellable* _tmp4_ = NULL;
		SecretService* service = NULL;
		SeahorseGkrBackend* _tmp5_ = NULL;
		SeahorseGkrBackend* _tmp6_ = NULL;
		SecretService* _tmp7_ = NULL;
		SecretService* _tmp8_ = NULL;
		SecretService* _tmp9_ = NULL;
		SecretService* _tmp10_ = NULL;
		SecretService* _tmp11_ = NULL;
		const gchar* _tmp12_ = NULL;
		GCancellable* _tmp13_ = NULL;
		_tmp1_ = _data7_->entry;
		_tmp2_ = gtk_entry_get_text (_tmp1_);
		_tmp3_ = g_strdup (_tmp2_);
		name = _tmp3_;
		_tmp4_ = seahorse_gkr_dialog_begin_request ((GtkWidget*) self);
		cancellable = _tmp4_;
		_tmp5_ = seahorse_gkr_backend_instance ();
		_tmp6_ = _tmp5_;
		_tmp7_ = seahorse_gkr_backend_get_service (_tmp6_);
		_tmp8_ = _tmp7_;
		_tmp9_ = _g_object_ref0 (_tmp8_);
		_tmp10_ = _tmp9_;
		_g_object_unref0 (_tmp6_);
		service = _tmp10_;
		_tmp11_ = service;
		_tmp12_ = name;
		_tmp13_ = cancellable;
		secret_collection_create (_tmp11_, _tmp12_, NULL, SECRET_COLLECTION_CREATE_NONE, _tmp13_, ____lambda9__gasync_ready_callback, g_object_ref (self));
		_g_object_unref0 (service);
		_g_object_unref0 (cancellable);
		_g_free0 (name);
	} else {
		gtk_widget_destroy ((GtkWidget*) self);
	}
}


static void __seahorse_gkr_keyring_add___lambda7__gtk_dialog_response (GtkDialog* _sender, gint response_id, gpointer self) {
	_seahorse_gkr_keyring_add___lambda7_ (self, response_id);
}


static GObject * seahorse_gkr_keyring_add_constructor (GType type, guint n_construct_properties, GObjectConstructParam * construct_properties) {
	GObject * obj;
	GObjectClass * parent_class;
	SeahorseGkrKeyringAdd * self;
	Block7Data* _data7_;
	const gchar* _tmp0_ = NULL;
	GtkBuilder* builder = NULL;
	GtkBuilder* _tmp1_ = NULL;
	GtkBuilder* _tmp2_ = NULL;
	GObject* _tmp3_ = NULL;
	GtkEntry* _tmp4_ = NULL;
	GtkEntry* _tmp5_ = NULL;
	parent_class = G_OBJECT_CLASS (seahorse_gkr_keyring_add_parent_class);
	obj = parent_class->constructor (type, n_construct_properties, construct_properties);
	self = G_TYPE_CHECK_INSTANCE_CAST (obj, SEAHORSE_GKR_TYPE_KEYRING_ADD, SeahorseGkrKeyringAdd);
	_data7_ = g_slice_new0 (Block7Data);
	_data7_->_ref_count_ = 1;
	_data7_->self = g_object_ref (self);
	_tmp0_ = _ ("Add Password Keyring");
	gtk_window_set_title ((GtkWindow*) self, _tmp0_);
	gtk_window_set_modal ((GtkWindow*) self, TRUE);
	g_object_set ((GtkWindow*) self, "window-position", GTK_WIN_POS_CENTER_ON_PARENT, NULL);
	gtk_container_set_border_width ((GtkContainer*) self, (guint) 5);
	_tmp1_ = seahorse_util_load_built_contents ((GtkContainer*) self, "add-keyring");
	builder = _tmp1_;
	gtk_dialog_add_buttons ((GtkDialog*) self, GTK_STOCK_OK, GTK_RESPONSE_ACCEPT, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, NULL);
	_tmp2_ = builder;
	_tmp3_ = gtk_builder_get_object (_tmp2_, "keyring-name");
	_tmp4_ = _g_object_ref0 (G_TYPE_CHECK_INSTANCE_CAST (_tmp3_, gtk_entry_get_type (), GtkEntry));
	_data7_->entry = _tmp4_;
	gtk_dialog_set_response_sensitive ((GtkDialog*) self, (gint) GTK_RESPONSE_ACCEPT, FALSE);
	_tmp5_ = _data7_->entry;
	g_signal_connect_data ((GtkEditable*) _tmp5_, "changed", (GCallback) __seahorse_gkr_keyring_add___lambda6__gtk_editable_changed, block7_data_ref (_data7_), (GClosureNotify) block7_data_unref, 0);
	g_signal_connect_data ((GtkDialog*) self, "response", (GCallback) __seahorse_gkr_keyring_add___lambda7__gtk_dialog_response, block7_data_ref (_data7_), (GClosureNotify) block7_data_unref, 0);
	_g_object_unref0 (builder);
	block7_data_unref (_data7_);
	_data7_ = NULL;
	return obj;
}


static void seahorse_gkr_keyring_add_class_init (SeahorseGkrKeyringAddClass * klass) {
	seahorse_gkr_keyring_add_parent_class = g_type_class_peek_parent (klass);
	G_OBJECT_CLASS (klass)->constructor = seahorse_gkr_keyring_add_constructor;
}


static void seahorse_gkr_keyring_add_instance_init (SeahorseGkrKeyringAdd * self) {
}


GType seahorse_gkr_keyring_add_get_type (void) {
	static volatile gsize seahorse_gkr_keyring_add_type_id__volatile = 0;
	if (g_once_init_enter (&seahorse_gkr_keyring_add_type_id__volatile)) {
		static const GTypeInfo g_define_type_info = { sizeof (SeahorseGkrKeyringAddClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) seahorse_gkr_keyring_add_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (SeahorseGkrKeyringAdd), 0, (GInstanceInitFunc) seahorse_gkr_keyring_add_instance_init, NULL };
		GType seahorse_gkr_keyring_add_type_id;
		seahorse_gkr_keyring_add_type_id = g_type_register_static (gtk_dialog_get_type (), "SeahorseGkrKeyringAdd", &g_define_type_info, 0);
		g_once_init_leave (&seahorse_gkr_keyring_add_type_id__volatile, seahorse_gkr_keyring_add_type_id);
	}
	return seahorse_gkr_keyring_add_type_id__volatile;
}



