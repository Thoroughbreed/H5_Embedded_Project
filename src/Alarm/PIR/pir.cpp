#include "pir.h"

void setupPIR() {
    pinMode(PIR_PIN, INPUT);
}
bool checkPIR() {
    return digitalRead(PIR_PIN);
}