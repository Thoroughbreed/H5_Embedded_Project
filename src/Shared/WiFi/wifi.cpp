#include "wifi.h"

WiFiClient wifiClient;

void setupWiFi() {
  Serial.print("WiFi: Connecting...");
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("\nWiFi: Connected!");
}