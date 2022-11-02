#include "climate.h"

extern MQTTClient mqttClient;
extern WiFiClient wifiClient;

DHT dhtLivingroom(DHTPIN2livingroom, DHTTYPE);
DHT dhtKitchen(DHTPIN3kitchen, DHTTYPE);
DHT dhtBedroom(DHTPIN4Bedroom, DHTTYPE);

unsigned long lastMillis = 0;

int setKitchenTemp = 24;
int setKitchenHumid = 50;
int setLivingroomTemp = 24;
int setLivingroomHunid = 50;
int setBedroomTemp = 24;
int setBedroomHumid = 50;


void setupClimate()
{
  Serial.begin(9600);

  setupWiFi();
  char clientId[] = "House_Cilmate";
  setupMQTT(clientId, onMessageReceived);

#pragma region Subscribtions

  mqttClient.subscribe("home/climate/servo");
  mqttClient.subscribe("home/alarm/arm");
  // SetKitchen
  mqttClient.subscribe("home/climate/kitchen/settemp");
  mqttClient.subscribe("home/climate/kitchen/sethumid");
  // SetLivingroom
  mqttClient.subscribe("home/climate/livingroom/settemp");
  mqttClient.subscribe("home/climate/livingroom/sethumid");
  // SetBedroom
  mqttClient.subscribe("home/climate/bedroom/settemp");
  mqttClient.subscribe("home/climate/bedroom/sethumid");

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

    // Check Temp
    checkLivingroomTemp(setLivingroomTemp, &dhtLivingroom);
    checkKitchenTemp(setKitchenTemp, &dhtKitchen);
    checkBedroomTemp(setBedroomTemp, &dhtBedroom);
    // Check Humid
    checkLivingroomHumid(setLivingroomHunid, &dhtLivingroom);
    checkKitchenHumid(setKitchenHumid, &dhtKitchen);
    checkBedroomHumid(setBedroomHumid, &dhtBedroom);

    // Chcek Air
    checkLivingroomHumid();

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
  if (topic == "home/alarm/arm")
  {
    if (payload == "1" || payload == "2")
    {
      alarmOnServoClose();
    }
    else 
    {
      alarmoff();
    } 
  }

  // kitchen
  if (topic == "home/climate/kitchen/settemp")
  {
    setKitchenTemp = payload.toInt();
  }
  if (topic == "home/climate/kitchen/sethumid")
  {
    setKitchenHumid = payload.toInt();
  }

  // livingroom
  if (topic == "home/climate/livingroom/settemp")
  {
    setLivingroomTemp = payload.toInt();
  }
  if (topic == "home/climate/livingroom/sethumid")
  {
    setLivingroomHunid = payload.toInt();
  }

  // bedroom
  if (topic == "home/climate/bedroom/settemp")
  {
    setBedroomTemp = payload.toInt();
  }
  if (topic == "home/climate/bedroom/sethumid")
  {
    setBedroomHumid = payload.toInt();
  }
}




