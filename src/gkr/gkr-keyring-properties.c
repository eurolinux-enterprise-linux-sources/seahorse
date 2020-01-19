/* gkr-keyring-properties.c generated by valac 0.28.0, the Vala compiler
 * generated from gkr-keyring-properties.vala, do not modify */

/*
 * Seahorse
 *
 * Copyright (C) 2008 Stefan Walter
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
#include <stdlib.h>
#include <string.h>
#include "seahorse-common.h"
#include <libsecret/secret.h>

#define _g_object_unref0(var) ((var == NULL) ? NULL : (var = (g_object_unref (var), NULL)))
#define _g_free0(var) (var = (g_free (var), NULL))
#define _g_error_free0(var) ((var == NULL) ? NULL : (var = (g_error_free (var), NULL)))

struct _SeahorseGkrKeyringPropertiesPrivate {
	SeahorseGkrKeyring* _keyring;
	GtkBuilder* _builder;
};


static gpointer seahorse_gkr_keyring_properties_parent_class = NULL;

#define SEAHORSE_GKR_KEYRING_PROPERTIES_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), SEAHORSE_GKR_TYPE_KEYRING_PROPERTIES, SeahorseGkrKeyringPropertiesPrivate))
enum  {
	SEAHORSE_GKR_KEYRING_PROPERTIES_DUMMY_PROPERTY,
	SEAHORSE_GKR_KEYRING_PROPERTIES_KEYRING
};
static GObject * seahorse_gkr_keyring_properties_constructor (GType type, guint n_construct_properties, GObjectConstructParam * construct_properties);
static void _seahorse_gkr_keyring_properties___lambda31_ (SeahorseGkrKeyringProperties* self, gint response);
static void __seahorse_gkr_keyring_properties___lambda31__gtk_dialog_response (GtkDialog* _sender, gint response_id, gpointer self);
static void _seahorse_gkr_keyring_properties___lambda32_ (SeahorseGkrKeyringProperties* self, GParamSpec* pspec);
static void __seahorse_gkr_keyring_properties___lambda32__g_object_notify (GObject* _sender, GParamSpec* pspec, gpointer self);
static void seahorse_gkr_keyring_properties_finalize (GObject* obj);
static void _vala_seahorse_gkr_keyring_properties_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec);
static void _vala_seahorse_gkr_keyring_properties_set_property (GObject * object, guint property_id, const GValue * value, GParamSpec * pspec);


SeahorseGkrKeyringProperties* seahorse_gkr_keyring_properties_construct (GType object_type, SeahorseGkrKeyring* keyring, GtkWindow* parent) {
	SeahorseGkrKeyringProperties * self = NULL;
	SeahorseGkrKeyring* _tmp0_ = NULL;
	GtkWindow* _tmp1_ = NULL;
	g_return_val_if_fail (keyring != NULL, NULL);
	_tmp0_ = keyring;
	_tmp1_ = parent;
	self = (SeahorseGkrKeyringProperties*) g_object_new (object_type, "keyring", _tmp0_, "transient-for", _tmp1_, NULL);
	return self;
}


SeahorseGkrKeyringProperties* seahorse_gkr_keyring_properties_new (SeahorseGkrKeyring* keyring, GtkWindow* parent) {
	return seahorse_gkr_keyring_properties_construct (SEAHORSE_GKR_TYPE_KEYRING_PROPERTIES, keyring, parent);
}


SeahorseGkrKeyring* seahorse_gkr_keyring_properties_get_keyring (SeahorseGkrKeyringProperties* self) {
	SeahorseGkrKeyring* result;
	SeahorseGkrKeyring* _tmp0_ = NULL;
	g_return_val_if_fail (self != NULL, NULL);
	_tmp0_ = self->priv->_keyring;
	result = _tmp0_;
	return result;
}


static gpointer _g_object_ref0 (gpointer self) {
	return self ? g_object_ref (self) : NULL;
}


static void seahorse_gkr_keyring_properties_set_keyring (SeahorseGkrKeyringProperties* self, SeahorseGkrKeyring* value) {
	SeahorseGkrKeyring* _tmp0_ = NULL;
	SeahorseGkrKeyring* _tmp1_ = NULL;
	g_return_if_fail (self != NULL);
	_tmp0_ = value;
	_tmp1_ = _g_object_ref0 (_tmp0_);
	_g_object_unref0 (self->priv->_keyring);
	self->priv->_keyring = _tmp1_;
	g_object_notify ((GObject *) self, "keyring");
}


static void _seahorse_gkr_keyring_properties___lambda31_ (SeahorseGkrKeyringProperties* self, gint response) {
	gtk_widget_destroy ((GtkWidget*) self);
}


static void __seahorse_gkr_keyring_properties___lambda31__gtk_dialog_response (GtkDialog* _sender, gint response_id, gpointer self) {
	_seahorse_gkr_keyring_properties___lambda31_ ((SeahorseGkrKeyringProperties*) self, response_id);
}


static void _seahorse_gkr_keyring_properties___lambda32_ (SeahorseGkrKeyringProperties* self, GParamSpec* pspec) {
	GParamSpec* _tmp0_ = NULL;
	const gchar* _tmp1_ = NULL;
	const gchar* _tmp2_ = NULL;
	GQuark _tmp4_ = 0U;
	static GQuark _tmp3_label0 = 0;
	g_return_if_fail (pspec != NULL);
	_tmp0_ = pspec;
	_tmp1_ = _tmp0_->name;
	_tmp2_ = _tmp1_;
	_tmp4_ = (NULL == _tmp2_) ? 0 : g_quark_from_string (_tmp2_);
	if (_tmp4_ == ((0 != _tmp3_label0) ? _tmp3_label0 : (_tmp3_label0 = g_quark_from_static_string ("created")))) {
		switch (0) {
			default:
			{
				GtkLabel* created = NULL;
				GtkBuilder* _tmp5_ = NULL;
				GObject* _tmp6_ = NULL;
				GtkLabel* _tmp7_ = NULL;
				GtkLabel* _tmp8_ = NULL;
				SeahorseGkrKeyring* _tmp9_ = NULL;
				guint64 _tmp10_ = 0ULL;
				guint64 _tmp11_ = 0ULL;
				gchar* _tmp12_ = NULL;
				gchar* _tmp13_ = NULL;
				_tmp5_ = self->priv->_builder;
				_tmp6_ = gtk_builder_get_object (_tmp5_, "created-field");
				_tmp7_ = _g_object_ref0 (G_TYPE_CHECK_INSTANCE_CAST (_tmp6_, gtk_label_get_type (), GtkLabel));
				created = _tmp7_;
				_tmp8_ = created;
				_tmp9_ = self->priv->_keyring;
				g_object_get ((SecretCollection*) _tmp9_, "created", &_tmp10_, NULL);
				_tmp11_ = _tmp10_;
				_tmp12_ = seahorse_util_get_display_date_string ((glong) _tmp11_);
				_tmp13_ = _tmp12_;
				gtk_label_set_label (_tmp8_, _tmp13_);
				_g_free0 (_tmp13_);
				_g_object_unref0 (created);
				break;
			}
		}
	}
}


static void __seahorse_gkr_keyring_properties___lambda32__g_object_notify (GObject* _sender, GParamSpec* pspec, gpointer self) {
	_seahorse_gkr_keyring_properties___lambda32_ ((SeahorseGkrKeyringProperties*) self, pspec);
}


static GObject * seahorse_gkr_keyring_properties_constructor (GType type, guint n_construct_properties, GObjectConstructParam * construct_properties) {
	GObject * obj;
	GObjectClass * parent_class;
	SeahorseGkrKeyringProperties * self;
	GtkBuilder* _tmp0_ = NULL;
	GtkWidget* content = NULL;
	GtkBuilder* _tmp6_ = NULL;
	GObject* _tmp7_ = NULL;
	GtkWidget* _tmp8_ = NULL;
	GtkBox* _tmp9_ = NULL;
	GtkWidget* _tmp10_ = NULL;
	GtkWidget* _tmp11_ = NULL;
	SeahorseGkrKeyring* _tmp12_ = NULL;
	GtkBuilder* _tmp13_ = NULL;
	GObject* _tmp14_ = NULL;
	SeahorseGkrKeyring* _tmp15_ = NULL;
	GtkLabel* name = NULL;
	GtkBuilder* _tmp16_ = NULL;
	GObject* _tmp17_ = NULL;
	GtkLabel* _tmp18_ = NULL;
	SeahorseGkrKeyring* _tmp19_ = NULL;
	GtkLabel* _tmp20_ = NULL;
	SeahorseGkrKeyring* _tmp21_ = NULL;
	GError * _inner_error_ = NULL;
	parent_class = G_OBJECT_CLASS (seahorse_gkr_keyring_properties_parent_class);
	obj = parent_class->constructor (type, n_construct_properties, construct_properties);
	self = G_TYPE_CHECK_INSTANCE_CAST (obj, SEAHORSE_GKR_TYPE_KEYRING_PROPERTIES, SeahorseGkrKeyringProperties);
	_tmp0_ = gtk_builder_new ();
	_g_object_unref0 (self->priv->_builder);
	self->priv->_builder = _tmp0_;
	{
		gchar* path = NULL;
		gchar* _tmp1_ = NULL;
		GtkBuilder* _tmp2_ = NULL;
		const gchar* _tmp3_ = NULL;
		_tmp1_ = g_strdup ("/org/gnome/Seahorse/seahorse-gkr-keyring.xml");
		path = _tmp1_;
		_tmp2_ = self->priv->_builder;
		_tmp3_ = path;
		gtk_builder_add_from_resource (_tmp2_, _tmp3_, &_inner_error_);
		if (G_UNLIKELY (_inner_error_ != NULL)) {
			_g_free0 (path);
			goto __catch15_g_error;
		}
		_g_free0 (path);
	}
	goto __finally15;
	__catch15_g_error:
	{
		GError* err = NULL;
		GError* _tmp4_ = NULL;
		const gchar* _tmp5_ = NULL;
		err = _inner_error_;
		_inner_error_ = NULL;
		_tmp4_ = err;
		_tmp5_ = _tmp4_->message;
		g_critical ("gkr-keyring-properties.vala:33: %s", _tmp5_);
		_g_error_free0 (err);
	}
	__finally15:
	if (G_UNLIKELY (_inner_error_ != NULL)) {
		g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
		g_clear_error (&_inner_error_);
	}
	gtk_dialog_add_button ((GtkDialog*) self, GTK_STOCK_CLOSE, (gint) GTK_RESPONSE_CLOSE);
	_tmp6_ = self->priv->_builder;
	_tmp7_ = gtk_builder_get_object (_tmp6_, "gkr-item-properties");
	_tmp8_ = _g_object_ref0 (G_TYPE_CHECK_INSTANCE_CAST (_tmp7_, gtk_widget_get_type (), GtkWidget));
	content = _tmp8_;
	_tmp9_ = (GtkBox*) gtk_dialog_get_content_area ((GtkDialog*) self);
	_tmp10_ = content;
	gtk_container_add (G_TYPE_CHECK_INSTANCE_CAST (_tmp9_, gtk_container_get_type (), GtkContainer), _tmp10_);
	_tmp11_ = content;
	gtk_widget_show (_tmp11_);
	g_signal_connect_object ((GtkDialog*) self, "response", (GCallback) __seahorse_gkr_keyring_properties___lambda31__gtk_dialog_response, self, 0);
	_tmp12_ = self->priv->_keyring;
	_tmp13_ = self->priv->_builder;
	_tmp14_ = gtk_builder_get_object (_tmp13_, "keyring-image");
	g_object_bind_property_with_closures ((GObject*) _tmp12_, "icon", _tmp14_, "gicon", G_BINDING_SYNC_CREATE, (GClosure*) ((NULL == NULL) ? NULL : g_cclosure_new ((GCallback) NULL, NULL, NULL)), (GClosure*) ((NULL == NULL) ? NULL : g_cclosure_new ((GCallback) NULL, NULL, NULL)));
	_tmp15_ = self->priv->_keyring;
	g_object_bind_property_with_closures ((GObject*) _tmp15_, "label", (GObject*) self, "title", G_BINDING_SYNC_CREATE, (GClosure*) ((NULL == NULL) ? NULL : g_cclosure_new ((GCallback) NULL, NULL, NULL)), (GClosure*) ((NULL == NULL) ? NULL : g_cclosure_new ((GCallback) NULL, NULL, NULL)));
	_tmp16_ = self->priv->_builder;
	_tmp17_ = gtk_builder_get_object (_tmp16_, "name-field");
	_tmp18_ = _g_object_ref0 (G_TYPE_CHECK_INSTANCE_CAST (_tmp17_, gtk_label_get_type (), GtkLabel));
	name = _tmp18_;
	_tmp19_ = self->priv->_keyring;
	_tmp20_ = name;
	g_object_bind_property_with_closures ((GObject*) _tmp19_, "label", (GObject*) _tmp20_, "label", G_BINDING_SYNC_CREATE, (GClosure*) ((NULL == NULL) ? NULL : g_cclosure_new ((GCallback) NULL, NULL, NULL)), (GClosure*) ((NULL == NULL) ? NULL : g_cclosure_new ((GCallback) NULL, NULL, NULL)));
	_tmp21_ = self->priv->_keyring;
	g_signal_connect_object ((GObject*) _tmp21_, "notify", (GCallback) __seahorse_gkr_keyring_properties___lambda32__g_object_notify, self, 0);
	_g_object_unref0 (name);
	_g_object_unref0 (content);
	return obj;
}


static void seahorse_gkr_keyring_properties_class_init (SeahorseGkrKeyringPropertiesClass * klass) {
	seahorse_gkr_keyring_properties_parent_class = g_type_class_peek_parent (klass);
	g_type_class_add_private (klass, sizeof (SeahorseGkrKeyringPropertiesPrivate));
	G_OBJECT_CLASS (klass)->get_property = _vala_seahorse_gkr_keyring_properties_get_property;
	G_OBJECT_CLASS (klass)->set_property = _vala_seahorse_gkr_keyring_properties_set_property;
	G_OBJECT_CLASS (klass)->constructor = seahorse_gkr_keyring_properties_constructor;
	G_OBJECT_CLASS (klass)->finalize = seahorse_gkr_keyring_properties_finalize;
	g_object_class_install_property (G_OBJECT_CLASS (klass), SEAHORSE_GKR_KEYRING_PROPERTIES_KEYRING, g_param_spec_object ("keyring", "keyring", "keyring", SEAHORSE_GKR_TYPE_KEYRING, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE | G_PARAM_CONSTRUCT_ONLY));
}


static void seahorse_gkr_keyring_properties_instance_init (SeahorseGkrKeyringProperties * self) {
	self->priv = SEAHORSE_GKR_KEYRING_PROPERTIES_GET_PRIVATE (self);
}


static void seahorse_gkr_keyring_properties_finalize (GObject* obj) {
	SeahorseGkrKeyringProperties * self;
	self = G_TYPE_CHECK_INSTANCE_CAST (obj, SEAHORSE_GKR_TYPE_KEYRING_PROPERTIES, SeahorseGkrKeyringProperties);
	_g_object_unref0 (self->priv->_keyring);
	_g_object_unref0 (self->priv->_builder);
	G_OBJECT_CLASS (seahorse_gkr_keyring_properties_parent_class)->finalize (obj);
}


GType seahorse_gkr_keyring_properties_get_type (void) {
	static volatile gsize seahorse_gkr_keyring_properties_type_id__volatile = 0;
	if (g_once_init_enter (&seahorse_gkr_keyring_properties_type_id__volatile)) {
		static const GTypeInfo g_define_type_info = { sizeof (SeahorseGkrKeyringPropertiesClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) seahorse_gkr_keyring_properties_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (SeahorseGkrKeyringProperties), 0, (GInstanceInitFunc) seahorse_gkr_keyring_properties_instance_init, NULL };
		GType seahorse_gkr_keyring_properties_type_id;
		seahorse_gkr_keyring_properties_type_id = g_type_register_static (gtk_dialog_get_type (), "SeahorseGkrKeyringProperties", &g_define_type_info, 0);
		g_once_init_leave (&seahorse_gkr_keyring_properties_type_id__volatile, seahorse_gkr_keyring_properties_type_id);
	}
	return seahorse_gkr_keyring_properties_type_id__volatile;
}


static void _vala_seahorse_gkr_keyring_properties_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec) {
	SeahorseGkrKeyringProperties * self;
	self = G_TYPE_CHECK_INSTANCE_CAST (object, SEAHORSE_GKR_TYPE_KEYRING_PROPERTIES, SeahorseGkrKeyringProperties);
	switch (property_id) {
		case SEAHORSE_GKR_KEYRING_PROPERTIES_KEYRING:
		g_value_set_object (value, seahorse_gkr_keyring_properties_get_keyring (self));
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}


static void _vala_seahorse_gkr_keyring_properties_set_property (GObject * object, guint property_id, const GValue * value, GParamSpec * pspec) {
	SeahorseGkrKeyringProperties * self;
	self = G_TYPE_CHECK_INSTANCE_CAST (object, SEAHORSE_GKR_TYPE_KEYRING_PROPERTIES, SeahorseGkrKeyringProperties);
	switch (property_id) {
		case SEAHORSE_GKR_KEYRING_PROPERTIES_KEYRING:
		seahorse_gkr_keyring_properties_set_keyring (self, g_value_get_object (value));
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}



