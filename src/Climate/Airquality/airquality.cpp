#include "Climate/climate.h"
#include "Shared/Logging/log.h"

int airqualityMax = 400;

String getMQ2()
{
	int ppm = analogRead(AIR);
  return String(ppm);
}


void checkLivingroomHumid()
{
  int ppm = analogRead(AIR);
  if (ppm >= airqualityMax)
  {
    logCritical("climate", "AirQuality: AirQuality too bad Run");
    setMyservo(50);
  }

  
}

