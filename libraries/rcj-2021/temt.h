#include "Arduino.h"

#ifndef temt_h
#define temt_h

class Temt {
  public:
    Temt(int pin);
    int update();
    double updatePercent();
    void setTreshold(int treshold);
  private:
    int _pin;
    int _threshold;
};

#endif