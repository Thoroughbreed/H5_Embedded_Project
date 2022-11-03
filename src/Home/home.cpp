//
// Created by Jan Andreasen on 01/11/2022.
//

#ifndef HOME_HEADER
#define HOME_HEADER
#include "Home/headers/home.h"
#endif

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
        display.setCursor(i*3, 20);
        display.write(".");
        display.display();
        i++;
        if (i == 25)
        {
            display.setCursor(0, 35);
            display.println("Resetting");
            display.display();
            initWireless();
        }
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
    pinMode(DOORSERVO, OUTPUT);
    doorServo.attach(DOORSERVO);
    doorServo.write(0);
}

void initMQTT()
{
    logMessage = "";
    critMessage = "";
    mqttClient.setWill(PUB_SYSTEM_SYSTEM, "Home controller lost connection!", false, 1);

    if (!setupMQTT(CLIENTID, onMessageReceivedHome))
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
    logInfo("home", "Home controller is connected ...");

    mqttClient.subscribe(ALARM_TOP);
    mqttClient.subscribe(SUB_SYSTEM_LOG);
    mqttClient.subscribe(ALARM_STAT);
    mqttClient.subscribe(SUB_SYSTEM_CRIT);
    mqttClient.subscribe(SUB_SYSTEM_SYSTEM);
}

