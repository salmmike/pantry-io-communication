#include <stdio.h>
#include <glib.h>
#include <gio/gio.h>
#include "pantryio_dbus_server.h"

int main()
{
    GDBusServer *server;
    GMainLoop *loop;

    server = pio_create_dbus_server();

    loop = g_main_loop_new (NULL, FALSE);
    g_main_loop_run(loop);

    g_object_unref(server);
    g_main_loop_unref(loop);
}
