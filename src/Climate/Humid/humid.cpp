#include "Climate/climate.h"

// Livingroom
String getHumidLivingroom(DHT* dhtLivingroom)
{
  String Humid = "Humid livingroom = ";
  Humid += String(dhtLivingroom->readHumidity());
  return Humid;
}


// Kitchen
String getHumidKitchen(DHT* dhtKitchen)
{
  String Humid = "Humid kitchen = ";
  Humid += String(dhtKitchen->readHumidity());
  return Humid;
}


// Bedroom
String getHumidBedroom(DHT* dhtBedroom)
{
  String Humid = "Humid bedroom = ";
  Humid += String(dhtBedroom->readHumidity());
  return Humid;
}