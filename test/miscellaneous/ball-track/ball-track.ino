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

float angleDeg, frontHigh, backHigh, moveAngle, frontMultiplier, backMultiplier;

void setup() {
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  frontHigh = irFront.maxVal();
  backHigh = irBack.maxVal();
  angleDeg = ball.getDeg();

  if (angleDeg >= 345 || angleDeg <= 15) frontMultiplier = constrain((135 - frontHigh) / 90, 0, 2);
  else frontMultiplier = 2;
  backMultiplier = min(backHigh / 130, 1);
  
  if (frontHigh > backHigh) {
    // IR Ball is to the front of the bot
    if (angleDeg >= 180) {
      // IR Ball is to the left of the bot
      moveAngle = frontMultiplier * (angleDeg - 360);
    } else {
      // IR Ball is to the right of the bot
      moveAngle = frontMultiplier * angleDeg;
    }
  } else {
    // IR Ball is to the back of the bot
    if (angleDeg >= 180) {
      // IR Ball is to the left of the bot
      moveAngle = angleDeg - 90 * backMultiplier;
    } else {
      // IR Ball is to the right of the bot
      moveAngle = angleDeg + 90 * backMultiplier;
    }
  }
  base.move(0.2, moveAngle, 0);
}