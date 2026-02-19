#include <esp_now.h>
#include <WiFi.h>

uint8_t slaveAddress[] = {0x8C, 0xBF, 0xEA, 0x8E, 0xEF, 0x40};  // Slave MAC address (8C:BF:EA:8E:EF:40)

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW Init Failed");
    return;
  }

  esp_now_peer_info_t peerInfo = {};
  memcpy(peerInfo.peer_addr, slaveAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }

  Serial.println("Master ready. Type 'a' or 'b'");
}

void loop() {
  if (Serial.available()) {
    char command = Serial.read();

    if (command == 'a' || command == 'b') {
      esp_now_send(slaveAddress, (uint8_t *)&command, sizeof(command));
      Serial.print("Sent: ");
      Serial.println(command);
    }
  }
}
