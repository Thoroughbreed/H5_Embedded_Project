#include "climate.h"

extern MQTTClient mqttClient;
extern WiFiClient wifiClient;

DHT dhtLivingroom(DHTPIN2livingroom, DHTTYPE);
DHT dhtKitchen(DHTPIN3kitchen, DHTTYPE);
DHT dhtBedroom(DHTPIN4Bedroom, DHTTYPE);

unsigned long lastMillis = 0;

int hysterase = 3;
int airqualityMax = 400;
int kitchenTemp;
int kitchenHumid;
int livingroomTemp;
int livingroomHunid;
int bedroomTemp;
int bedroomHumid;
int airquality;


void setupClimate()
{
  Serial.begin(9600);
  while (!Serial);

  setupWiFi();
  char clientId[] = "House_Cilmate";
  setupMQTT(clientId, onMessageReceived);

#pragma region Subscribtions

  mqttClient.subscribe("home/climate/servo");
  mqttClient.subscribe("home/alarm/status");
  // SetKitchen
  mqttClient.subscribe("home/climate/kitchen/settemp");
  mqttClient.subscribe("home/climate/kitchen/sethumid");
  // SetLivingroom
  mqttClient.subscribe("home/climate/livingroom/settemp");
  mqttClient.subscribe("home/climate/livingroom/sethumid");
  // SetBedroom
  mqttClient.subscribe("home/climate/bedroom/settemp");
  mqttClient.subscribe("home/climate/bedroom/sethumid");

  mqttClient.subscribe("home/climate/airquality/setairquality");

#pragma endregion

  dhtLivingroom.begin();
  dhtKitchen.begin();
  dhtBedroom.begin();
  setupMyservo();

}

void loopClimate()
{
  mqttClient.loop();

#pragma region Publish component data

  if (millis() - lastMillis > 20000) {
    lastMillis = millis();
    //livingroom
    mqttClient.publish("home/climate/status/livingroom/temp", getTempLivingroom(&dhtLivingroom));
    mqttClient.publish("home/climate/status/livingroom/humid", getHumidLivingroom(&dhtLivingroom));
    //kithcen
    mqttClient.publish("home/climate/status/kitchen/temp", getTempKitchen(&dhtKitchen));
    mqttClient.publish("home/climate/status/kitchen/humid", getHumidKitchen(&dhtKitchen));
    //bedroom
    mqttClient.publish("home/climate/status/bedroom/temp", getTempBedroom(&dhtBedroom));
    mqttClient.publish("home/climate/status/bedroom/humid", getHumidBedroom(&dhtBedroom));
    // Airquality
    mqttClient.publish("home/climate/status/airquality", getMQ2());

  }
#pragma endregion

}



void onMessageReceived(String& topic, String& payload) {
  Serial.println("Incoming: " + topic + " Payload: " + payload);

  // servo
  if(topic == "home/climate/servo")
  {
    setMyservo(payload.toInt());
  }

  // alarm
  if (topic == "home/alarm/status")
  {
    if (payload == "1" || payload == "2")
    {
      alarmOnServoClose();
    }
  }

  // kitchen
  if (topic == "home/climate/kitchen/settemp")
  {
    kitchenTemp = payload.toInt();
  }
  if (topic == "home/climate/kitchen/sethumid")
  {
    kitchenHumid = payload.toInt();
  }

  // livingroom
  if (topic == "home/climate/livingroom/settemp")
  {
    livingroomTemp = payload.toInt();
  }
  if (topic == "home/climate/livingroom/sethumid")
  {
    livingroomHunid = payload.toInt();
  }

  // bedroom
  if (topic == "home/climate/bedroom/settemp")
  {
    bedroomTemp = payload.toInt();
  }
  if (topic == "home/climate/bedroom/sethumid")
  {
    bedroomHumid = payload.toInt();
  }

  // airquality
  if (topic == "home/climate/airquality/setairquality")
  {
    airquality = payload.toInt();
  }
}




