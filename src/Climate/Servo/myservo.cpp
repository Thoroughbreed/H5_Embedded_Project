#include "myservo.h"

Servo myservo;

void setupMyservo() {
  myservo.attach(servoPin);
}

void setMyservo(int servoAngel) {
  myservo.write(servoAngel);
}