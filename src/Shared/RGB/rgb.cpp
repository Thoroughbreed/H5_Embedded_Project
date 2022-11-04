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

void ledRed() {
    setRGB(255, 0, 0);
}
void ledGreen() {
    setRGB(0, 255, 0);
}
void ledBlue() {
    setRGB(0, 0, 255);
}

void ledWhite() {
    setRGB(255, 255, 255);
}
void ledOff() {
    setRGB(0, 0, 0);
}

void flashWhite(int delayInMs) {
    for (size_t i = 0; i < 3; i++) {
        delay(delayInMs);
        ledWhite();
        delay(delayInMs);
        ledOff();
    }
}