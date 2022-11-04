#include <Adafruit_GFX.h>
#include "Home/headers/home_func.h"

void setup() {
  Serial.begin(9600);
  setupHome();
  // put your setup code here, to run once:
}

void loop() {
    homeLoop();
  // put your main code here, to run repeatedly:
}
