#include "pantryio_bluetooth.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>

#define MAX_BT_NAME_LEN 255
#define MAX_BT_ADDRESS_LEN 20

void
pio_print_bluetooth_devices(struct pio_bluetooth_device **devices)
{
    if (devices == NULL) {
        return;
    }

    size_t i = 0;
    while (devices[i] != NULL)
    {
        printf("name: %s, address: %s\n", devices[i]->name, devices[i]->address);
        i++;
    }
}


struct pio_bluetooth_device*
pio_new_bluetooth_device(const char *name, const char *addr)
{
    struct pio_bluetooth_device* device = malloc(sizeof(struct pio_bluetooth_device));
    device->address = calloc((strnlen(addr, MAX_BT_ADDRESS_LEN) + 1), sizeof(char));
    device->name = calloc((strnlen(name, MAX_BT_NAME_LEN) + 1), sizeof(char));
    strcpy(device->name, name);
    strcpy(device->address, addr);

    return device;
}

void
pio_free_bluetooth_device(struct pio_bluetooth_device *device)
{
    free(device->name);
    free(device->address);
    free(device);
}

void
pio_free_bluetooth_devices(struct pio_bluetooth_device **devices)
{
    if (devices == NULL) {
        return;
    }

    int i = 0;
    while (devices[i] != NULL)
    {
        pio_free_bluetooth_device(devices[i]);
        ++i;
    }
    free(devices);
}

int
pio_bluetooth_init(struct pio_bluetooth_connection **conn)
{
    int dev_id;
    int dd_tmp;

    *conn = malloc(sizeof(struct pio_bluetooth_connection));

    (*conn)->dd = 0;
    dev_id = hci_get_route(NULL);
    if (dev_id < 0) {
        perror("Failed to get HCI route\n");
        return dev_id;
    }

    dd_tmp = hci_open_dev(dev_id);
    if (dd_tmp < 0) {
        perror("Failed to open HCI device\n");
        return dd_tmp;
    }
    (*conn)->dd = dd_tmp;
    (*conn)->dev_id = dev_id;
    return 0;
}

int
pio_bluetooth_deinit(struct pio_bluetooth_connection** conn)
{
    int rc = 0;
    if (*conn != NULL) {
        rc = close((*conn)->dd);
    }
    free(*conn);
    *conn = NULL;
    return rc;
}

struct pio_bluetooth_device**
pio_scan_bt_devices(struct pio_bluetooth_connection* conn)
{
    int len;
    int max_rsp;
    int num_rsp;
    int flags;
    inquiry_info *ii;
    char addr[19] = {0};
    char name[248] = {0};
    struct pio_bluetooth_device** found_devices;

    len  = 8;
    max_rsp = 255;
    flags = IREQ_CACHE_FLUSH;

    ii = (inquiry_info*) malloc(max_rsp * sizeof(inquiry_info));

    if ((num_rsp = hci_inquiry(conn->dev_id, len, max_rsp, NULL, &ii, flags)) < 0) {
        printf("hci_inquiry failed: %d\n", num_rsp);
        free(ii);
        return NULL;
    }

    found_devices = malloc(sizeof(struct pio_bluetooth_device*) * (num_rsp + 1));
    found_devices[num_rsp] = NULL;

    for (int i = 0; i < num_rsp; i++) {
        ba2str(&ii[i].bdaddr, addr);
        memset(name, 0, sizeof(name));

        if (hci_read_remote_name(conn->dd, &ii[i].bdaddr, sizeof(name), name, 0) < 0) {
            strcpy(name, "[unknown]");
        }

        struct pio_bluetooth_device* found_device = pio_new_bluetooth_device(name, addr);
        found_devices[i] = found_device;
    }

    free(ii);
    return found_devices;
}
