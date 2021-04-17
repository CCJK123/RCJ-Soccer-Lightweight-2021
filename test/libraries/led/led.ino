#include <Adafruit_NeoPixel.h>

int pin = 12;

Adafruit_NeoPixel ring(32, pin, NEO_GRB + NEO_KHZ800);

void setup() {
  ring.begin();
}

void loop() {
  ring.clear();
  ring.show();
  delay(1000);
  
  for (int i = 0; i<32; i++) {
    ring.setPixelColor(i, 255, 255, 255);
  }
  ring.show();
  delay(1000);
}
