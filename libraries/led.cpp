#include "led.h"
#include <FastLED.h>

LED::LED(int pin) {
  CRGB leds[32];
  FastLED.addLeds<WS2812, pin, GRB>(leds, 32);
  for (int i = 0; i <= 32; i++) {
    leds[i] = CRGB::White;  //CRGB(255, 255, 255) also works
  }
  FastLED.show();
  _pin = pin;
}