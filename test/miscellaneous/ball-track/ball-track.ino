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

float angleDeg, irFrontHigh, irBackHigh, moveAngle;

void setup() {
  base.rotate(0.2);
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  irFrontHigh = irFront.maxVal();
  irBackHigh = irBack.maxVal();
  angleDeg = ball.getDeg();
  
  if (irFrontHigh > irBackHigh) {
    // IR Ball is to the front of the bot
    if (angleDeg >= 180) moveAngle = 2 * (angleDeg - 360);
    else moveAngle = 2 * angleDeg;
  } else {
    // IR Ball is to the back of the bot
    if (angleDeg <= 180) moveAngle = angleDeg + 90;
    else moveAngle = angleDeg - 90;
  }
  base.move(0.2, moveAngle, 0);
}