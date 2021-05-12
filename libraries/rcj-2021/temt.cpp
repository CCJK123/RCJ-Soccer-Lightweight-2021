#include "temt.h"

Temt::Temt(int pin, int threshold) {
  pinMode(pin, INPUT);
  _pin = pin;
  _threshold = threshold;
}

int Temt::getVal() {
  return analogRead(_pin);
}

double Temt::getPercent() {
  return double(analogRead(_pin))/_threshold;
}

int Temt::getThreshold() {
  return _threshold;
}

bool Temt::isOnLine() {
  return Temt::getVal() > _threshold;
}
