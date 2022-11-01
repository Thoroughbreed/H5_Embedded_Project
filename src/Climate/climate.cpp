#include "climate.h"

extern MQTTClient mqttClient;
DHT dht(DHTPIN, DHTTYPE);

unsigned long lastMillis = 0;

extern WiFiClient wifiClient;

void setupClimate()
{
  Serial.begin(9600);
  while (!Serial);

  setupWiFi();
  char clientId[] = "House_Cilmate";
  setupMQTT(clientId, onMessageReceived);

  mqttClient.subscribe("home/climate/servo");
  mqttClient.subscribe("home/climate/status/test");
  dht.begin();

}

void loopClimate()
{
  // publish a message roughly every second.
  if (millis() - lastMillis > 5000) {
    lastMillis = millis();
    String Temp = String(dht.readTemperature());
    String Humid = String(dht.readHumidity());
    String Climate = "Temp = ";
    Climate += Temp; 
    Climate += " Humid = ";
    Climate += Humid;
    mqttClient.publish("home/climate/status/test", Climate);
    Serial.println(Climate);
  }
}



void onMessageReceived(String& topic, String& payload) {
  Serial.println("Incoming: " + topic + " Payload: " + payload);
}


