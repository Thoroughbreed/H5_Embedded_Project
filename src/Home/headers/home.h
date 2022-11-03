
#ifndef H5_EMBEDDED_PROJECT_HOME_H
#define H5_EMBEDDED_PROJECT_HOME_H

#include "../../Shared/shared.h"           // Shared
#include "../../../.pio/libdeps/mkrwifi1010/Adafruit SSD1306/Adafruit_SSD1306.h"           // OLED
#include "../../../.pio/libdeps/mkrwifi1010/Servo/src/Servo.h"
#include "keypad.h"                     // Keypad
#include "../../../.pio/libdeps/mkrwifi1010/MFRC522/src/MFRC522.h"
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
String logMessage;
String critMessage;
bool ArmSystem = false;
bool ArmPerim = false;
bool RFIDActive = true;
bool incomingMessage = false;
uint8_t alarmStatus = 0;


/************************* External declarations *********************************/
extern WiFiClient wifiClient;
extern MQTTClient mqttClient;


/************************* Door opener (ping-dims) *********************************/
#define TRIGGER_PING 6
#define ECHO_PING 5
#define PULSE_WAIT 200000
#define DOORSERVO 14

/************************* NFC/RFID *********************************/
#define RST_PIN 7
#define SS_PIN 13
MFRC522 mfrc522(SS_PIN, RST_PIN);
MFRC522::MIFARE_Key key;
String uid;

/************************* OLED *********************************/
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


/****************************** MQTT ***************************************/
#define CLIENTID "House_Controller"
#define ALARM_TOP "home/alarm/alarm"
#define ALARM_STAT "home/alarm/arm"
#define SUB_SYSTEM_LOG "home/log/info/#"
#define SUB_SYSTEM_CRIT "home/log/critical/#"
#define PUB_SYSTEM_LOG "home/log/info/home"
#define PUB_SYSTEM_CRIT "home/log/critical/home"


/************************* Func prototyping *********************************/
void initDisplay();             // OLED
void initWireless();            // Connects wifi
void initMQTT();
void initPing();
void initServo();

void connectivityCheck();

void readChip();

//void initmqttSub(String topic);
void onMessageReceived(String& topic, String& payload);

void updateOLED(int interval, bool screensaver = true);
void printOLED(int x, int y, String text, int textSize = 1);

void getTime(int interval = 36000000); // 1 hour
void pingDoors(int interval);
void actionDoor(bool open = false);
void actionAlarm(int alarmStatus);


#endif