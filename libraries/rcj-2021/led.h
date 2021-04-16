#include "Arduino.h"
#include <FastLED.h>

#ifndef led_h
#define led_h

class LED {
  public:
    LED(int pin);
    void on();
  private:
    int _pin;
    CRGB leds[32];
};

#endif