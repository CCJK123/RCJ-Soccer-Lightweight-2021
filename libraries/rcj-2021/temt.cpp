#include "temt.h"

Temt::Temt(int pin) {
  pinMode(pin, INPUT);
  _pin = pin;
  _threshold = 650; // defaults to 650
}

int Temt::update() {
  return analogRead(_pin);
}

double Temt::updatePercent() {
  return double(analogRead(_pin))/_threshold;
}

void Temt::setTreshold(int treshold) {
  _threshold = treshold;
}