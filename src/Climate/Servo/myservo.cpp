#include "myservo.h"
#include "Shared/Logging/log.h"

Servo myservo;
bool alarm = false;

void setupMyservo() {
  myservo.attach(servoPin);
}

void setMyservo(int servoAngel) {
  if (!alarm)
  {
      myservo.write(servoAngel);
  }
}

void alarmOnServoClose()
{
  alarm = true;
  myservo.write(0);
  logInfo("climate", "Servo: Closing All windows");
}

void alarmoff()
{
  alarm = false;
}