#include "Climate/climate.h"


// Livingroom
String getTempLivingroom(DHT* dhtLivingroom)
{
  String Temp = "Temp livinroom = ";
  Temp +=  String(dhtLivingroom->readTemperature());
  return Temp;
}


// Kitchen
String getTempKitchen(DHT* dhtKitchen)
{
  String Temp = "Temp kitchen = ";
  Temp +=  String(dhtKitchen->readTemperature());
  return Temp;
}


// Bedroom
String getTempBedroom(DHT* dhtBedroom)
{
  String Temp = "Temp bedroom = ";
  Temp +=  String(dhtBedroom->readTemperature());
  return Temp;
}