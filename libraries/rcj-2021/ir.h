#include <Wire.h> 

#ifndef temt_h
#define temt_h

class IR {
  public:
    IR();
    int one(int channel);
    int maxVal();
    int maxChannel();
};

#endif