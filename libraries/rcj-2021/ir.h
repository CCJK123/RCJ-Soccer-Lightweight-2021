#include "Arduino.h"
#include <Wire.h> 

#ifndef temt_h
#define temt_h

class IR {
  public:
    IR();
    void begin(int wire);
    int getData(int wire, int channel);
    int maxVal(int wire);
    int maxChannel(int wire);
};

#endif
