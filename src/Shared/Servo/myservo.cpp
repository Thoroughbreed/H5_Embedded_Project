#include "myservo.h"

Servo myservo;
extern MQTTClient mqttClient;

void onMessageReceived(String& topic, String& payload) {
  Serial.println("Incoming: " + topic + " Payload: " + payload);
  myservo.write(payload.toInt());
}

void setupMyservo() {
  Serial.begin(9600);
  while (!Serial);

  setupWiFi();
  char clientId[] = "House_Cilmate";
  setupMQTT(clientId, onMessageReceived);

  mqttClient.subscribe("home/climate/servo");
  myservo.attach(servoPin);
}

void loopMyservo() {
  mqttClient.loop();
}