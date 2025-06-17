#ifndef OBJECT_DETECTOR_H
#define OBJECT_DETECTOR_H

enum Direction { DIR_NONE, DIR_FRONT, DIR_LEFT, DIR_RIGHT, DIR_BACK };

struct DetectionResult {
  bool detected;
  Direction direction;
};

class ObjectDetector {
  public:
    void begin();  // Initializes object detection sensors
    DetectionResult detectOpponent(); // Detects the object and returns the result
};

#endif
