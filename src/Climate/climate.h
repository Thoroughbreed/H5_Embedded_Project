#include <DHT.h>

#include "Shared/RGB/rgb.h"
#include "Shared/WiFi/wifi.h"
#include "Servo/myservo.h"
#include "Shared/MQTT/mqtt.h"
#include "Shared/WiFi/wifi.h"

#define DHTPIN2livingroom 2
#define DHTPIN3kitchen 3
#define DHTPIN4Bedroom 4
#define DHTTYPE DHT11
#define AIR A1

void setupClimate();
void loopClimate();
void onMessageReceived(String& topic, String& payload);
String getTempLivingroom();
String getHumidLivingroom();
String getTempKitchen();
String getHumidKitchen();
String getTempBedroom();
String getHumidBedroom();
String getMQ2();
void checkClimate(int setclimate);
