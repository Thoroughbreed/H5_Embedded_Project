#include "Climate/climate.h"
#include "Shared/Logging/log.h"

int hysterese = 3;

// Livingroom
String getTempLivingroom(DHT* dhtLivingroom)
{
  String Temp = "Temp livinroom = ";
  Temp +=  String(dhtLivingroom->readTemperature());
  return Temp;
}


void checkLivingroomTemp(int setLivingroomTemp, DHT* dhtLivingroom)
{
  if (dhtLivingroom->readTemperature() < (setLivingroomTemp - hysterese))
  {
    logInfo("climate", "Livingroom: temp to cold turning on head");
  }
  if (dhtLivingroom->readTemperature() > (setLivingroomTemp + hysterese))
  {
    logInfo("climate", "Livingroom: temp to hot, opening windows");
    setMyservo(20);
  }
  if (dhtLivingroom->readTemperature() > (setLivingroomTemp - hysterese) && dhtLivingroom->readTemperature() < (setLivingroomTemp + hysterese))
  {
    logInfo("climate", "Livingroom: temp is OK");
  }
  
}


// Kitchen
String getTempKitchen(DHT* dhtKitchen)
{
  String Temp = "Temp kitchen = ";
  Temp +=  String(dhtKitchen->readTemperature());
  return Temp;
}

void checkKitchenTemp(int setKitchenTemp, DHT* dhtKitchen)
{
  if (dhtKitchen->readTemperature() < (setKitchenTemp - hysterese))
  {
    logInfo("climate", "Kitchen: temp to cold turning on head");
  }
  if (dhtKitchen->readTemperature() > (setKitchenTemp + hysterese))
  {
    logInfo("climate", "Kitchen: temp to hot, opening windows");
    setMyservo(20);
  }
  if (dhtKitchen->readTemperature() > (setKitchenTemp - hysterese) && dhtKitchen->readTemperature() < (setKitchenTemp + hysterese))
  {
    logInfo("climate", "Kitchen: temp is OK");
  }
  
}



// Bedroom
String getTempBedroom(DHT* dhtBedroom)
{
  String Temp = "Temp bedroom = ";
  Temp +=  String(dhtBedroom->readTemperature());
  return Temp;
}


void checkBedroomTemp(int setBedroomTemp, DHT* dhtBedroom)
{
  if (dhtBedroom->readTemperature() < (setBedroomTemp - hysterese))
  {
    logInfo("climate", "Bedroom: temp to cold turning on head");
  }
  if (dhtBedroom->readTemperature() > (setBedroomTemp + hysterese))
  {
    logInfo("climate", "Bedroom: temp to hot, opening windows");
    setMyservo(20);
  }
  if (dhtBedroom->readTemperature() > (setBedroomTemp - hysterese) && dhtBedroom->readTemperature() < (setBedroomTemp + hysterese))
  {
    logInfo("climate", "Bedroom: temp is OK");
  }
  
}

