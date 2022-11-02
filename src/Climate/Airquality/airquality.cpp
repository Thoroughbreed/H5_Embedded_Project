#include "Climate/climate.h"

String getMQ2()
{
	int ppm = analogRead(AIR);
  return String(ppm);
}

