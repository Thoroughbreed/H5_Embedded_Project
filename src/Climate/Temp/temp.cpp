#include "Climate/climate.h"
#include "Shared/Logging/log.h"

int hysteresetemp = 3;

// Livingroom
String getTempLivingroom(DHT* dhtLivingroom)
{
  String Temp = String(dhtLivingroom->readTemperature());
  return Temp;
}


void checkLivingroomTemp(int setLivingroomTemp, DHT* dhtLivingroom)
{
  if (dhtLivingroom->readTemperature() < (setLivingroomTemp - hysteresetemp))
  {
    logInfo("climate", "Livingroom: temp to cold turning on head");
  }
  if (dhtLivingroom->readTemperature() > (setLivingroomTemp + hysteresetemp))
  {
    logInfo("climate", "Livingroom: temp to hot, opening windows");
    setMyservo(50);
  }
  if (dhtLivingroom->readTemperature() > (setLivingroomTemp - hysteresetemp) && dhtLivingroom->readTemperature() < (setLivingroomTemp + hysteresetemp))
  {
    logDebug("climate", "Livingroom: temp is OK");
  }
  
}


// Kitchen
String getTempKitchen(DHT* dhtKitchen)
{
  String Temp = String(dhtKitchen->readTemperature());
  return Temp;
}

void checkKitchenTemp(int setKitchenTemp, DHT* dhtKitchen)
{
  if (dhtKitchen->readTemperature() < (setKitchenTemp - hysteresetemp))
  {
    logInfo("climate", "Kitchen: temp to cold turning on head");
  }
  if (dhtKitchen->readTemperature() > (setKitchenTemp + hysteresetemp))
  {
    logInfo("climate", "Kitchen: temp to hot, opening windows");
    setMyservo(50);
  }
  if (dhtKitchen->readTemperature() > (setKitchenTemp - hysteresetemp) && dhtKitchen->readTemperature() < (setKitchenTemp + hysteresetemp))
  {
    logDebug("climate", "Kitchen: temp is OK");
  }
  
}



// Bedroom
String getTempBedroom(DHT* dhtBedroom)
{
  String Temp = String(dhtBedroom->readTemperature());
  return Temp;
}


void checkBedroomTemp(int setBedroomTemp, DHT* dhtBedroom)
{
  if (dhtBedroom->readTemperature() < (setBedroomTemp - hysteresetemp))
  {
    logInfo("climate", "Bedroom: temp to cold turning on head");
  }
  if (dhtBedroom->readTemperature() > (setBedroomTemp + hysteresetemp))
  {
    logInfo("climate", "Bedroom: temp to hot, opening windows");
    setMyservo(50);
  }
  if (dhtBedroom->readTemperature() > (setBedroomTemp - hysteresetemp) && dhtBedroom->readTemperature() < (setBedroomTemp + hysteresetemp))
  {
    logDebug("climate", "Bedroom: temp is OK");
  }
  
}

