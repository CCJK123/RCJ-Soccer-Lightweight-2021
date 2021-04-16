#include "Arduino.h"

#ifndef ultrasound_h
#define ultrasound_h

class Ultrasound {
  public:
    Ultrasound(int pin);
    int getDist();
  private:
    int _pin;
};

#endif
