#ifndef __RESOURCE_seahorse_H__
#define __RESOURCE_seahorse_H__

#include <gio/gio.h>

extern GResource *seahorse_get_resource (void);

extern void seahorse_register_resource (void);
extern void seahorse_unregister_resource (void);

#endif
