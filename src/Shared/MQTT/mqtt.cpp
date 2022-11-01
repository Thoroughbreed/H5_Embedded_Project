#include "mqtt.h"
#include "../WiFi/wifi.h"

extern WiFiClient wifiClient;
MQTTClient mqttClient;
u_int8_t retries = 5;

bool setupMQTT(char* clientId, MQTTClientCallbackSimpleFunction messageReceivedCallback) {
  ledBlue();
  Serial.print("\nMQTT: Connecting...");

  mqttClient.begin(MQTT_BROKER_ADDRESS, wifiClient);
  mqttClient.onMessage(messageReceivedCallback);

  while (!mqttClient.connect(clientId, MQTT_USERNAME, MQTT_PASSWORD))
  {
    Serial.println("Trying to connect to broker");
    delay(2500);
    retries--;
    if (retries == 0) return false;
  }

  Serial.println("\nMQTT: Connected!");
  ledGreen();
  return true;
}