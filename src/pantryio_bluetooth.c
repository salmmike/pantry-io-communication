#include "pantryio_bluetooth.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>

int pio_bluetooth_init(int *dd)
{
    int dev_id;
    int dd_tmp;

    *dd = NULL;
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

    *dd = dd_tmp;
    return 0;
}
