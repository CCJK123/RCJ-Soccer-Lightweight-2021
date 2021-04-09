#include "Arduino.h"

#ifndef led_h
#define led_h

class LED {
  public:
    LED(int pin);
  private:
    int _pin;
};

#endif