#include "../Shared/RGB/rgb.h"
#include "../Shared/WiFi/wifi.h"
#include "../Shared/MQTT/mqtt.h"
#include "../Alarm/PIR/pir.h"

#define MQTT_ALARM_CLIENT_ID "House_Alarm"
#define MQTT_ARM_TOPIC "home/alarm/status"
#define MQTT_ACTIVATE_ALARM_TOPIC "home/alarm/alarm"

#define ALARM_DISARMED 0
#define ALARM_PARTIALLY_ARMED 1
#define ALARM_FULLY_ARMED 2

#define ALARM_SENSOR_CHECK_INTERVAL 1000

void setupAlarm();
void loopAlarm();
void setArmed(String payload);
void onMessageReceived(String &topic, String &payload);

bool checkMagnet();
void checkSensors();
void activateAlarm();