#include <WiFiNINA.h>
#include "../secrets.h"
#include "../RGB/rgb.h"

const char ssid[] = SECRET_SSID;
const char pass[] = SECRET_PASS;

bool setupWiFi();