#include <Arduino.h>
#include <Adafruit_GFX.h>
#include "Climate/climate.h"

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  setupClimate();
}

void loop() {
  // put your main code here, to run repeatedly:
  loopClimate();
}