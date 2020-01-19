/* seahorse-pkcs11.h generated by valac 0.28.0, the Vala compiler, do not modify */


#ifndef __PKCS11_SEAHORSE_PKCS11_H__
#define __PKCS11_SEAHORSE_PKCS11_H__

#include <glib.h>
#include <glib-object.h>
#include "seahorse-common.h"
#include <gcr/gcr-base.h>
#include <gio/gio.h>
#include <gck/gck.h>
#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>

G_BEGIN_DECLS


#define SEAHORSE_TYPE_CERTIFICATE_DER_EXPORTER (seahorse_certificate_der_exporter_get_type ())
#define SEAHORSE_CERTIFICATE_DER_EXPORTER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), SEAHORSE_TYPE_CERTIFICATE_DER_EXPORTER, SeahorseCertificateDerExporter))
#define SEAHORSE_CERTIFICATE_DER_EXPORTER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), SEAHORSE_TYPE_CERTIFICATE_DER_EXPORTER, SeahorseCertificateDerExporterClass))
#define SEAHORSE_IS_CERTIFICATE_DER_EXPORTER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), SEAHORSE_TYPE_CERTIFICATE_DER_EXPORTER))
#define SEAHORSE_IS_CERTIFICATE_DER_EXPORTER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), SEAHORSE_TYPE_CERTIFICATE_DER_EXPORTER))
#define SEAHORSE_CERTIFICATE_DER_EXPORTER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), SEAHORSE_TYPE_CERTIFICATE_DER_EXPORTER, SeahorseCertificateDerExporterClass))

typedef struct _SeahorseCertificateDerExporter SeahorseCertificateDerExporter;
typedef struct _SeahorseCertificateDerExporterClass SeahorseCertificateDerExporterClass;
typedef struct _SeahorseCertificateDerExporterPrivate SeahorseCertificateDerExporterPrivate;

#define SEAHORSE_PKCS11_TYPE_CERTIFICATE (seahorse_pkcs11_certificate_get_type ())
#define SEAHORSE_PKCS11_CERTIFICATE(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), SEAHORSE_PKCS11_TYPE_CERTIFICATE, SeahorsePkcs11Certificate))
#define SEAHORSE_PKCS11_CERTIFICATE_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), SEAHORSE_PKCS11_TYPE_CERTIFICATE, SeahorsePkcs11CertificateClass))
#define SEAHORSE_PKCS11_IS_CERTIFICATE(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), SEAHORSE_PKCS11_TYPE_CERTIFICATE))
#define SEAHORSE_PKCS11_IS_CERTIFICATE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), SEAHORSE_PKCS11_TYPE_CERTIFICATE))
#define SEAHORSE_PKCS11_CERTIFICATE_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), SEAHORSE_PKCS11_TYPE_CERTIFICATE, SeahorsePkcs11CertificateClass))

typedef struct _SeahorsePkcs11Certificate SeahorsePkcs11Certificate;
typedef struct _SeahorsePkcs11CertificateClass SeahorsePkcs11CertificateClass;
typedef struct _SeahorsePkcs11CertificatePrivate SeahorsePkcs11CertificatePrivate;

#define SEAHORSE_PKCS11_TYPE_TOKEN (seahorse_pkcs11_token_get_type ())
#define SEAHORSE_PKCS11_TOKEN(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), SEAHORSE_PKCS11_TYPE_TOKEN, SeahorsePkcs11Token))
#define SEAHORSE_PKCS11_TOKEN_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), SEAHORSE_PKCS11_TYPE_TOKEN, SeahorsePkcs11TokenClass))
#define SEAHORSE_PKCS11_IS_TOKEN(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), SEAHORSE_PKCS11_TYPE_TOKEN))
#define SEAHORSE_PKCS11_IS_TOKEN_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), SEAHORSE_PKCS11_TYPE_TOKEN))
#define SEAHORSE_PKCS11_TOKEN_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), SEAHORSE_PKCS11_TYPE_TOKEN, SeahorsePkcs11TokenClass))

typedef struct _SeahorsePkcs11Token SeahorsePkcs11Token;
typedef struct _SeahorsePkcs11TokenClass SeahorsePkcs11TokenClass;

