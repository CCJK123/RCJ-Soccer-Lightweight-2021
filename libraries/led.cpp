#include "Arduino.h"
#include "led.h"
#include <FastLED.h>

LED::LED(int pin) {
  FastLED.addLeds<WS2812, pin, GRB>(leds, 32);
  for (int i = 0; i <= 32; i++) {
    leds[i] = CRGB(255, 255, 255);
  }
  FastLED.show();
  _pin = pin;
}