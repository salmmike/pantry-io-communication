
#include <gtest/gtest.h>
#include <cassert>

extern "C" {
    #include "pantryio_bluetooth.h"
}

#define NAME pio_bluetooth_unittest

TEST(NAME, test_find_devices)
{
    struct pio_bluetooth_connection *conn;
    struct pio_bluetooth_device** devices;

    ASSERT_EQ(pio_bluetooth_init(&conn), 0);

    devices = pio_scan_bt_devices(conn);

    pio_print_bluetooth_devices(devices);

    pio_free_bluetooth_devices(devices);

    pio_bluetooth_deinit(&conn);
}

TEST(NAME, test_create_device)
{
    struct pio_bluetooth_device* device = pio_new_bluetooth_device("testdevice", "testaddr");
    ASSERT_EQ(strcmp(device->name, "testdevice"), 0);
    ASSERT_EQ(strcmp(device->address, "testaddr"), 0);

    pio_free_bluetooth_device(device);
}

TEST(NAME, test_create_devices)
{
    struct pio_bluetooth_device** devices = (pio_bluetooth_device**) malloc(sizeof(struct pio_bluetooth_device*) * 2);

    struct pio_bluetooth_device* device = pio_new_bluetooth_device("testdevice", "testaddr");
    devices[0] = device;
    devices[1] = NULL;

    pio_free_bluetooth_devices(devices);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
