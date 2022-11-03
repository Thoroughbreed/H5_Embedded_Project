#include <Arduino.h>
#include <Adafruit_GFX.h>

#ifndef HOME_HEADER
#define HOME_HEADER
#include "Home/headers/home_func.h"
#endif

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
    setupHome();
}

void loop() {
    homeLoop();
    // put your main code here, to run repeatedly:
}