#define SEAHORSE_PKCS11_TYPE_PRIVATE_KEY (seahorse_pkcs11_private_key_get_type ())
#define SEAHORSE_PKCS11_PRIVATE_KEY(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), SEAHORSE_PKCS11_TYPE_PRIVATE_KEY, SeahorsePkcs11PrivateKey))
#define SEAHORSE_PKCS11_PRIVATE_KEY_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), SEAHORSE_PKCS11_TYPE_PRIVATE_KEY, SeahorsePkcs11PrivateKeyClass))
#define SEAHORSE_PKCS11_IS_PRIVATE_KEY(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), SEAHORSE_PKCS11_TYPE_PRIVATE_KEY))
#define SEAHORSE_PKCS11_IS_PRIVATE_KEY_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), SEAHORSE_PKCS11_TYPE_PRIVATE_KEY))
#define SEAHORSE_PKCS11_PRIVATE_KEY_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), SEAHORSE_PKCS11_TYPE_PRIVATE_KEY, SeahorsePkcs11PrivateKeyClass))

typedef struct _SeahorsePkcs11PrivateKey SeahorsePkcs11PrivateKey;
typedef struct _SeahorsePkcs11PrivateKeyClass SeahorsePkcs11PrivateKeyClass;

#define SEAHORSE_PKCS11_TYPE_DELETER (seahorse_pkcs11_deleter_get_type ())
#define SEAHORSE_PKCS11_DELETER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), SEAHORSE_PKCS11_TYPE_DELETER, SeahorsePkcs11Deleter))
#define SEAHORSE_PKCS11_DELETER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), SEAHORSE_PKCS11_TYPE_DELETER, SeahorsePkcs11DeleterClass))
#define SEAHORSE_PKCS11_IS_DELETER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), SEAHORSE_PKCS11_TYPE_DELETER))
#define SEAHORSE_PKCS11_IS_DELETER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), SEAHORSE_PKCS11_TYPE_DELETER))
#define SEAHORSE_PKCS11_DELETER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), SEAHORSE_PKCS11_TYPE_DELETER, SeahorsePkcs11DeleterClass))

typedef struct _SeahorsePkcs11Deleter SeahorsePkcs11Deleter;
typedef struct _SeahorsePkcs11DeleterClass SeahorsePkcs11DeleterClass;
typedef struct _SeahorsePkcs11DeleterPrivate SeahorsePkcs11DeleterPrivate;
typedef struct _SeahorsePkcs11PrivateKeyPrivate SeahorsePkcs11PrivateKeyPrivate;

#define SEAHORSE_PKCS11_TYPE_PROPERTIES (seahorse_pkcs11_properties_get_type ())
#define SEAHORSE_PKCS11_PROPERTIES(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), SEAHORSE_PKCS11_TYPE_PROPERTIES, SeahorsePkcs11Properties))
#define SEAHORSE_PKCS11_PROPERTIES_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), SEAHORSE_PKCS11_TYPE_PROPERTIES, SeahorsePkcs11PropertiesClass))
#define SEAHORSE_PKCS11_IS_PROPERTIES(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), SEAHORSE_PKCS11_TYPE_PROPERTIES))
#define SEAHORSE_PKCS11_IS_PROPERTIES_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), SEAHORSE_PKCS11_TYPE_PROPERTIES))
#define SEAHORSE_PKCS11_PROPERTIES_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), SEAHORSE_PKCS11_TYPE_PROPERTIES, SeahorsePkcs11PropertiesClass))

typedef struct _SeahorsePkcs11Properties SeahorsePkcs11Properties;
typedef struct _SeahorsePkcs11PropertiesClass SeahorsePkcs11PropertiesClass;
typedef struct _SeahorsePkcs11PropertiesPrivate SeahorsePkcs11PropertiesPrivate;

