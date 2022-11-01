#include <WiFiNINA.h>
#include <WiFiUdp.h>
#include "../../.pio/libdeps/mkrwifi1010/NTPClient/NTPClient.h"

/************************* NTP cluent *********************************/
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

/************************* Reset board! ********************************/
void(* resetFunc) (void) = 0;