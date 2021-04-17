#include "Arduino.h"
#include <FastLED.h>
#include "led.h"

template <int pin>
LED<pin>::LED() {
  FastLED.addLeds<WS2812, pin, GRB>(leds, 32);
}

template <int pin>
void LED<pin>::on() {
  for (int i = 0; i <= 32; i++) {
    leds[i] = CRGB::White;  // CRGB(255, 255, 255) also works
  }
  FastLED.show();
}

template <int pin>
void LED<pin>::off() {
  FastLED.clear();
  FastLED.show();
}
