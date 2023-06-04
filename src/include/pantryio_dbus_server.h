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