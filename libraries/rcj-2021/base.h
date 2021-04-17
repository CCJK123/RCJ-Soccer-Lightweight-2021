#include "Arduino.h"
#include "motor.h"

#ifndef base_h
#define base_h

class Base {
  public:
    Base(Motor motorFrontLeft, Motor motorFrontRight, Motor motorBackLeft, Motor motorBackRight);
    void rotate(double speed);
    void move(double speed, float angleDeg);
  private:
    Motor _motorFrontLeft;
    Motor _motorFrontRight;
    Motor _motorBackLeft;
    Motor _motorBackRight;
};

#endif