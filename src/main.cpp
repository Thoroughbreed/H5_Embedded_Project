#include <Arduino.h>
#include <Adafruit_GFX.h>
#include "Climate/climate.h"

void setup() {
  Serial.begin(9600);
  setupClimate();

}

void loop() {
  loopClimate();

}