#include "pantryio_bluetooth.h"
#include <stdio.h>
#include <stdlib.h>

void test_find_devices()
{
    struct pio_bluetooth_connection *conn;
    struct pio_bluetooth_device** devices;

    printf("create connection\n");
    pio_bluetooth_init(&conn);

    printf("Scan devices\n");
    devices = pio_scan_bt_devices(conn);

    printf("Print devices\n");
    pio_print_bluetooth_devices(devices);

    printf("free devices\n");
    pio_free_bluetooth_devices(devices);

    printf("deinit bt\n");
    pio_bluetooth_deinit(&conn);
}

void test_create_device()
{
    printf("Try creating a new device\n");
    struct pio_bluetooth_device* device = pio_new_bluetooth_device("testdevice", "testaddr");
    printf("Try freeing device\n");
    pio_free_bluetooth_device(device);
    printf("Success\n");
}

void test_create_devices()
{
    struct pio_bluetooth_device** devices = malloc(sizeof(struct pio_bluetooth_device*) * 2);

    printf("Try creating a new device\n");
    struct pio_bluetooth_device* device = pio_new_bluetooth_device("testdevice", "testaddr");
    printf("Creating a device worked\n");
    devices[0] = device;
    devices[1] = NULL;

    pio_free_bluetooth_devices(devices);
    printf("Freeing device array worked\n");
}

int main()
{
    test_create_device();
    test_create_devices();
    test_find_devices();
    return 0;
}