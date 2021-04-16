#include <FastLED.h>
#define LED_PIN     6
#define NUM_LEDS    32
CRGB leds[NUM_LEDS];
void setup() {
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  for (int i = 0; i <= 32; i++) {
    leds[i] = CRGB(255, 255, 255);
  }
  FastLED.show();
}
void loop() {}
