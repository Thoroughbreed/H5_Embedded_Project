#include "reed.h"

void setupREED() {
    pinMode(REED_PIN, INPUT_PULLUP);
}
bool checkREED() {
    bool result = digitalRead(REED_PIN);
    if (result) logCritical("alarm", "Alarm: Alarm triggered by a door being opened!");
    return result;
}