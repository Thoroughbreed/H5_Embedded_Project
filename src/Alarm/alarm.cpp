#include "alarm.h"

const char* clientId = MQTT_ALARM_CLIENT_ID;
extern MQTTClient mqttClient;
int alarmArmedState = 0;
unsigned long checkSensorMillis = 0;

void setupAlarm() {
    Serial.begin(9600);
    setupRGB();
    
    while (!setupWiFi());
    while (!setupMQTT((char*)clientId, onMessageReceived));
    mqttClient.subscribe(MQTT_ARM_TOPIC);
}

void loopAlarm() {
    mqttClient.loop();
    if (alarmArmedState == ALARM_DISARMED) return;

    if (millis() - checkSensorMillis > 5000) {
        checkSensorMillis = millis();
        checkSensors();
    }
}

void checkSensors() {
    checkPIR();
    if (alarmArmedState == ALARM_FULLY_ARMED) {
        checkMagnet();
    }
}
void checkPIR() {

}
void checkMagnet() {
    
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
        setArmed(payload);
    }
}