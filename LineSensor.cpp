#include "LineSensor.h"
#include <Arduino.h>

// Initialize line sensor pins
void LineSensor::begin() {
  pinMode(LINE_LEFT_PIN, INPUT);
  pinMode(LINE_RIGHT_PIN, INPUT);
}

// Detect which side sees the white line
LineSide LineSensor::detectWhiteLine() {
  bool leftWhite = digitalRead(LINE_LEFT_PIN) == LOW;
  bool rightWhite = digitalRead(LINE_RIGHT_PIN) == LOW;

  if (leftWhite && rightWhite) return LINE_BOTH;
  if (leftWhite) return LINE_LEFT;
  if (rightWhite) return LINE_RIGHT;
  return LINE_NONE;
}
