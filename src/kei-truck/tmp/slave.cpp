#include <esp_now.h>
#include <WiFi.h>

#define LED_PIN LED_BUILTIN   // XIAO ESP32S3 built-in LED

void onReceive(const uint8_t *mac, const uint8_t *incomingData, int len) {
  char command = (char)incomingData[0];

  if (command == 'a') {
    digitalWrite(LED_PIN, HIGH);
    Serial.println("LED ON");
  }

  if (command == 'b') {
    digitalWrite(LED_PIN, LOW);
    Serial.println("LED OFF");
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);

  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW Init Failed");
    return;
  }

  esp_now_register_recv_cb(onReceive);

  Serial.println("Slave ready.");
}

void loop() {}
