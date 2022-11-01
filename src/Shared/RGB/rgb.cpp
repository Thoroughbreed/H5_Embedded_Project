#include "rgb.h"

void setRGB(byte r, byte g, byte b) {
    WiFiDrv::analogWrite(RGB_RED_PIN, r);
    WiFiDrv::analogWrite(RGB_GREEN_PIN, g);
    WiFiDrv::analogWrite(RGB_BLUE_PIN, b);
}
void setupRGB() {
    pinMode(RGB_BLUE_PIN, OUTPUT);
    pinMode(RGB_GREEN_PIN, OUTPUT);
    pinMode(RGB_RED_PIN, OUTPUT);
}