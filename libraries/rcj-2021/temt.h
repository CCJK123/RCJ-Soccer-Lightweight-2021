#include "Arduino.h"

#ifndef temt_h
#define temt_h

class Temt {
  public:
    Temt(int pin, int threshold);
    int getVal();
    double getPercent();
  private:
    int _pin;
    int _threshold;
};

#endif