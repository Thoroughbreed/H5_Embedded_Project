#include <MQTT.h>

#define MQTT_USERNAME "ardui"
#define MQTT_PASSWORD "s1hif-xp!sT-qCuwu"
#define MQTT_BROKER_ADDRESS "62.66.208.26"

bool setupMQTT(char* clientId, MQTTClientCallbackSimpleFunction messageReceivedCallback);
