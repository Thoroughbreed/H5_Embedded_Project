//
// Created by Jan Andreasen on 01/11/2022.
//

#include "Home/headers/home.h"

#pragma region Initialization

void initDisplay()
{
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    {
        Serial.println(F("OLED allocation failed"));
        for(;;);
    }
}

void initWireless()
{
    printOLED(0, 0, "Connecting to:", 1);
    printOLED(0, 10, SECRET_SSID, 2);
    display.display();
    WiFi.begin(SECRET_SSID, SECRET_PASS);
    int i = 0;
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        display.setCursor(i*2, 20);
        display.write(".");
        display.display();
        i++;
        if (i == 50) resetFunc();
    }
    display.clearDisplay();
    printOLED(0, 0, "WiFi connected!");
    printOLED(0, 30, timeClient.getFormattedTime());
    display.display();
    delay(1000);
}

void initPing()
{
    pinMode(TRIGGER_PING, OUTPUT);
    pinMode(ECHO_PING, INPUT);
}

void initServo()
{
    doorServo.attach(DOORSERVO);
}

void initmqttSub(String topic)
{
    mqttClient.subscribe(topic);
}

void setupHome()
{
    Serial.begin(9600);
    setupRGB();
    ledRed();
    initDisplay();
    display.clearDisplay();
    delay(10);
    timeClient.begin();
    initWireless();
    getTime(0);
    timeClient.setTimeOffset(3600);
    if (!setupMQTT(CLIENTID, onMessageReceived))
    {
        while(true)
        {
            display.clearDisplay();
            printOLED(0, 0, "Conecting to MQTT ...");
            printOLED(0, 10, "Retrying MQTT conn.");
            printOLED(0, 20, "MQTT conn. dead");
            printOLED(0, 30, timeClient.getFormattedTime());
            printOLED(0, 40, "Check settings!");
            display.display();
            delay(999);
        }
    }
    initmqttSub(ALARM_TOP);
    initPing();
    initServo();
}

#pragma endregion

#pragma region OLED

void printOLED(int x, int y, String text, int textSize)
{
    display.setTextSize(textSize);
    display.setTextColor(WHITE);
    display.setCursor(x, y);
    display.println(text);
}

void updateOLED(int interval)
{
    if ((millis() - delayOLED) > interval)
    {
        delayOLED = millis();
        display.clearDisplay();
        printOLED(0, 0, messageToDisplay, 2);
        printOLED(0, 55, timeClient.getFormattedTime());
        display.display();
    }
}

#pragma endregion

#pragma region MQTT

void onMessageReceived(String& topic, String& payload)
{
    if (topic == ALARM_TOP)
    {
        // TODO Do something!
        // Alarm halløj
        messageToDisplay = payload;
        Serial.println(messageToDisplay);
        flashWhite(75);
    }
    if (topic == CLIMATE_SUB)
    {
        // TODO Do something!
        // Klima halløj
        messageToDisplay = payload;
        Serial.println(messageToDisplay);
        flashWhite(75);
    }
    if (topic == LOG)
    {
        // TODO Do something!
        // Vis log
        messageToDisplay = payload;
        Serial.println(messageToDisplay);
        flashWhite(75);
    }
    if (topic == HMI)
    {
        // TODO Do something!
        // Gør noget!
        messageToDisplay = payload;
        Serial.println(messageToDisplay);
        flashWhite(75);
    }
}

#pragma endregion

#pragma region Misc functions

void getTime(int interval)
{
    if ((millis() - delayTime) > interval)
    {
        delayTime = millis();
        timeClient.update();
    }
}

void pingDoors(int interval)
{
    long duration;
    int distance;

    if ((millis() - delayPing) > interval)
    {
        digitalWrite(TRIGGER_PING, false);
        delayMicroseconds(2);
        digitalWrite(TRIGGER_PING, true);
        delayMicroseconds(10);
        digitalWrite(TRIGGER_PING, false);

        duration = pulseIn(ECHO_PING, true, PULSE_WAIT);
        distance = duration/58;
        if (distance < 15)  { actionDoor(true); }
        else if (distance > 30) { actionDoor(); }
        delayPing = millis();
    }
}

void actionDoor(bool open)
{
    if (open) { doorServo.write(doorOpen); }
    else { doorServo.write(doorClosed); }
}

#pragma endregion

#pragma region Keypad and entry

void checkPassword(char key)
{
    if (pwdCount <= 3)
    {
        pwdTest[pwdCount] = key;
        pwdCount++;
    }
    else
    {
        pwdCount = 0;
    }
}

void keyIn()
{
    char key = '1';//keypad.getKey();
    switch (key)
    {
        case 'A':
            // TODO
            break;
        case 'B':
            // TODO
            break;
        case 'C':
            // TODO
            break;
        case 'D':
            // TODO
            break;
        case '#':
            pwdCount = 0;
            if (comparePassword(pwdTest))
            {
                // TODO Unlock
            }
            else
            {
                // TODO Lock
            }
            break;
        case '*':
            // TODO
            break;
        default:
            checkPassword(key);
            break;
    }
}

bool comparePassword(char pw[])
{
    if (pwdTest[0] == pwd[0] && pwdTest[1] == pwd[1] && pwdTest[2] == pwd[2] && pwdTest[3] == pwd[3])
    {
        pwdTest[0] = 0;
        return true;
    }
    return false;
}

#pragma endregion

//void loop()
//{
//    updateOLED(500);
//    getTime(); // Default is 1 time
//    mqttConnect();
//    mqttSub();
//    keyIn();
//}