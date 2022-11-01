#include "mqtt.h"
#include "../WiFi/wifi.h"

extern WiFiClient wifiClient;
MQTTClient mqttClient;

void setupMQTT(char* clientId, MQTTClientCallbackSimpleFunction messageReceivedCallback) {
  Serial.print("\nMQTT: Connecting...");

  mqttClient.begin(MQTT_BROKER_ADDRESS, wifiClient);
  mqttClient.onMessage(messageReceivedCallback);

  while (!mqttClient.connect(clientId, MQTT_USERNAME, MQTT_PASSWORD)) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nMQTT: Connected!");
}