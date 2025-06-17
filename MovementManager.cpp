#include "MovementManager.h"
#include <Arduino.h>

// Motor control pins (you can update these as needed)
const int DIR_L = 6; // Left Front Direction
const int PWM_L = 9; // Left Front PWM
const int DIR_R = 3; // Left Rear Direction
const int PWM_R = 10; // Left Rear PWM
//back
const int DIR_BL = 7; // Left Front Direction
const int PWM_BL = 11; // Left Front PWM
const int DIR_BR = 4; // Left Rear Direction
const int PWM_BR = 5; // Left Rear PWM


void MovementManager::begin() {
  // Initialize motor control pins
  pinMode(DIR_L, OUTPUT); pinMode(PWM_L, OUTPUT);
  pinMode(DIR_R, OUTPUT); pinMode(PWM_R, OUTPUT);
  pinMode(DIR_BL, OUTPUT); pinMode(PWM_BL, OUTPUT);
  pinMode(DIR_BR, OUTPUT); pinMode(PWM_BR, OUTPUT);
}

void MovementManager::moveForward() {
  setMotors(HIGH, HIGH, HIGH, HIGH, speed);
}

void MovementManager::moveBackward() {
  setMotors(LOW, LOW, LOW, LOW, speed);
}

void MovementManager::turnLeft() {
  setMotors(LOW, HIGH, LOW, HIGH, speed);
}

void MovementManager::turnRight() {
  setMotors(HIGH, LOW, HIGH, LOW, speed);
}

void MovementManager::stopMotors() {
  analogWrite(PWM_L, 0); analogWrite(PWM_BL, 0);
  analogWrite(PWM_R, 0); analogWrite(PWM_BR, 0);
}

void MovementManager::tornadoSearch(ObjectDetector& detector, LineSensor& lineSensor) {
  const int spinSteps = 6;         // 360 degrees in steps
  const int spinDelay = 250;       // Delay for each small turn
  const int moveDelay = 500;       // Move forward delay if nothing found

  for (int i = 0; i < spinSteps; i++) {
    // Line check
    LineSide edge = lineSensor.detectWhiteLine();
    if (edge != LINE_NONE) {
      Serial.println("Line detected! Abort tornado spin.");
      moveBackward();
      delay(400);
      stopMotors();
      return;
    }

    // Opponent check
    DetectionResult result = detector.detectOpponent();
    if (result.detected) {
      Serial.println("Opponent detected during tornado!");
      speed = 150;
      moveForward();
      return;
    }

    // Spin right a bit
    turnRight();
    delay(spinDelay);
    stopMotors();
    delay(100);
  }

  // After full spin, move forward cautiously
  LineSide edge = lineSensor.detectWhiteLine();
  if (edge == LINE_NONE) {
    Serial.println("No opponent, moving forward to reposition.");
    speed = 100;
    moveForward();
    delay(moveDelay);
    stopMotors();
  } else {
    Serial.println("Line detected after spin, holding position.");
    stopMotors();
  }
}


void MovementManager::turnAround() {
  // Turn 180 degrees by reversing motors for a brief moment
  moveBackward();
  delay(500);
  stopMotors();
  delay(200);
  turnLeft();  // Turn to face the opposite direction
}

void MovementManager::setMotors(bool dirF, bool dirR, bool dirBL, bool dirBR, int speed) {
  digitalWrite(DIR_L, dirF); analogWrite(PWM_L, speed);
  digitalWrite(DIR_R, dirR); analogWrite(PWM_R, speed);
  // Back
  digitalWrite(DIR_BL, dirBL); analogWrite(PWM_BL, speed);
  digitalWrite(DIR_BR, dirBR); analogWrite(PWM_BR, speed);
}
