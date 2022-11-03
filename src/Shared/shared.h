#ifndef H5_EMBEDDED_PROJECT_SHARED_H
#define H5_EMBEDDED_PROJECT_SHARED_H

#include <WiFiNINA.h>
#include <WiFiUdp.h>
#include "../../.pio/libdeps/mkrwifi1010/NTPClient/NTPClient.h"

/************************* NTP client *********************************/
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

/************************* Reset board! ********************************/
void(* resetFunc) (void) = 0;

#endif