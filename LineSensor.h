#ifndef LINESENSOR_H
#define LINESENSOR_H

// Line Side Enum
enum LineSide { LINE_NONE, LINE_LEFT, LINE_RIGHT, LINE_BOTH };

// Line Sensor Pins
const int LINE_LEFT_PIN  = 12;
const int LINE_RIGHT_PIN = 8;
const int LINE_LEFT_PIN2  = 14; //back
const int LINE_RIGHT_PIN2 = 15; //back

class LineSensor {
  public:
    void begin();           // Initialize the line sensor
    LineSide detectWhiteLine();  // Detect which side sees the white line
};

#endif
