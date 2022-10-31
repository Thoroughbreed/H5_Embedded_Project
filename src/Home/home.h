#include "../Shared/shared.h"           // Shared
#include <SPI.h>                        // SPI
#include <WiFiNINA.h>                   // WiFi
#include <utility/wifi_drv.h>           // RGB LED
#include <Wire.h>                       // I2C
#include <Adafruit_GFX.h>               // OLED
#include <Adafruit_SSD1306.h>           // OLED
#include "Adafruit_MQTT.h"              // MQTT
#include "Adafruit_MQTT_Client.h"       // MQTT



/************************* Var & const *********************************/
String messageToDisplay;    // Message for OLED
long delayOLED;
WiFiClient client;          // Wireless client

/************************* Brooker Setup *********************************/
#define MQTT_SERVER      "62.66.208.26"
#define MQTT_SERVERPORT  1883                   // use 8883 for SSL
#define MQTT_USERNAME    "ardui"
#define MQTT_PWD         "s1hif-xp!sT-qCuwu"
#define MQTT_CLIENTID    "House_HomeController"

/************************* Devices/classes *********************************/
// OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// MQTT
Adafruit_MQTT_Client mqtt(&client, MQTT_SERVER, MQTT_SERVERPORT, MQTT_CLIENTID, MQTT_USERNAME, MQTT_PWD);
/****************************** Feeds ***************************************/
// PUB
Adafruit_MQTT_Publish alarmStatus = Adafruit_MQTT_Publish(&mqtt, "home/alarm/status");
Adafruit_MQTT_Publish alarmAlarm = Adafruit_MQTT_Publish(&mqtt, "home/alarm/alarm");
Adafruit_MQTT_Publish log = Adafruit_MQTT_Publish(&mqtt, "home/log");

// SUB
Adafruit_MQTT_Subscribe climate = Adafruit_MQTT_Subscribe(&mqtt, "home/climate/#");
Adafruit_MQTT_Subscribe alarm = Adafruit_MQTT_Subscribe(&mqtt, "home/alarm/#");
Adafruit_MQTT_Subscribe log = Adafruit_MQTT_Subscribe(&mqtt, "home/log/#");
Adafruit_MQTT_Subscribe HMI = Adafruit_MQTT_Subscribe(&mqtt, "home/input/#");