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

/**
 * @brief represents a bluetooth device found nearby.
 */
struct pio_bluetooth_device
{
    char* name;
    char* address;
};

void
pio_print_bluetooth_devices(struct pio_bluetooth_device** devices);

void
pio_free_bluetooth_devices(struct pio_bluetooth_device** devices);

/**
 * @brief represents communicator bluetooth connection.
 */
struct pio_bluetooth_connection
{
    int dd;
    int dev_id;
};

/**
 * @brief init bluetooth connections.
 * @return non-zero value on error.
 */
int
pio_bluetooth_init(struct pio_bluetooth_connection** conn);

/**
 * @brief close down bluetooth connections.
 * @return non-zero value on error.
 * @param dd the hci device descriptor.
 */
int
pio_bluetooth_deinit(struct pio_bluetooth_connection** conn);

/**
 * @brief Scan for nearby bluetooth devices.
 * Caller must free the returned array.
 * @param dd the hci device descriptor.
 * @return a NULL terminated array of pio_bluetooth_device*
 * or NULL if no devices are found.
 */
struct pio_bluetooth_device**
pio_scan_bt_devices(struct pio_bluetooth_connection* conn);

/**
 * @brief Share wifi network info with a pantry-io sensor device.
 * @return non-zero return value on failure.
 * @param device pio_bluetooth_device* with info of the device to share the wifi credentials.
 * @param dd the hci device descriptor.
 */
int
pio_share_wifi_credentials(struct pio_bluetooth_connection* conn,
                           struct pio_bluetooth_device* device);
