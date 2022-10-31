#include "Home/home.h"

#pragma region Initialization

void initRGB()
{
    WiFiDrv::pinMode(25, OUTPUT);
    WiFiDrv::pinMode(26, OUTPUT);
    WiFiDrv::pinMode(27, OUTPUT);
}

void initDisplay()
{
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    {
        Serial.println(F("OLED allocation failed"))
        for(;;);
    }
}

void initWireless()
{
    printOLED(0, 0, "Connecting to:", 1);
    printOLED(0, 10, WLAN_SSID, 2);
    display.display();
    WiFi.begin(WLAN_SSID, WLAN_PASS);
    int i = 0;
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        display.setCursor(i, 20);
        display.write(".");
        display.display();
        i++;
    }
    display.clearDisplay();
    printOLED(0, 0, "WiFi connected!");
    printOLED(0, 30, timeClient.getFormattedTime());
    display.display();
    delay(1000);
}

void setup()
{
    Serial.begin(9600);
    initRGB();
    ledRed();
    initDisplay();
    display.clearDisplay();
    delay(10);
    timeClient.begin();
    initWireless();
    getTime(0);
    mqtt.subscribe(&climate);
    mqtt.subscribe(&alarm);
    mqtt.subscribe(&log);
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

#pragma region MQTT pub/sub

void mqttConnect()
{
    int8_t ret;

    if (mqtt.connected())
    {
        ledGreen();
        return;
    }

    ledBlue();
    display.clearDisplay();
    printOLED(0, 0, "Conecting to MQTT ...");
    printOLED(0, 30, timeClient.getFormattedTime());
    display.display();

    uint8_t retries = 5;
    while ((ret = mqtt.connect()) != 0)
    {
        display.clearDisplay();
        printOLED(0, 0, "Connecting to MQTT ...");
        printOLED(0, 10, "Retying MQTT conn.");
        printOLED(0, 30, timeClient.getFormattedTime());
        display.display();
        mqtt.disconnect();
        delay(5000);
        retries--;
        if (retries == 0)
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
    }
    display.clearDisplay();
    printOLED(0, 0, "Conecting to MQTT ...");
    printOLED(0, 10, "MQTT connected!");
    display.display();
    Serial.println("MQTT Connected!");
    ledGreen();
    delay(1234);
}

void mqttSub()
{
    Adafruit_MQTT_Subscribe *subscription;
    while ((subscription = mqtt.readSubscription()))
    {

        if (subscription == &alarm)
        {
            // TODO Do something!
            // Alarm halløj
            messageToDisplay = (char *)alarm.lastread;
            Serial.println(messageToDisplay);
            flashWhite(75);
        }
        if (subscription == &climate)
        {
            // TODO Do something!
            // Klima halløj
            messageToDisplay = (char *)climate.lastread;
            Serial.println(messageToDisplay);
            flashWhite(75);
        }
        if (subscription == &log)
        {
            // TODO Do something!
            // Vis log
            // messageToDisplay = (char *)text.lastread;
            //        Serial.println(messageToDisplay);
            //        flashWhite(75);
        }
        if (subscription == &HMI)
        {
            // TODO Do something!
            // Gør noget!
        }
    }
}

#pragma endregion


void loop() {
  // put your main code here, to run repeatedly:
}