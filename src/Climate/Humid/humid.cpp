#include "Climate/climate.h"
#include "Shared/Logging/log.h"

int hysterese = 10;

// Livingroom
String getHumidLivingroom(DHT* dhtLivingroom)
{
  String Humid = String(dhtLivingroom->readHumidity());
  return Humid;
}

void checkLivingroomHumid(int setLivingroomHunid, DHT* dhtLivingroom)
{
  if (dhtLivingroom->readHumidity() < (setLivingroomHunid - hysterese))
  {
    logInfo("climate", "Livingroom: Humid to low turning on humidifyer");
  }
  if (dhtLivingroom->readHumidity() > (setLivingroomHunid + hysterese))
  {
    logInfo("climate", "Livingroom: humid to high, opening windows");
    setMyservo(30);
  }
  if (dhtLivingroom->readHumidity() > (setLivingroomHunid - hysterese) && dhtLivingroom->readTemperature() < (setLivingroomHunid + hysterese))
  {
    logDebug("climate", "Livingroom: humid is OK");
  }
  
}


// Kitchen
String getHumidKitchen(DHT* dhtKitchen)
{
  String Humid = String(dhtKitchen->readHumidity());
  return Humid;
}

void checkKitchenHumid(int setKitchenHumid, DHT* dhtKitchen)
{
  if (dhtKitchen->readHumidity() < (setKitchenHumid - hysterese))
  {
    logInfo("climate", "Kitchen: Humid to low turning on humidifyer");
  }
  if (dhtKitchen->readHumidity() > (setKitchenHumid + hysterese))
  {
    logInfo("climate", "Kitchen: humid to high, opening windows");
    setMyservo(30);
  }
  if (dhtKitchen->readHumidity() > (setKitchenHumid - hysterese) && dhtKitchen->readTemperature() < (setKitchenHumid + hysterese))
  {
    logDebug("climate", "Kitchen: humid is OK");
  }
  
}


// Bedroom
String getHumidBedroom(DHT* dhtBedroom)
{
  String Humid = String(dhtBedroom->readHumidity());
  return Humid;
}

void checkBedroomHumid(int setBedroomHumid, DHT* dhtBedroom)
{
  if (dhtBedroom->readHumidity() < (setBedroomHumid - hysterese))
  {
    logInfo("climate", "Bedroom: Humid to low turning on humidifyer");
  }
  if (dhtBedroom->readHumidity() > (setBedroomHumid + hysterese))
  {
    logInfo("climate", "Bedroom: humid to high, opening windows");
    setMyservo(30);
    
  }
  if (dhtBedroom->readHumidity() > (setBedroomHumid - hysterese) && dhtBedroom->readTemperature() < (setBedroomHumid + hysterese))
  {
    logDebug("climate", "Bedroom: humid is OK");
  }
  
}

