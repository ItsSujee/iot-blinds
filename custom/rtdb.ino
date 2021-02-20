#include <WiFi.h>
#include "FirebaseESP32.h"
#include <Motor.h>
#define FIREBASE_HOST ""
#define FIREBASE_AUTH ""
#define WIFI_SSID ""
#define WIFI_PASSWORD ""

FirebaseData openPercent;
Motor motor(24510);

String path = "/blinds";
String key = "openPercent";
String state = "null";

void streamCallback(StreamData data) {
  state = data.intData();
  motor.setPosition(state.toInt());
  Serial.println("Blinds set to: " + String(state));
}

void streamTimeoutCallback(bool timeout) {
  if (timeout)
  {
    Serial.println();
    Serial.println("Stream timeout, resume streaming...");
    Serial.println();
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println();
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.print("Connected with IP:");
  Serial.println(WiFi.localIP());
  Serial.println();
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  if (!Firebase.beginStream(openPercent, path + "/" + key))
  {
    Serial.println("Could not begin stream");
    Serial.println("ERROR:" + openPercent.errorReason());
    Serial.println();
  }
  Firebase.setStreamCallback(openPercent, streamCallback, streamTimeoutCallback);
}

void loop() {}