void setupHome()
{
    Serial.begin(9600);
    initServo();
    setupRGB();
    ledRed();
    initDisplay();
    display.clearDisplay();
    delay(10);
    timeClient.begin();
    SPI.begin();
    mfrc522.PCD_Init();
    pinMode(RST_PIN, OUTPUT);
    initWireless();
    getTime(0);
    timeClient.setTimeOffset(3600);
    display.clearDisplay();
    printOLED(0, 0, "Connecting to");
    printOLED(0, 5, "mqtt broker ...");
    initMQTT();
    initPing();
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

void updateOLED(int interval, bool message)
{
    if ((millis() - delayOLED) > interval)
    {
        if (message)
        {
            while ((millis() - delayOLED) < 5000)
            {
                display.clearDisplay();
                printOLED(0, 0, messageToDisplay, 2);
                printOLED(0, 55, timeClient.getFormattedTime());
                display.display();
                keyIn();
            }
        }
        else
        {
            display.clearDisplay();
            printOLED(0, 0, "Connected", 2);
            if (alarmStatus == 0) printOLED(0, 15, "Disarmed", 2);
            if (alarmStatus == 1) printOLED(0, 15, "Perim. arm", 2);
            if (alarmStatus == 2) printOLED(0, 15, "Full arm", 2);
            printOLED(0, 50, timeClient.getFormattedTime(), 2);
            display.display();
        }
        delayOLED = millis();
        incomingMessage = false;
    }
}

#pragma endregion

#pragma region MQTT

void onMessageReceivedHome(String& topic, String& payload)
{
    if (topic == ALARM_TOP)
    {
        // Alarm halløj
        if (payload == "1")
        {
            messageToDisplay = "  ALARM!! ";
            incomingMessage = true;
            flashWhite(75);
        }
    }
    if (topic.startsWith("home/log/info"))
    {
        // Vis log
        logMessage = payload;
        flashWhite(25);
    }
    if (topic.startsWith("home/log/critical"))
    {
        // Vis critical log
        critMessage = payload;
        flashWhite(50);
    }
    if (topic.startsWith("home/log/system"))
    {
        critMessage = payload;
        flashWhite(100);
    }
    if (topic == ALARM_STAT)
    {
        if (payload == "0") // Disarmed
        {
            messageToDisplay = "Alarm disabled";
            alarmStatus = 0;
            incomingMessage = true;
            ArmPerim = false;
            ArmSystem = false;
            RFIDActive = false;
        }
        if (payload == "1") // Partial
        {
            messageToDisplay = "Perimeter Armed";
            alarmStatus = 1;
            incomingMessage = true;
            ArmPerim = true;
            ArmSystem = false;
            RFIDActive = true;
        }
        if (payload == "2") // Full
        {
            messageToDisplay = "Fully     Armed";
            alarmStatus = 2;
            incomingMessage = true;
            ArmPerim = false;
            ArmSystem = true;
            RFIDActive = true;
        }
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
    if (alarmStatus == 2) return;
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

void connectivityCheck()
{
    if (wifiClient.connected()) return;
    initWireless();
    initMQTT();
}

#pragma endregion

#pragma region Keypad and entry

void readChip()
{
    if (RFIDActive)
    {
        digitalWrite(RST_PIN, 1);
        ledRed();
    }
    if (!RFIDActive)
    {
        digitalWrite(RST_PIN, 0);
        ledBlue();
    }

    if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial())
    {
        delay(50);
        return;
    }
    String newUid = "";
    for (byte i = 0; i < mfrc522.uid.size; i++)
    {
        newUid += mfrc522.uid.uidByte[i] < 0x10 ? "0" : "";
        newUid += mfrc522.uid.uidByte[i], HEX;
    }
    if (newUid != uid)
    {
        String payload = "RFID UID: ";
        payload += newUid;
        uid = newUid;
        if (newUid == SECRET_RFID)
        {
            actionAlarm(0); // 0 Disables alarm
            messageToDisplay = "Welcome home :)";
            incomingMessage = true;
            uid = "";
            RFIDActive = false;
        }
        else
        {
            messageToDisplay = "ACCESS DENIED";
            incomingMessage = true;
            logInfo("home", "Wrong chip at front door");
        }
    }
}

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
    char key = keypad.getKey();
    if (key != NO_KEY)
    {
        switch (key)
        {
            case 'A':
                incomingMessage = true;
                messageToDisplay = "Press * to fully arm system";
                ArmPerim = false;
                ArmSystem = true;
                RFIDActive = true;
                break;
            case 'B':
                incomingMessage = true;
                messageToDisplay = "Press * to partiallyarm system";
                ArmSystem = false;
                ArmPerim = true;
                RFIDActive = true;
                break;
            case 'C':
                messageToDisplay = logMessage;
                incomingMessage = true;
                break;
            case 'D':
                messageToDisplay = critMessage;
                incomingMessage = true;
                break;
            case '#':
                pwdCount = 0;
                if (comparePassword())
                {
                    messageToDisplay = "Welcome   home :)";
                    actionAlarm(0);
                    incomingMessage = true;
                    RFIDActive = false;
                }
                else
                {
                    messageToDisplay = "ACCESS DENIED!";
                    incomingMessage = true;
                }
                break;
            case '*':
                if (ArmSystem)
                {
                    actionAlarm(2);
                    ArmSystem = false;
                }
                else if (ArmPerim)
                {
                    actionAlarm(1);
                    ArmPerim = false;
                }
                break;
            default:
                checkPassword(key);
                break;
        }
    }
}

bool comparePassword()
{
    if (pwdTest[0] == pwd[0] && pwdTest[1] == pwd[1] && pwdTest[2] == pwd[2] && pwdTest[3] == pwd[3])
    {
        pwdTest[0] = 0;
        logInfo("home", "Password OK");
        mqttClient.publish(ALARM_STAT, "0");
        logInfo("home", "Alarm disabled");
        RFIDActive = false;
        return true;
    }
    logCritical("home", "Wrong password at entry!");
    return false;
}

#pragma endregion

#pragma region Actions

void actionAlarm(int alarmStatus)
{
    String status = "";
    switch (alarmStatus)
    {
        case 0:
            status = "0";
            break;
        case 1:
            status = "1";
            RFIDActive = true;
            break;
        case 2:
            status = "2";
            RFIDActive = true;
            break;
    }
    if (status != "") mqttClient.publish(ALARM_STAT, status);
}

void actionDoor(bool open)
{
    if (open) { doorServo.write(doorOpen); }
    else { doorServo.write(doorClosed); }
}

#pragma endregion

void homeLoop()
{
    updateOLED(500, incomingMessage);
    pingDoors(2000);
    getTime(); // Default is 1 time
    keyIn();
    mqttClient.loop();
    readChip();
    connectivityCheck();
}