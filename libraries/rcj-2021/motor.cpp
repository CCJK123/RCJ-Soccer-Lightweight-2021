#include "motor.h"

Motor::Motor(int pin1, int pin2) {
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  _pin1 = pin1;
  _pin2 = pin2;
}

Motor::Motor(Motor &motor) {
  _pin1 = motor._pin1;
  _pin2 = motor._pin2;
}

void Motor::setSpeed(double speed) {
  if (speed >= 0) {
    // Turn Motor Clockwise
    analogWrite(_pin1, 0);
    analogWrite(_pin2, speed * 255);
  } else {
    // Turn Motor Anti-clockwise
    analogWrite(_pin1, -speed * 255);
    analogWrite(_pin2, 0);
  }
}