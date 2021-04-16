#include "temt.h"

Temt::Temt(int pin, int threshold) {
  pinMode(pin, INPUT);
  _pin = pin;
  _threshold = threshold;
}

int Temt::update() {
  return analogRead(_pin);
}

double Temt::updatePercent() {
  return double(analogRead(_pin))/_threshold;
}