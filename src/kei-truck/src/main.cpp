#include <Arduino.h>

const int PIN_ENA = D1;  // D1
const int PIN_IN1 = D2;  // D2
const int PIN_IN2 = D3;  // D3
const int PIN_IN3 = D4;  // D4
const int PIN_IN4 = D5;  // D5  
const int PIN_ENB = D6;  // D6 

const int PWM_FREQ = 20000;     // 20 kHz (quiet)
const int PWM_RES  = 8;         // 8-bit: 0-255

const int CH_ENA = 0;
const int CH_ENB = 1;

void motorA_forward() { digitalWrite(PIN_IN1, HIGH); digitalWrite(PIN_IN2, LOW); }
void motorA_backward(){ digitalWrite(PIN_IN1, LOW);  digitalWrite(PIN_IN2, HIGH); }
void motorA_brake()   { digitalWrite(PIN_IN1, HIGH); digitalWrite(PIN_IN2, HIGH); }
void motorA_coast()   { digitalWrite(PIN_IN1, LOW);  digitalWrite(PIN_IN2, LOW);  }

void motorB_forward() { digitalWrite(PIN_IN3, HIGH); digitalWrite(PIN_IN4, LOW); }
void motorB_backward(){ digitalWrite(PIN_IN3, LOW);  digitalWrite(PIN_IN4, HIGH); }
void motorB_brake()   { digitalWrite(PIN_IN3, HIGH); digitalWrite(PIN_IN4, HIGH); }
void motorB_coast()   { digitalWrite(PIN_IN3, LOW);  digitalWrite(PIN_IN4, LOW);  }

// Helper to safely set PWM even if ENA not used
void pwmWriteSafe(int pin, int channel, int duty) {
  duty = constrain(duty, 0, 255);
  if (pin < 0) return;
  ledcWrite(channel, duty);
}
void driveForward(int speedA, int speedB) {
  motorA_forward();
  motorB_forward();

  // If ENA isn't wired, speedA won't matter (Motor A will just run).
  pwmWriteSafe(PIN_ENA, CH_ENA, speedA);
  pwmWriteSafe(PIN_ENB, CH_ENB, speedB);
}

void driveBackward(int speedA, int speedB) {
  motorA_backward();
  motorB_backward();
  pwmWriteSafe(PIN_ENA, CH_ENA, speedA);
  pwmWriteSafe(PIN_ENB, CH_ENB, speedB);
}

void turnLeft(int speedA, int speedB) {
  // Left turn: left wheel slower/back, right wheel forward (depends on your wiring)
  motorA_backward();
  motorB_forward();
  pwmWriteSafe(PIN_ENA, CH_ENA, speedA);
  pwmWriteSafe(PIN_ENB, CH_ENB, speedB);
}

void turnRight(int speedA, int speedB) {
  motorA_forward();
  motorB_backward();
  pwmWriteSafe(PIN_ENA, CH_ENA, speedA);
  pwmWriteSafe(PIN_ENB, CH_ENB, speedB);
}

void stopMotors() {
  // Choose brake or coast:
  motorA_coast();
  motorB_coast();
  pwmWriteSafe(PIN_ENA, CH_ENA, 0);
  pwmWriteSafe(PIN_ENB, CH_ENB, 0);
}

void setup() {
  pinMode(PIN_IN1, OUTPUT);
  pinMode(PIN_IN2, OUTPUT);
  pinMode(PIN_IN3, OUTPUT);
  pinMode(PIN_IN4, OUTPUT);
  
  ledcSetup(CH_ENA, PWM_FREQ, PWM_RES);
  ledcAttachPin(PIN_ENA, CH_ENA);
  ledcSetup(CH_ENB, PWM_FREQ, PWM_RES);
  ledcAttachPin(PIN_ENB, CH_ENB);
  stopMotors();
}
// --- High-level controls ---
// speed: 0-255

void loop() {
  // Demo pattern
  driveForward(220, 220);
  delay(1500);

  stopMotors();
  delay(400);

  driveBackward(220, 220);
  delay(1500);

  stopMotors();
  delay(400);

  turnLeft(220, 220);
  delay(700);

  stopMotors();
  delay(400);

  turnRight(255, 220);
  delay(700);

  stopMotors();
  delay(1000);
}

