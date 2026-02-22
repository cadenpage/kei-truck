#include <WiFi.h>

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  delay(5000);
  Serial.println("MAC Address:");
  Serial.println(WiFi.macAddress());
}

void loop() {}
