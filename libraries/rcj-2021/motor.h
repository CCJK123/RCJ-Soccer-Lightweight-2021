#include "Arduino.h"

#ifndef motor_h
#define motor_h

class Motor {
  public:
    Motor(int pin1, int pin2);
    void setSpeed(double speed);
  private:
    int _pin1;
    int _pin2;
};

#endif