#include <Arduino.h>

#define LED LED_BUILTIN   // Try 21 first

void setup() {
  pinMode(LED, OUTPUT);
}

void loop() {
  digitalWrite(LED, HIGH);  // LED ON
  delay(1000);                  // Wait 1 second
  digitalWrite(LED, LOW);   // LED OFF
  delay(1000);                  // Wait 1 second
}
