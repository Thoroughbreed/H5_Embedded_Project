#include "../Shared/RGB/rgb.h"
#include "../Shared/WiFi/wifi.h"
#include "../Shared/MQTT/mqtt.h"
#include "../Shared/Logging/log.h"
#include "PIR/pir.h"
#include "REED/reed.h"

#define MQTT_ALARM_CLIENT_ID "House_Alarm"
#define MQTT_ARM_TOPIC "home/alarm/arm"
#define MQTT_ACTIVATE_ALARM_TOPIC "home/alarm/alarm"

#define ALARM_DISARMED 0
#define ALARM_PARTIALLY_ARMED 1
#define ALARM_FULLY_ARMED 2

#define ALARM_SENSOR_CHECK_INTERVAL 1000

void setupAlarm();
void loopAlarm();

void setupConnectivity();
void ensureConnectivity();

void setArmed(String payload);
void activateAlarm();
void deactivateAlarm();

void checkSensors();

void onMessageReceived(String &topic, String &payload);