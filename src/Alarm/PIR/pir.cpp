#include "pir.h"

const byte inDoorsPirPins[] = { 6 };
const byte outDoorsPirPins[] = { 5 };

void setupPIR() {
    for (int pin : inDoorsPirPins) {
        pinMode(pin, INPUT);
    }
    for (int pin : outDoorsPirPins) {
        pinMode(pin, INPUT);
    }
}
bool checkOutDoorPIR() {
    for (int pin : outDoorsPirPins) {
        bool result = digitalRead(pin);
        if (result) return true;
    }
    return false;
}
bool checkInDoorPIR() {
    for (int pin : inDoorsPirPins) {
        bool result = digitalRead(pin);
        if (result) return true;
    }

    return false;
}