#include "Arduino.h"
#include <Wire.h> 

#ifndef temt_h
#define temt_h

class IR {
  public:
    IR(int wire);
    int one(int channel);
    int maxVal();
    int maxChannel();
  private:
    int _wire;
};

#endif
