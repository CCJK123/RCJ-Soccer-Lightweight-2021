#include "Arduino.h"
#include <Wire.h> 

#ifndef ir_h
#define ir_h

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
