#include "alarm.h"

void setupAlarm() {
    setupRGB();
}

void loopAlarm() {
    delay(1000);
    setRGB(255, 0, 0);
    delay(1000);
    setRGB(0, 0, 0);
}