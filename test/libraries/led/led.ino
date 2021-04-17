// Set all the LEDs to a random color.
#include <AddressableLEDStrip.h>

int pin = 6;

AddressableLEDStrip strip = AddressableLEDStrip(pin, pin, 32);

void setup() {
}

void loop() {
  strip.set_all_leds(0, 0, 0);
  strip.send();
}
