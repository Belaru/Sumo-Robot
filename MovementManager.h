#ifndef MOVEMENT_MANAGER_H
#define MOVEMENT_MANAGER_H

#include "ObjectDetector.h"
#include "LineSensor.h"

class MovementManager {
  public:
    int speed;  // Speed of the robot (100-150 based on detection)

    void begin();   // Initializes motor control pins
    void moveForward(); // Moves the robot forward
    void moveBackward(); // Moves the robot backward
    void turnLeft();    // Turns the robot to the left
    void turnRight();   // Turns the robot to the right
    void stopMotors();  // Stops the motors
    void turnAround();  // Turns the robot 180 degrees
    void setMotors(bool, bool, bool, bool,  int);
    void tornadoSearch(ObjectDetector&, LineSensor&);
};

#endif
