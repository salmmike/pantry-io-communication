#include <stdio.h>
#include <mosquitto.h>
#include <string.h>

int main(){
    int rc;
    struct mosquitto * mosq;

    mosquitto_lib_init();

    mosq = mosquitto_new("pantry-io-test-publisher", true, NULL);

    rc = mosquitto_connect(mosq, "localhost", 1883, 60);
    if(rc != 0){
        printf("Broker connection error: %d\n", rc);
        mosquitto_destroy(mosq);
        return -1;
    }

    const char* payload = "0=0,1=0,2=1,3=0,4=0,5=0";

    mosquitto_publish(mosq,
                      NULL,
                      "pantry-io/testdeviceid/item-changed",
                      (unsigned int) strlen(payload),
                      payload,
                      0,
                      false);

    mosquitto_disconnect(mosq);
    mosquitto_destroy(mosq);

    mosquitto_lib_cleanup();
    return 0;
}
