#include "climate.h"

char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;

WiFiClient net;
MQTTClient client;
DHT dht(DHTPIN, DHTTYPE);
Servo myservo;

unsigned long lastMillis = 0;



void setupClimate()
{
    WiFiDrv::pinMode(25, OUTPUT); //Green
    WiFiDrv::pinMode(26, OUTPUT); //Red
    WiFiDrv::pinMode(27, OUTPUT); //Blue
    WiFi.begin(ssid, pass);

    client.begin("62.66.208.26", net);
    client.onMessage(messageReceived);

    connect();
    dht.begin();
    myservo.attach(3);

}


void loopClimate()
{
  client.loop();

  if (!client.connected()) {
    connect();
  }
  LedGreen();

  // publish a message roughly every second.
  if (millis() - lastMillis > 5000) {
    lastMillis = millis();
    String Temp = String(dht.readTemperature());
    String Humid = String(dht.readHumidity());
    String Climate = "Temp = ";
    Climate += Temp; 
    Climate += " Humid = ";
    Climate += Humid;
    //client.publish("Temp", "Temp: " + Temp + (char)248);
    //client.publish("Humid", "Humid: " + Humid + "%");
    LedFlashWithe();
    client.publish("home/climate/status/test", Climate);
    Serial.println(Climate);
  }
  

}




void connect() {
  Serial.print("checking wifi...");
  while (WiFi.status() != WL_CONNECTED) {
    LedRed();
    Serial.print(".");
    delay(1000);
  }

  Serial.print("\nconnecting...");
  while (!client.connect("House_climate", "ardui", "s1hif-xp!sT-qCuwu")) {
    LedBlue();
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nconnected!");

  client.subscribe("home/climate/servo/test");
  //client.subscribe("LightOn");
}

void messageReceived(String &topic, String &payload) {
  Serial.println("incoming: " + topic + " - " + payload);

  myservo.write(payload.toInt());  
  // Note: Do not use the client in the callback to publish, subscribe or
  // unsubscribe as it may cause deadlocks when other things arrive while
  // sending and receiving acknowledgments. Instead, change a global variable,
  // or push to a queue and handle it in the loop after calling `client.loop()`.
}




void LedGreen()
{
  WiFiDrv::digitalWrite(25, HIGH);  //GREEN
  WiFiDrv::digitalWrite(26, LOW);   //RED
  WiFiDrv::digitalWrite(27, LOW);   //BLUE
}

void LedRed()
{
  WiFiDrv::digitalWrite(25, LOW);   //GREEN
  WiFiDrv::digitalWrite(26, HIGH);  //RED
  WiFiDrv::digitalWrite(27, LOW);   //BLUE
}

void LedBlue()
{
  WiFiDrv::digitalWrite(25, LOW);   //GREEN
  WiFiDrv::digitalWrite(26, LOW);   //RED
  WiFiDrv::digitalWrite(27, HIGH);  //BLUE
}

void LedFlashWithe()
{
  LedWhite();
  delay(75);
  LedOff();
  delay(75);
  LedWhite();
  delay(75);
  LedOff();
  delay(75);
  LedWhite();
  delay(75);
  LedOff();
  delay(75);
}


void LedWhite()
{
  WiFiDrv::digitalWrite(25, HIGH);   //GREEN
  WiFiDrv::digitalWrite(26, HIGH);   //RED
  WiFiDrv::digitalWrite(27, HIGH);   //BLUE
}

void LedOff()
{
  WiFiDrv::digitalWrite(25, LOW);   //GREEN
  WiFiDrv::digitalWrite(26, LOW);   //RED
  WiFiDrv::digitalWrite(27, LOW);   //BLUE
}





