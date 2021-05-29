#include "motor.h"
#include "base.h"
#include "ir.h"
#include "ball.h"

Motor motorFrontLeft(6, 7);
Motor motorFrontRight(8, 9);
Motor motorBackLeft(4, 5);
Motor motorBackRight(2, 3);
Base base(motorFrontLeft, motorFrontRight, motorBackLeft, motorBackRight);
IR irFront(0);
IR irBack(1);
Ball ball(irFront, irBack);

float frontHigh, backHigh;

void setup() {}

void loop() {
  // put your main code here, to run repeatedly:
  frontHigh = irFront.maxVal();
  backHigh = irBack.maxVal();
  if (max(frontHigh, backHigh) <= 130) {
    base.move(0.3, ball.getDeg(), 0);
  } else {
    delay(100000);
  }
}