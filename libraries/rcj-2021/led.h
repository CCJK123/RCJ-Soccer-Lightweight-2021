#include "Arduino.h"
#include <FastLED.h>

#ifndef led_h
#define led_h

template <int pin>
class LED {
  public:
    LED();
    void on();
    void off();
  private:
    CRGB leds[32];
};

#endif