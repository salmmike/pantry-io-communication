#include <stdio.h>
#include <glib.h>
#include <gio/gio.h>

#define PIO_DBUS_SERVER_OBJECT_PATH "/org/gtk/GDBus/PantryIOCommunicator"
#define PIO_DBUS_SERVER_INTERFACE_NAME "org.pantryio.GDBus.StatusInterface"
#define PIO_DATA_CHANGED_SIGNAL "PantryDataChanged"
#define PIO_GET_STATUS_METHOD "GetStatus"
#define PIO_UNIX_ADDRESS "unix:abstract=pantryiocommunication"

/**
 * @brief Emits the PantryDataChanged signal.
 * This should be called when ever the data changes.
 */
void
pio_emit_data_changed_signal(void);

/**
 * @brief Create the pantry-io-communicator DBus server.
 * The caller must call g_object_unref(server) when finished with the server.
 * @return GDBusServer* server
 */
GDBusServer*
pio_create_dbus_server();