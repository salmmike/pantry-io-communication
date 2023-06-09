/*
* Copyright (c) 2023 Mike Salmela
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/

#include "pantryio_dbus_server.h"

/***** STATIC ******/
static GDBusNodeInfo *introspection_data = NULL;

static const gchar introspection_xml[] =
    "<node>"
    "  <interface name='" PIO_DBUS_SERVER_INTERFACE_NAME "'>"
    "    <method name='" PIO_GET_STATUS_METHOD "'>"
    "      <arg type='s' name='currentData' direction='out'/>"
    "    </method>"
    "    <signal name='" PIO_DATA_CHANGED_SIGNAL "'>"
    "      <arg type='s' name='currentData' direction='out'/>"
    "    </signal>"
    "  </interface>"
    "</node>";


/**
 * @brief Handle Pantry-io-communications DBus interface communication.
 */
static void
handle_method_call (G_GNUC_UNUSED
                    GDBusConnection       *connection,
                    G_GNUC_UNUSED
                    const gchar           *sender,
                    const gchar           *object_path,
                    const gchar           *PIO_DBUS_SERVER_interface_name,
                    const gchar           *method_name,
                    GVariant              *parameters,
                    GDBusMethodInvocation *invocation,
                    gpointer               user_data)
{
    GError *error;
    error = NULL;
    gboolean ret;

    if (g_strcmp0(method_name, "GetStatus") == 0) {
        gchar *response = "abc=1,123=0,cdef=0,longstring item with space=1";
        g_dbus_method_invocation_return_value(invocation,
                                              g_variant_new("(s)", response));
    }
}

static const GDBusInterfaceVTable interface_vtable =
{
    handle_method_call,
    NULL,
    NULL,
    { 0 }
};

static void
connection_closed (G_GNUC_UNUSED
                   GDBusConnection *connection,
                   gboolean remote_peer_vanished,
                   GError *Error,
                   gpointer user_data)
{
    g_print ("Client disconnected.\n");
    g_object_unref (connection);
}

static gboolean
on_new_connection (GDBusServer *server,
                   GDBusConnection *connection,
                   gpointer user_data)
{
    guint registration_id;
    g_object_ref(connection);
    g_signal_connect(connection, "closed", G_CALLBACK (connection_closed), NULL);
    registration_id = g_dbus_connection_register_object(connection,
                                                        PIO_DBUS_SERVER_OBJECT_PATH,
                                                        introspection_data->interfaces[0],
                                                        &interface_vtable,
                                                        NULL,  /* user_data */
                                                        NULL,  /* user_data_free_func */
                                                        NULL); /* GError** */
    g_assert (registration_id > 0);
    return TRUE;
}


static gboolean
allow_mechanism_cb(GDBusAuthObserver *observer,
                   const gchar *mechanism,
                   G_GNUC_UNUSED gpointer user_data)
{
    return TRUE;
}


static gboolean
authorize_authenticated_peer_cb (GDBusAuthObserver *observer,
                                 G_GNUC_UNUSED GIOStream *stream,
                                 GCredentials *credentials,
                                 G_GNUC_UNUSED gpointer user_data)
{
    gboolean authorized = FALSE;

    if (credentials != NULL) {
        GCredentials *own_credentials;
        gchar *credentials_string = NULL;

        credentials_string = g_credentials_to_string(credentials);
        g_print ("Peer's credentials: %s\n", credentials_string);
        g_free (credentials_string);

        own_credentials = g_credentials_new ();

        credentials_string = g_credentials_to_string(own_credentials);
        g_print("Server's credentials: %s\n", credentials_string);
        g_free(credentials_string);

        if (g_credentials_is_same_user(credentials, own_credentials, NULL))
            authorized = TRUE;

        g_object_unref (own_credentials);
    }

    return authorized;
}

/***** PUBLIC ******/

void
pio_emit_data_changed_signal(const char* data)
{
        gboolean ret;
        GDBusConnection* connection;
        GError* error;
        error = NULL;

        connection = g_bus_get_sync(G_BUS_TYPE_SESSION, NULL, &error);
        if (error != NULL) {
            g_printerr("Failed to get bus connection: %s\n", error->message);
            g_error_free(error);
            return;
        }

        ret = g_dbus_connection_emit_signal(connection,
                                            NULL,
                                            PIO_DBUS_SERVER_OBJECT_PATH,
                                            PIO_DBUS_SERVER_INTERFACE_NAME,
                                            PIO_DATA_CHANGED_SIGNAL,
                                            g_variant_new("(s)", data),
                                            &error);
        if (error != NULL) {
            g_printerr("Error emitting signal: %s\n", error->message);
            g_error_free(error);
        }
}

GDBusServer*
pio_create_dbus_server()
{
    gint ret;
    GError *error;

    introspection_data = g_dbus_node_info_new_for_xml(introspection_xml, &error);
    g_assert(introspection_data != NULL);

    GDBusAuthObserver *observer;
    GDBusServer *server;
    gchar *guid;
    GDBusServerFlags server_flags;

    guid = g_dbus_generate_guid();

    server_flags = G_DBUS_SERVER_FLAGS_NONE;

    observer = g_dbus_auth_observer_new();
    g_signal_connect(observer, "allow-mechanism", G_CALLBACK (allow_mechanism_cb), NULL);
    g_signal_connect(observer, "authorize-authenticated-peer", G_CALLBACK (authorize_authenticated_peer_cb), NULL);

    error = NULL;
    server = g_dbus_server_new_sync(PIO_UNIX_ADDRESS,
                                    server_flags,
                                    guid,
                                    observer,
                                    NULL, /* GCancellable */
                                    &error);
    g_dbus_server_start(server);

    g_object_unref(observer);
    g_free(guid);

    if (server == NULL) {
        g_printerr("Error creating server at address %s: %s\n", PIO_UNIX_ADDRESS, error->message);
        g_error_free(error);
    }
    g_print("Server is listening at: %s\n", g_dbus_server_get_client_address(server));
    g_signal_connect(server,
                     "new-connection",
                     G_CALLBACK (on_new_connection),
                     NULL);
    return server;
}
