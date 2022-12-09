#include<ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <BlynkSimpleEsp8266.h>
#include<WiFiClient.h>
#define BLYNK_PRINT Serial

char auth[] = "Give you auth code given by Blynk";
char ssid[] = "Give your WiFi SSID name";
char pswd[] = "Give your Wifi Password";

int equipmt1 = 16;
int receivedValue;

void setup() {
  // put your setup code here, to run once:

  pinMode(equipmt1, OUTPUT);
  digitalWrite(equipmt1, HIGH);
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pswd);
}

void loop() {
  // put your main code here, to run repeatedly:
  Blynk.run();
}
BLYNK_WRITE(V1) {

  HTTPClient http;
  WiFiClient wificlient;
  int httpCode;
  receivedValue = param.asInt();
  Serial.print(receivedValue);
  if (1 == receivedValue) {
    digitalWrite(equipmt1, HIGH);
    while (WiFi.status() != WL_CONNECTED) {
      delay(1000);
      Serial.print("Connecting...");
      if (WiFi.status() == WL_CONNECTED) {
        
        http.begin(wificlient,"https://maker.ifttt.com/trigger/motor is on/with/key/cQC1rG9rthkoaj05gVhTLx");
        http.end();
        httpCode = http.GET();
        Serial.println(httpCode);
      }
    }
  }

  if (0 == receivedValue) {
    digitalWrite(equipmt1,LOW);
    while (WiFi.status() != WL_CONNECTED) {
      delay(1000);
      Serial.print("Connecting...");
      if (WiFi.status() == WL_CONNECTED) {

        http.begin(wificlient,"https://maker.ifttt.com/trigger/motor is off/with/key/cQC1rG9rthkoaj05gVhTLx");
        http.end();
        httpCode = http.GET();
        Serial.println(httpCode);
      }
    }
  }
}