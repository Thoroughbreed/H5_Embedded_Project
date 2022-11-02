#include "climate.h"

extern MQTTClient mqttClient;
DHT dhtLivingroom(DHTPIN2livingroom, DHTTYPE);
DHT dhtKitchen(DHTPIN3kitchen, DHTTYPE);
DHT dhtBedroom(DHTPIN4Bedroom, DHTTYPE);

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
  //mqttClient.subscribe("home/alarm/status");
  //mqttClient.subscribe("home/climate/status/#");
  dhtLivingroom.begin();
  dhtKitchen.begin();
  dhtBedroom.begin();
  setupMyservo();

}

void loopClimate()
{
  mqttClient.loop();
  // publish a message roughly every second.
  if (millis() - lastMillis > 10000) {
    lastMillis = millis();
    //livingroom
    mqttClient.publish("home/climate/status/livingroom/temp", getTempLivingroom());
    mqttClient.publish("home/climate/status/livingroom/humid", getHumidLivingroom());
    delay(1000);
    //kithcen
    mqttClient.publish("home/climate/status/kitchen/temp", getTempKitchen());
    mqttClient.publish("home/climate/status/kitchen/humid", getHumidKitchen());
    delay(1000);
    //bedroom
    mqttClient.publish("home/climate/status/bedroom/temp", getTempBedroom());
    mqttClient.publish("home/climate/status/bedroom/humid", getHumidBedroom());
    delay(1000);
    mqttClient.publish("home/climate/status/Airquality", getMQ2());

  }
}



void onMessageReceived(String& topic, String& payload) {
  Serial.println("Incoming: " + topic + " Payload: " + payload);
  if(topic == "home/climate/servo")
  {
    setMyservo(payload.toInt());
  }
  if (topic == "home/alarm/status")
  {
    if (payload == "1" || payload == "2")
    {
      void alarmOnServoClose();
    }
  }
  
}


String getMQ2()
{
	int ppm = analogRead(AIR);
  return String(ppm);
}



// Livingroom
String getTempLivingroom()
{
  String Temp = "Temp livinroom = ";
  Temp +=  String(dhtLivingroom.readTemperature());
  return Temp;
}

String getHumidLivingroom()
{
  String Humid = "Humid livingroom = ";
  Humid += String(dhtLivingroom.readHumidity());
  return Humid;
}


// Kitchen
String getTempKitchen()
{
  String Temp = "Temp kitchen = ";
  Temp +=  String(dhtKitchen.readTemperature());
  return Temp;
}

String getHumidKitchen()
{
  String Humid = "Humid kitchen = ";
  Humid += String(dhtKitchen.readHumidity());
  return Humid;
}


// Bedroom
String getTempBedroom()
{
  String Temp = "Temp bedroom = ";
  Temp +=  String(dhtBedroom.readTemperature());
  return Temp;
}

String getHumidBedroom()
{
  String Humid = "Humid bedroom = ";
  Humid += String(dhtBedroom.readHumidity());
  return Humid;
}



