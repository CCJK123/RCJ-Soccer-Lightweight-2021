#include "Arduino.h"

#ifndef ultrasound_h
#define ultrasound_h

class Ultrasound {
  public:
    Ultrasound(int pin);
    int update();
  private:
    int _pin;
};

#endif
