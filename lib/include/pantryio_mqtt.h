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

#include <mosquitto.h>

/**
 * @brief Starts the pantry-io MQTT subscriber.
 * @param mosq struct mosquitto** where the mosquitto client is initialized.
 * @return non-zero value on failure.
 */
int
pio_init_mqtt_subscriber(struct mosquitto** mosq);

/**
 * @brief Stops the pantry-io MQTT subscriber.
 * @param mosq the mosquitto struct used with init_mqtt_subscriber
 */
void
pio_mqtt_stop(struct mosquitto* mosq);

/**
 * @brief parse sender id from topic.
 * @param topic The topic
 * @return const char* with sender ID. Returns NULL if unsuccessful.
 * Caller should free the return value.
 */
const char*
pio_mqtt_parse_sender_id(const char* topic);