#define SEAHORSE_PKCS11_TYPE_REQUEST (seahorse_pkcs11_request_get_type ())
#define SEAHORSE_PKCS11_REQUEST(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), SEAHORSE_PKCS11_TYPE_REQUEST, SeahorsePkcs11Request))
#define SEAHORSE_PKCS11_REQUEST_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), SEAHORSE_PKCS11_TYPE_REQUEST, SeahorsePkcs11RequestClass))
#define SEAHORSE_PKCS11_IS_REQUEST(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), SEAHORSE_PKCS11_TYPE_REQUEST))
#define SEAHORSE_PKCS11_IS_REQUEST_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), SEAHORSE_PKCS11_TYPE_REQUEST))
#define SEAHORSE_PKCS11_REQUEST_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), SEAHORSE_PKCS11_TYPE_REQUEST, SeahorsePkcs11RequestClass))

typedef struct _SeahorsePkcs11Request SeahorsePkcs11Request;
typedef struct _SeahorsePkcs11RequestClass SeahorsePkcs11RequestClass;
typedef struct _SeahorsePkcs11RequestPrivate SeahorsePkcs11RequestPrivate;
typedef struct _SeahorsePkcs11TokenPrivate SeahorsePkcs11TokenPrivate;

struct _SeahorseCertificateDerExporter {
	GObject parent_instance;
	SeahorseCertificateDerExporterPrivate * priv;
};

struct _SeahorseCertificateDerExporterClass {
	GObjectClass parent_class;
};

struct _SeahorsePkcs11Certificate {
	GckObject parent_instance;
	SeahorsePkcs11CertificatePrivate * priv;
};

struct _SeahorsePkcs11CertificateClass {
	GckObjectClass parent_class;
};

struct _SeahorsePkcs11Deleter {
	SeahorseDeleter parent_instance;
	SeahorsePkcs11DeleterPrivate * priv;
	GList* objects;
};

struct _SeahorsePkcs11DeleterClass {
	SeahorseDeleterClass parent_class;
};

struct _SeahorsePkcs11PrivateKey {
	GckObject parent_instance;
	SeahorsePkcs11PrivateKeyPrivate * priv;
};

struct _SeahorsePkcs11PrivateKeyClass {
	GckObjectClass parent_class;
};

struct _SeahorsePkcs11Properties {
	GtkWindow parent_instance;
	SeahorsePkcs11PropertiesPrivate * priv;
};

struct _SeahorsePkcs11PropertiesClass {
	GtkWindowClass parent_class;
};

struct _SeahorsePkcs11Request {
	GtkDialog parent_instance;
	SeahorsePkcs11RequestPrivate * priv;
};

struct _SeahorsePkcs11RequestClass {
	GtkDialogClass parent_class;
};

struct _SeahorsePkcs11Token {
	GObject parent_instance;
	SeahorsePkcs11TokenPrivate * priv;
};

struct _SeahorsePkcs11TokenClass {
	GObjectClass parent_class;
};


