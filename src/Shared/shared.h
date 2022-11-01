#include <Arduino.h>
#include <WiFiNINA.h>
#include <NTPClient.h>
#include <WiFiUdp.h>


/************************* WiFi Access Point *********************************/
#define WLAN_SSID       "SibirienAP"
#define WLAN_PASS       "Siberia51244"

/************************* NTP cluent *********************************/
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

/************************* Var & const *********************************/
long delayTime;
// WiFiClient client;          // Wireless client