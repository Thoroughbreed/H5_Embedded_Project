#include <WiFiNINA.h>
#include <WiFiUdp.h>
#include "../../.pio/libdeps/mkrwifi1010/NTPClient/NTPClient.h"


/************************* WiFi Access Point *********************************/
#define WLAN_SSID       "SibirienAP"
#define WLAN_PASS       "Siberia51244"

/************************* NTP cluent *********************************/
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

/************************* Var & const *********************************/
long delayTime;
String messageToDisplay;    // Message for OLED