GType seahorse_certificate_der_exporter_get_type (void) G_GNUC_CONST;
SeahorseCertificateDerExporter* seahorse_certificate_der_exporter_new (GcrCertificate* certificate);
SeahorseCertificateDerExporter* seahorse_certificate_der_exporter_construct (GType object_type, GcrCertificate* certificate);
GType seahorse_pkcs11_certificate_get_type (void) G_GNUC_CONST;
SeahorsePkcs11Certificate* seahorse_pkcs11_certificate_new (void);
SeahorsePkcs11Certificate* seahorse_pkcs11_certificate_construct (GType object_type);
GType seahorse_pkcs11_token_get_type (void) G_GNUC_CONST;
SeahorsePkcs11Token* seahorse_pkcs11_certificate_get_place (SeahorsePkcs11Certificate* self);
void seahorse_pkcs11_certificate_set_place (SeahorsePkcs11Certificate* self, SeahorsePkcs11Token* value);
SeahorseFlags seahorse_pkcs11_certificate_get_object_flags (SeahorsePkcs11Certificate* self);
GtkActionGroup* seahorse_pkcs11_certificate_get_actions (SeahorsePkcs11Certificate* self);
GType seahorse_pkcs11_private_key_get_type (void) G_GNUC_CONST;
SeahorsePkcs11PrivateKey* seahorse_pkcs11_certificate_get_partner (SeahorsePkcs11Certificate* self);
void seahorse_pkcs11_certificate_set_partner (SeahorsePkcs11Certificate* self, SeahorsePkcs11PrivateKey* value);
GType seahorse_pkcs11_deleter_get_type (void) G_GNUC_CONST;
SeahorsePkcs11Deleter* seahorse_pkcs11_deleter_new (GckObject* object);
SeahorsePkcs11Deleter* seahorse_pkcs11_deleter_construct (GType object_type, GckObject* object);
#define SEAHORSE_PKCS11_NAME "pkcs11"
SeahorsePkcs11PrivateKey* seahorse_pkcs11_private_key_new (void);
SeahorsePkcs11PrivateKey* seahorse_pkcs11_private_key_construct (GType object_type);
SeahorsePkcs11Token* seahorse_pkcs11_private_key_get_place (SeahorsePkcs11PrivateKey* self);
void seahorse_pkcs11_private_key_set_place (SeahorsePkcs11PrivateKey* self, SeahorsePkcs11Token* value);
SeahorseFlags seahorse_pkcs11_private_key_get_object_flags (SeahorsePkcs11PrivateKey* self);
GtkActionGroup* seahorse_pkcs11_private_key_get_actions (SeahorsePkcs11PrivateKey* self);
SeahorsePkcs11Certificate* seahorse_pkcs11_private_key_get_partner (SeahorsePkcs11PrivateKey* self);
void seahorse_pkcs11_private_key_set_partner (SeahorsePkcs11PrivateKey* self, SeahorsePkcs11Certificate* value);
gchar* seahorse_pkcs11_private_key_get_label (SeahorsePkcs11PrivateKey* self);
gchar* seahorse_pkcs11_private_key_get_markup (SeahorsePkcs11PrivateKey* self);
const gchar* seahorse_pkcs11_private_key_get_description (SeahorsePkcs11PrivateKey* self);
GIcon* seahorse_pkcs11_private_key_get_icon (SeahorsePkcs11PrivateKey* self);
GType seahorse_pkcs11_properties_get_type (void) G_GNUC_CONST;
SeahorsePkcs11Properties* seahorse_pkcs11_properties_new (GckObject* object, GtkWindow* window);
SeahorsePkcs11Properties* seahorse_pkcs11_properties_construct (GType object_type, GckObject* object, GtkWindow* window);
GckObject* seahorse_pkcs11_properties_get_object (SeahorsePkcs11Properties* self);
GType seahorse_pkcs11_request_get_type (void) G_GNUC_CONST;
void seahorse_pkcs11_request_prompt (GtkWindow* parent, GckObject* private_key);
SeahorsePkcs11Request* seahorse_pkcs11_request_new (void);
SeahorsePkcs11Request* seahorse_pkcs11_request_construct (GType object_type);
SeahorsePkcs11PrivateKey* seahorse_pkcs11_request_get_private_key (SeahorsePkcs11Request* self);
SeahorsePkcs11Token* seahorse_pkcs11_token_new (GckSlot* slot);
SeahorsePkcs11Token* seahorse_pkcs11_token_construct (GType object_type, GckSlot* slot);
gboolean seahorse_pkcs11_token_is_deletable (SeahorsePkcs11Token* self, GckObject* object);
void seahorse_pkcs11_token_remove_object (SeahorsePkcs11Token* self, GckObject* object);
gboolean seahorse_pkcs11_token_has_mechanism (SeahorsePkcs11Token* self, gulong mechanism);
GckTokenInfo* seahorse_pkcs11_token_get_info (SeahorsePkcs11Token* self);
GckSession* seahorse_pkcs11_token_get_session (SeahorsePkcs11Token* self);
void seahorse_pkcs11_token_set_session (SeahorsePkcs11Token* self, GckSession* value);
GckSlot* seahorse_pkcs11_token_get_slot (SeahorsePkcs11Token* self);
SeahorseFlags seahorse_pkcs11_token_get_object_flags (SeahorsePkcs11Token* self);
GArray* seahorse_pkcs11_token_get_mechanisms (SeahorsePkcs11Token* self);


G_END_DECLS

#endif
