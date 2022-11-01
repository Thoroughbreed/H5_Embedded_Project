#include <DHT.h>

#include "Shared/RGB/rgb.h"
#include "Shared/WiFi/wifi.h"
#include "Shared/Servo/myservo.h"
#include "Shared/MQTT/mqtt.h"
#include "Shared/WiFi/wifi.h"

#define DHTPIN 2
#define DHTTYPE DHT11

void setupClimate();
void loopClimate();
void onMessageReceived(String& topic, String& payload);
