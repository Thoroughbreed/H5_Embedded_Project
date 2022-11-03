#include "alarm.h"

extern MQTTClient mqttClient;

const char* clientId = MQTT_ALARM_CLIENT_ID;
int alarmArmedState = 0;
bool alarmActive = false;
unsigned long checkSensorMillis = 0;

void setupAlarm() {
    Serial.begin(9600);
    setupRGB();
    setupPIR();
    setupREED();
    
    setupConnectivity();
}
void loopAlarm() {
    mqttClient.loop();
    ensureConnectivity();

    if (alarmArmedState == ALARM_DISARMED) return;
    if (alarmActive) return;

    if (millis() - checkSensorMillis > ALARM_SENSOR_CHECK_INTERVAL) {
        checkSensorMillis = millis();
        checkSensors();
    }
}

void setupConnectivity() {
    mqttClient.setWill("home/log/system", "Alarm system disconnected", false, 1);

    while (!setupWiFi());
    while (!setupMQTT((char*)clientId, onMessageReceived));
    mqttClient.subscribe(MQTT_ARM_TOPIC);
}
void ensureConnectivity() {
    if (WiFi.status() == WL_CONNECTED) return;
    if (mqttClient.connected()) return;

    setupConnectivity();
}

void checkSensors() {
    bool anyMovementOutDoors = false;
    bool anyMovementInDoors = false;
    bool doorOpened = checkREED();

    anyMovementOutDoors = checkOutDoorPIR();
    if (alarmArmedState == ALARM_FULLY_ARMED) {
        anyMovementInDoors = checkInDoorPIR();
    }

    if (anyMovementOutDoors || anyMovementInDoors || doorOpened) activateAlarm();
}

void activateAlarm() {
    alarmActive = true;
    mqttClient.publish(MQTT_ACTIVATE_ALARM_TOPIC, "1", true, 2);
}
void deactivateAlarm() {
    alarmActive = false;
    mqttClient.publish(MQTT_ACTIVATE_ALARM_TOPIC, "0", true, 1);
}
void setArmed(String payload) {
    if (payload.toInt() == ALARM_DISARMED) {
        setRGB(0, 255, 0);
        alarmArmedState = 0;
    } else if (payload.toInt() == ALARM_PARTIALLY_ARMED) {
        setRGB(255, 255, 0);
        alarmArmedState = 1;
    } else if (payload.toInt() == ALARM_FULLY_ARMED) {
        setRGB(255, 0, 0);
        alarmArmedState = 2;
    }
}

void onMessageReceived(String &topic, String &payload) {
    Serial.println("Incoming: " + topic + " Payload: " + payload);
    if (topic == MQTT_ARM_TOPIC) {
        if (alarmActive && payload.toInt() == ALARM_DISARMED) {
            deactivateAlarm();
        }

        setArmed(payload);
    }
}