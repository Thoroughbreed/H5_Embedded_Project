#ifndef H5_EMBEDDED_PROJECT_MQTT_H
#define H5_EMBEDDED_PROJECT_MQTT_H

#include <MQTT.h>

#define MQTT_USERNAME "ardui"
#define MQTT_PASSWORD "s1hif-xp!sT-qCuwu"
#define MQTT_BROKER_ADDRESS "62.66.208.26"

bool setupMQTT(char* clientId, MQTTClientCallbackSimpleFunction messageReceivedCallback);

#endif