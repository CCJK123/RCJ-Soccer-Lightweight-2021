#include "motor.h"
#include "base.h"
#include "ir.h"
#include "ball.h"
/*
#include <UM7.h>
#include "orientation.h"
*/

Motor motorFrontLeft(6, 7);
Motor motorFrontRight(8, 9);
Motor motorBackLeft(4, 5);
Motor motorBackRight(2, 3);
Base base(motorFrontLeft, motorFrontRight, motorBackLeft, motorBackRight);
IR irFront(0);
IR irBack(1);
Ball ball(irFront, irBack);
//Orientation imu();


void setup() {
  base.rotate(0.2);
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  float angleDeg = ball.getDeg();
  if (angleDeg >= 0 && angleDeg < 180) {
    // IR Ball is to the right of bot
    base.move(0.2, 1.1 * angleDeg, 0);
  } else {
    // IR Ball is to the left of bot
    base.move(0.2, 0.9 * angleDeg, 0);
  }
}
