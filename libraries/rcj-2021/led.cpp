#include "Arduino.h"
#include <Adafruit_NeoPixel.h>
#include "led.h"

LED::LED(int pin) : Adafruit_NeoPixel(24, pin, NEO_GRB + NEO_KHZ800) {
  Adafruit_NeoPixel::begin();
  _pin = pin;
}

void LED::on() {
  for (int i = 0; i < 24; i++) {
    Adafruit_NeoPixel::setPixelColor(i, 255, 255, 255);
  }
  Adafruit_NeoPixel::show();
}

void LED::off() {
  Adafruit_NeoPixel::clear();
  Adafruit_NeoPixel::show();
}