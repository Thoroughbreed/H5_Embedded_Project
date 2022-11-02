#include "Climate/climate.h"

DHT dhtLivingroom(DHTPIN2livingroom, DHTTYPE);
DHT dhtKitchen(DHTPIN3kitchen, DHTTYPE);
DHT dhtBedroom(DHTPIN4Bedroom, DHTTYPE);

void setupTemp()
{
  dhtLivingroom.begin();
  dhtKitchen.begin();
  dhtBedroom.begin();
}


// Livingroom
String getTempLivingroom()
{
  String Temp = "Temp livinroom = ";
  Temp +=  String(dhtLivingroom.readTemperature());
  return Temp;
}


// Kitchen
String getTempKitchen()
{
  String Temp = "Temp kitchen = ";
  Temp +=  String(dhtKitchen.readTemperature());
  return Temp;
}


// Bedroom
String getTempBedroom()
{
  String Temp = "Temp bedroom = ";
  Temp +=  String(dhtBedroom.readTemperature());
  return Temp;
}