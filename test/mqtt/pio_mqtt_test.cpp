
#include <gtest/gtest.h>
#include <cassert>

extern "C" {
    #include "pantryio_mqtt.h"
}

#define NAME pio_mqtt_unittest
#define TESTID "testdeviceid123"

TEST(NAME, test_parse_id)
{
    const char* topic = "pantry-io/" TESTID "/test";
    const char* sender_id = pio_mqtt_parse_sender_id(topic);
    ASSERT_EQ(strcmp(sender_id, TESTID), 0) << "Sender id: " << sender_id;
}

TEST(NAME, test_init_mqtt)
{
    struct mosquitto* mosq;
    ASSERT_EQ(pio_init_mqtt_subscriber(&mosq), 0);
    pio_mqtt_stop(mosq);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
