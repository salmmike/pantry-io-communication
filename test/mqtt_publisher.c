#include <stdio.h>
#include <mosquitto.h>

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
	mosquitto_publish(mosq, NULL, "pantry-io/asdf/item-changed", 6, "123", 0, false);

	mosquitto_disconnect(mosq);
	mosquitto_destroy(mosq);

	mosquitto_lib_cleanup();
	return 0;
}
