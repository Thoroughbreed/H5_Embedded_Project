
#ifndef H5_EMBEDDED_PROJECT_HOME_H
#define H5_EMBEDDED_PROJECT_HOME_H

#include "../../Shared/shared.h"           // Shared
#include "../../../.pio/libdeps/mkrwifi1010/Adafruit SSD1306/Adafruit_SSD1306.h"           // OLED
#include "../../../.pio/libdeps/mkrwifi1010/Servo/src/Servo.h"
#include "keypad.h"                     // Keypad
#include "../../Shared/WiFi/wifi.h"
#include "../../Shared/MQTT/mqtt.h"
#include "../../Shared/RGB/rgb.h"
#include "home_func.h"



/************************* Var & const *********************************/
Servo doorServo;
long delayOLED;
long delayPing;
long delayTime;
const int doorClosed = 0;
const int doorOpen = 90;
String messageToDisplay;
String logMessage = "";
bool ArmSystem = false;
bool ArmPerim = false;
bool incomingMessage = false;


/************************* External declarations *********************************/
extern WiFiClient wifiClient;
extern MQTTClient mqttClient;


/************************* Door opener (ping-dims) *********************************/
#define TRIGGER_PING 2           // TODO er den pin overhovedet ledig??
#define ECHO_PING 3              // TODO er den pin overhovedet ledig??
#define PULSE_WAIT 200000
#define DOORSERVO 4              // TODO er den pin overhovedet ledig??


/************************* Devices/classes *********************************/
// OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


/****************************** MQTT ***************************************/
#define CLIENTID "House_Controller"
#define ALARM_TOP "home/alarm/alarm"
#define ALARM_STAT "home/alarm/status"
#define HMI "home/input/#"
#define LOG "home/log"
#define CLIMATE_SUB "home/climate/#"


/************************* Func prototyping *********************************/
void initDisplay();             // OLED
void initWireless();            // Connects wifi
void initPing();
void initServo();

void initmqttSub(String topic);
void onMessageReceived(String& topic, String& payload);

void updateOLED(int interval, bool screensaver = true);
void printOLED(int x, int y, String text, int textSize = 1);

void mqttAlarmAction(String action);
void getTime(int interval = 36000000); // 1 hour
void pingDoors(int interval);
void actionDoor(bool open = false);


#endif