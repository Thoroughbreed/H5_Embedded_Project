
#include "../Shared/RGB/rgb.h"
#include <DHT.h>
#include <SPI.h>
#include <WiFiNINA.h>
#include <MQTT.h>
#include <utility/wifi_drv.h>    
#include <Servo.h>
#include "Shared/WiFi/wifi.h"

#define DHTPIN 2
#define DHTTYPE DHT11

void setupClimate();
void loopClimate();
void connect();
void messageReceived(String &topic, String &payload);
void LedGreen();
void LedRed();
void LedBlue();
void LedFlashWithe();
void LedWhite();
void LedOff();
