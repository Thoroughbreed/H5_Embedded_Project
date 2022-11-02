#include "Climate/climate.h"

DHT dhtLivingroom(DHTPIN2livingroom, DHTTYPE);
DHT dhtKitchen(DHTPIN3kitchen, DHTTYPE);
DHT dhtBedroom(DHTPIN4Bedroom, DHTTYPE);


void setupHumid()
{
  dhtLivingroom.begin();
  dhtKitchen.begin();
  dhtBedroom.begin();
}


String getHumidLivingroom()
{
  String Humid = "Humid livingroom = ";
  Humid += String(dhtLivingroom.readHumidity());
  return Humid;
}




String getHumidKitchen()
{
  String Humid = "Humid kitchen = ";
  Humid += String(dhtKitchen.readHumidity());
  return Humid;
}




String getHumidBedroom()
{
  String Humid = "Humid bedroom = ";
  Humid += String(dhtBedroom.readHumidity());
  return Humid;
}