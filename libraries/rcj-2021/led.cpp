#include "led.h"
#include <FastLED.h>

LED::LED(int pin) {
  FastLED.addLeds<WS2812, pin, GRB>(leds, 32);
  _pin = pin;
}

void LED::on() {
  for (int i = 0; i <= 32; i++) {
    leds[i] = CRGB::White;  //CRGB(255, 255, 255) also works
  }
  FastLED.show();
}
