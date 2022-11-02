#include "../MQTT/mqtt.h"

#define MQTT_LOG_BASE_TOPIC "home/log/"

void logDebug(const char* endpoint, const char* message);
void logInfo(const char* endpoint, const char* message);
void logCritical(const char* endpoint, const char* message);