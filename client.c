#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include "minminbus.h"

int main()
{
	MinMinBusGDBUS *proxy;
	GError *error;
	gchar **buf;

	error = NULL;
	proxy = min_min_bus_gdbus_proxy_new_for_bus_sync(G_BUS_TYPE_SESSION, G_DBUS_PROXY_FLAGS_NONE,
			"com.fatminmin", "/com/fatminmin/GDBUS", NULL, &error);

	min_min_bus_gdbus_call_hello_world_sync(proxy, "fatminmin", buf, NULL, &error);
	g_print("resp: %s\n", *buf);

	g_object_unref(proxy);
	return 0;
}
