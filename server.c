#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include "minminbus.h"

static gboolean
on_handle_hello_world (MinMinBusGDBUS *interface, GDBusMethodInvocation *invocation,
					const gchar *greeting, gpointer user_data)
{
	gchar *response;
	response = g_strdup_printf ("Hello world %s!!.", greeting);
	min_min_bus_gdbus_complete_hello_world (interface, invocation, response);
	g_print("%s\n", response);
	g_free (response);
	return TRUE;
}

static void
on_name_acquired(GDBusConnection *connection, const gchar *name, gpointer user_data)
{
	MinMinBusGDBUS *interface;
	GError *error;

	interface = min_min_bus_gdbus_skeleton_new();
	g_signal_connect (interface, "handle-hello-world", G_CALLBACK (on_handle_hello_world), NULL);
	error = NULL;
	!g_dbus_interface_skeleton_export (G_DBUS_INTERFACE_SKELETON (interface), connection, "/com/fatminmin/GDBUS", &error);
}

int main()
{
	GMainLoop *loop;

	loop = g_main_loop_new (NULL, FALSE);

	g_bus_own_name(G_BUS_TYPE_SESSION, "com.fatminmin", G_BUS_NAME_OWNER_FLAGS_NONE, NULL,
				on_name_acquired, NULL, NULL, NULL);

	g_main_loop_run (loop);

	return 0;
}
