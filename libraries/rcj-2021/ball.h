#include "Arduino.h"
#include "ir.h"

#ifndef ball_h
#define ball_h

class Ball {
  public:
    Ball(IR irFront, IR irBack);
    float getDeg();
  private:
    IR _irFront;
    IR _irBack;
};

#endif
