#include "../Shared/shared.h"           // Shared
#include <SPI.h>                        // SPI
#include <utility/wifi_drv.h>           // RGB LED
#include <Wire.h>                       // I2C
#include <Adafruit_GFX.h>               // OLED
#include <Adafruit_SSD1306.h>           // OLED
#include "Adafruit_MQTT.h"              // MQTT
#include "Adafruit_MQTT_Client.h"       // MQTT
#include <Servo.h>                      // Run servos



/************************* Var & const *********************************/
String messageToDisplay;    // Message for OLED
Servo doorServo;
long delayOLED;
long delayPing;
const int doorClosed = 0;
const int doorOpen = 90;

/************************* Door opener (ping-dims) *********************************/
#define TRIGGER_PING 2           // TODO er den pin overhovedet ledig??
#define ECHO_PING 3              // TODO er den pin overhovedet ledig??
#define PULSE_WAIT 200000
#define DOORSERVO 4              // TODO er den pin overhovedet ledig??

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
Adafruit_MQTT_Publish pubLog = Adafruit_MQTT_Publish(&mqtt, "home/log");

// SUB
Adafruit_MQTT_Subscribe climate = Adafruit_MQTT_Subscribe(&mqtt, "home/climate/#");
Adafruit_MQTT_Subscribe alarm = Adafruit_MQTT_Subscribe(&mqtt, "home/alarm/#");
Adafruit_MQTT_Subscribe readLog = Adafruit_MQTT_Subscribe(&mqtt, "home/log/#");
Adafruit_MQTT_Subscribe HMI = Adafruit_MQTT_Subscribe(&mqtt, "home/input/#");

/************************* Func prototyping *********************************/
void initRGB();                 // Builtin RGB
void initDisplay();             // OLED
void initWireless();            // Connects wifi
void initPing();
void initServo();

void printOLED(int x, int y, String text, int textSize = 1);
void updateOLED(int interval);

void mqttConnect();
void mqttSub();
void mqttPub();

void getTime(int interval = 36000000); // 1 hour
void doPing(int interval);
void actionDoor(bool open = false);

void flashWhite(int interval);
void ledRed();
void ledGreen();
void ledBlue();