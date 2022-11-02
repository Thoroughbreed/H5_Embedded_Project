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
void setupTemp();
void setupHumid();
void loopClimate();
void onMessageReceived(String& topic, String& payload);

String getTempLivingroom(DHT* dhtLivingroom);
String getHumidLivingroom(DHT* dhtLivingroom);
String getTempKitchen(DHT* dhtKitchen);
String getHumidKitchen(DHT* dhtKitchen);
String getTempBedroom(DHT* dhtBedroom);
String getHumidBedroom(DHT* dhtBedroom);

String getMQ2();

void checkLivingroomTemp(int setLivingroomTemp, DHT* dhtLivingroom);
void checkKitchenTemp(int setKitchenTemp, DHT* dhtKitchen);
void checkBedroomTemp(int setBedroomTemp, DHT* dhtBedroom);

void checkLivingroomHumid(int setLivingroomHunid, DHT* dhtLivingroom);
void checkKitchenHumid(int setKitchenHumid, DHT* dhtKitchen);
void checkBedroomHumid(int setBedroomHumid, DHT* dhtBedroom);
