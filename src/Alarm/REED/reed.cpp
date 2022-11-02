#include "reed.h"

void setupREED() {
    pinMode(REED_PIN, INPUT_PULLUP);
}
bool checkREED() {
    return digitalRead(REED_PIN);
}