#include "base.h"

Base::Base(Motor motorFrontLeft, Motor motorFrontRight, Motor motorBackLeft, Motor motorBackRight) {
  _motorFrontLeft = motorFrontLeft;
  _motorFrontRight = motorFrontRight;
  _motorBackLeft = motorBackLeft;
  _motorBackRight = motorBackRight;
}

void Base::rotate(double speed) {
  _motorFrontLeft.setSpeed(-speed);
  _motorFrontRight.setSpeed(-speed);
  _motorBackLeft.setSpeed(-speed);
  _motorBackRight.setSpeed(-speed);
}

void Base::move(double speed, float angleDeg) {}