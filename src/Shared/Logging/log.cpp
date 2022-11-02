#include "log.h"
extern MQTTClient mqttClient;

void log(const char* endpoint, const char* logLevel, const char* message) {
    String logTopic = String(MQTT_LOG_BASE_TOPIC) + logLevel + "/" + endpoint;
    mqttClient.publish(logTopic, message);
}

void logDebug(const char* endpoint, const char* message) {
    log(endpoint, "debug", message);
}
void logInfo(const char* endpoint, const char* message) {
    log(endpoint, "info", message);
}
void logCritical(const char* endpoint, const char* message) {
    log(endpoint, "critical", message);
}