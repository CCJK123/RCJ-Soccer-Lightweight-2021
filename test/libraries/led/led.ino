#include <FastLED.h>

template <int pin>
class LED {
  public:
    LED() {
      FastLED.addLeds<WS2812, pin, GRB>(leds, 32);
    }

    void on() {
      for (int i = 0; i <= 32; i++) {
        leds[i] = CRGB::White;  // CRGB(255, 255, 255) also works
      }
      FastLED.show();
    }

    void off() {
      FastLED.clear();
      FastLED.show();
    }

  private:
    CRGB leds[32];
};

LED<6> led;

void setup() {
}

void loop() {
  led.on();
  delay(1000);
  led.off();
  delay(1000);
}
