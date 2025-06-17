#include "ObjectDetector.h"
#include <Arduino.h>

// Sensor pins (updated based on your request)
const int SENSOR_FRONTLEFT_PIN = 30;
const int SENSOR_FRONTRIGHT_PIN = 2;
const int SENSOR_LEFT_PIN = 50;
const int SENSOR_RIGHT_PIN = 16;

void ObjectDetector::begin() {
  // Initialize sensor pins
  pinMode(SENSOR_FRONTLEFT_PIN, INPUT);
  pinMode(SENSOR_FRONTRIGHT_PIN, INPUT);
  pinMode(SENSOR_LEFT_PIN, INPUT);
  pinMode(SENSOR_RIGHT_PIN, INPUT);
}

DetectionResult ObjectDetector::detectOpponent() {
  DetectionResult result = { false, DIR_NONE };

  // Check if any sensor detects an object
  if (digitalRead(SENSOR_FRONTLEFT_PIN) == HIGH || digitalRead(SENSOR_FRONTRIGHT_PIN) == HIGH) {
    result = { true, DIR_FRONT };
  } else if (digitalRead(SENSOR_LEFT_PIN) == HIGH) {
    result = { true, DIR_LEFT };
  } else if (digitalRead(SENSOR_RIGHT_PIN) == HIGH) {
    result = { true, DIR_RIGHT };
  }

  return result;
}
