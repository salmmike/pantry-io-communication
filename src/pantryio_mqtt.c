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

#include "pantryio_mqtt.h"
#include "pantryio_dbus_server.h"

#include <stdio.h>

#define PIO_MQTT_SUBSCRIBER "pantry-io-mqtt-subscriber"

static void
connect_cb(struct mosquitto *mosq,
           void *obj,
           int rc)
{
    printf("ID: %d\n", * (int *) obj);
    if(rc) {
        printf("MQTT connection error: %d\n", rc);
        return;
    }
    mosquitto_subscribe(mosq, NULL, "pantry-io/+/+", 0);
}

static void
message_cb(struct mosquitto *mosq,
           void *obj,
           const struct mosquitto_message *msg)
{
    printf("Pantry-io MQTT message %s: %s\n", msg->topic, (char *) msg->payload);
    pio_emit_data_changed_signal(msg->payload);
}

int
pio_init_mqtt_subscriber(struct mosquitto** mosq)
{
    int rc;
    int id = 12;

    rc = mosquitto_lib_init();
    if (rc != MOSQ_ERR_SUCCESS) {
        printf("Mosquitto lib init failed: %d\n", rc);
    }

    *mosq = mosquitto_new(PIO_MQTT_SUBSCRIBER, true, &id);
    mosquitto_connect_callback_set(*mosq, connect_cb);
    mosquitto_message_callback_set(*mosq, message_cb);

    rc = mosquitto_connect(*mosq, "localhost", 1883, 10);
    if(rc) {
        printf("Connecting to broker failed: %d\n", rc);
        return -1;
	}

    mosquitto_loop_start(*mosq);
    return 0;
}

void
pio_mqtt_stop(struct mosquitto* mosq)
{
    mosquitto_loop_stop(mosq, true);
    mosquitto_disconnect(mosq);
    mosquitto_destroy(mosq);
    mosquitto_lib_cleanup();
}