#include <utility/wifi_drv.h>

#define RGB_GREEN_PIN 25
#define RGB_RED_PIN 26
#define RGB_BLUE_PIN 27

void setRGB(byte r, byte g, byte b);
void setupRGB();

void ledRed();
void ledGreen();
void ledBlue();

void ledWhite();
void ledOff();

void flashWhite(int delayInMs);