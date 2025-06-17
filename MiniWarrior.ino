#include "MovementManager.h"   // Include MovementManager class
#include "ObjectDetector.h"    // Include ObjectDetector class
#include "LineSensor.h"        // Include LineSensor class

MovementManager robot;   // Create an instance of MovementManager
ObjectDetector detector; // Create an instance of ObjectDetector
LineSensor lineSensor;   // Create an instance of LineSensor

const int START_PIN = 2;  // Pin where the start module is connected

void waitForStartSignal() {
  pinMode(START_PIN, INPUT);  // Initialize the pin as input

  Serial.println("Waiting for start signal...");
  while (digitalRead(START_PIN) == LOW) {
    // Do nothing until the pin goes HIGH
  }

  Serial.println("Start signal received! Waiting 5 seconds...");
  delay(1000); // 5-second delay before starting the match
}

void setup() {
  Serial.begin(9600);
  robot.begin();         // Initialize the robot
  detector.begin();      // Initialize the object detector
  lineSensor.begin();    // Initialize the line sensor

  waitForStartSignal(); 
}

void loop() {

  // Wait while signal is LOW (pause robot)
  if (digitalRead(START_PIN) == LOW) {
    robot.stopMotors(); // Make sure motors are stopped
    return;             // Skip the loop if not running
  }

  // Detect white line
  LineSide edge = lineSensor.detectWhiteLine();

  if (edge != LINE_NONE) {
    Serial.println("EDGE DETECTED! Backing off.");
    robot.speed = 130;  // Slightly lower speed for safer backing
    robot.moveBackward();
    delay(500);

    if (edge == LINE_LEFT) {
      robot.turnRight();
      delay(300);
    } else if (edge == LINE_RIGHT) {
      robot.turnLeft();
      delay(300);
    } else if (edge == LINE_BOTH) {
      robot.moveBackward();
      delay(300);
    } else {
      // Full line coverage, move forward
      robot.moveForward();
      delay(500);
    }

    robot.stopMotors();
    delay(200);
    return;
  }

  // Detect opponent
  DetectionResult result = detector.detectOpponent();

  if (result.detected) {
    robot.speed = 150;  // Full power during combat
    switch (result.direction) {
      case DIR_FRONT:
        Serial.println("Opponent in FRONT");
        robot.moveForward();
        break;
      case DIR_LEFT:
        Serial.println("Opponent on LEFT");
        robot.turnLeft();
        delay(300);
        break;
      case DIR_RIGHT:
        Serial.println("Opponent on RIGHT");
        robot.turnRight();
        delay(300);
        break;
      default:
        break;
    }
  } else {
    robot.speed = 100;  // Slower speed while searching
    Serial.println("No opponent detected. Searching...");
    robot.turnLeft();
    delay(200);

    // robot.tornadoSearch(detector, lineSensor);
  }

  delay(100); // Small delay before next iteration
}
