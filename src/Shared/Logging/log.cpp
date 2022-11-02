#include "log.h"
extern MQTTClient mqttClient;

void log(const char* endpoint, const char* logLevel, const char* message, bool retain, int qos) {
    String logTopic = String(MQTT_LOG_BASE_TOPIC) + logLevel + "/" + endpoint;
    mqttClient.publish(logTopic, message, retain, qos);
}

void logDebug(const char* endpoint, const char* message) {
    log(endpoint, "debug", message, false, 0);
}
void logInfo(const char* endpoint, const char* message) {
    log(endpoint, "info", message, true, 1);
}
void logCritical(const char* endpoint, const char* message) {
    log(endpoint, "critical", message, true, 2);
}