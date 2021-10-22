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

float ballAngle, frontHigh, backHigh, moveAngle, frontMultiplier, backMultiplier, dist;

#define IR_FRONT_THRESH 130
#define IR_BACK_THRESH 120 
#define IR_RESPONSE 0.8 // 

void setup() {
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  frontHigh = irFront.maxVal();
  backHigh = irBack.maxVal();
  ballAngle = ball.getDeg();

//  dist = pow((frontHigh / IR_FRONT_THRESH), IR_RESPONSE); // further the distance, smaller the number

  if (ballAngle >= 350 || ballAngle <= 10) { // in ball cap zone // account for minor differences when ball in ball capture zone, need to be calibrated
    /*  0 <= multiplier <= 2, scaled by 2x from the dist
     *  multiplier < 1 when near for stability
     *  multiplier > 1 when far so as to prioritise one axis
     */
    dist = pow((frontHigh / IR_FRONT_THRESH), IR_RESPONSE); // further the distance, smaller the number
    frontMultiplier = constrain((2 * (1 - dist)), 0, 2); // 2x for scaling, 1 - dist due to relationship

    if (ballAngle >= 180) { // ball is to the left of the bot
      moveAngle = (ballAngle - 360) * frontMultiplier; // negative to move left
    } else {
      moveAngle = ballAngle * frontMultiplier;
    }

  } else { // in other zones
    if (frontHigh > backHigh) { // ball is in front of the bot
      /*  1 <= multiplier <= 2, calculated by adding 1 to the dist
       *  suppose ball is right beside the bot, then multiplier = 2 to move at 2x90=180 deg to catch the ball
       *  if the bot is far from the ball, then multiplier is smaller so as to move more at the actual angle of the ball
       */

      dist = pow((frontHigh / IR_FRONT_THRESH), IR_RESPONSE); // further the distance, smaller the number
      frontMultiplier = constrain((dist + 1), 1, 2); // 2x for scaling, 1 - dist due to relationship
    
      if (ballAngle >= 180) {    // 1. ball is to the front left of the bot
        moveAngle = (ballAngle - 360) * frontMultiplier; // negative to move left
      } else {                  // 2. ball is to the front right of the bot
        moveAngle = ballAngle * frontMultiplier;
      }
    } else { // ball is behind the bot

      dist = pow((backHigh / IR_BACK_THRESH), IR_RESPONSE); // further the distance, smaller the number
      backMultiplier = constrain((dist * 2), 0, 2); // 2x for scaling, 1 - dist due to relationship  

      if (ballAngle >= 180) {    // 3. ball is to the back left of the bot
        moveAngle = ballAngle - (90 * backMultiplier); 
      } else {                  // 4. ball is to the back right of the bot
        moveAngle = ballAngle + (90 * backMultiplier);
      }
    }
  }

  base.move(0.2, moveAngle, 0);
}
