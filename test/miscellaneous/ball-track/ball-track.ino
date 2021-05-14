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

#define IR_FRONT_THRESH 130
#define IR_BACK_THRESH 120 

void setup() {
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  frontHigh = irFront.maxVal();
  backHigh = irBack.maxVal();
  angleDeg = ball.getDeg();

  if (angleDeg >= 350 || angleDeg <= 10) { // account for minor differences when ball in ball capture zone, need to be calibrated
    frontMultiplier = constrain((IR_FRONT_TRESH - frontHigh) / 90, 0, 2);
  } else {
    frontMultiplier = 2;
  }

  backMultiplier = min(backHigh / IR_BACK_TRESH, 1);

  if (frontHigh > backHigh) { // ball is in front of the bot
    if (angleDeg >= 180) { // ball is to the left of the bot
      moveAngle = (angleDeg - 360) * frontMultiplier;
    } else { // ball is to the right of the bot
      moveAngle = angleDeg * frontMultiplier;
    }

  } else { // ball is behind the bot
    if (angleDeg >= 180) { // ball is to the left of the bot
      moveAngle = angleDeg - (90 * backMultiplier);
    } else { // ball is to the right of the bot
      moveAngle = angleDeg + (90 * backMultiplier);
    }
  }

  base.move(0.15, moveAngle, 0);
}
