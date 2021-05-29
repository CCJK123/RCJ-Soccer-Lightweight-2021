#include "ultrasound.h"

Ultrasound::Ultrasound(int pin) {
  pinMode(pin, INPUT);
  _pin = pin;
}

int Ultrasound::getDist() {
  return (double)analogRead(_pin);
}