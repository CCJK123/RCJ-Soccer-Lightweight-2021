#include "ultrasound.h"

Ultrasound::Ultrasound(int pin) {
  pinMode(pin, INPUT);
  _pin = pin;
}

int Ultrasound::update() {
  return (double)analogRead(_pin)*1.325;
}
