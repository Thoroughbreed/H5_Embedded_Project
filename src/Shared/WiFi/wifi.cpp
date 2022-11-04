#include "wifi.h"

const char ssid[] = SECRET_SSID;
const char pass[] = SECRET_PASS;

WiFiClient wifiClient;

bool setupWiFi() {
  int retry = 5;
  ledRed();
  Serial.print("WiFi: Connecting...");
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
    retry--;

    if (retry <= 0) {
      Serial.println("\nWiFi: Connection failed");
      return false;
    }
  }

  Serial.println("\nWiFi: Connected!");
  return true;
}