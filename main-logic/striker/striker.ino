#include <cmath>

#include "motor.h"
Motor motorFrontLeft(4, 5);   //6,7
Motor motorFrontRight(7, 8);  //8,9
Motor motorBackLeft(2, 3);    //4,5
Motor motorBackRight(9, 10);  //2,3

#include "base.h"
Base base(motorFrontLeft, motorFrontRight, motorBackLeft, motorBackRight);
double speed; float moveAngle; double rotationRate;

#include "orientation.h"
Orientation imu(Serial5);
float bearingInit = NULL;
float bearingOffset;

#include "ultrasound.h"
Ultrasound ultMidLeft(A20);   //A9
Ultrasound ultMidRight(A14);  //A20
Ultrasound ultTopLeft(A17);   //A1
Ultrasound ultTopFront(A16);  //A2
Ultrasound ultTopRight(A15);  //A0
int distFront, distBack, distLeft, distRight, coordCorners[4][2], worstCorner;
double distCorner;
int coordCentre[2] = {91, 121};

#include "ir.h"
IR irFront(0);
IR irBack(1);

#include "ball.h"
Ball ball(irFront, irBack);
float ballAngle, frontHigh, backHigh, moveAngle, frontMultiplier, backMultiplier, dist;

#include "led.h"
#include "temt.h"



// Compass Correction
#define IMU_ROTATION_RATE_SCALE 0.005 

// No-go / Slowdown Zones
#define BOT_NO_GO_SIDE_DIST 20
#define BOT_NO_GO_CORNER_DIST 50
#define BOT_MAX_SPEED 0.3
#define BOT_SLOWDOWN_DIST 15
#define BOT_SLOWDOWN_ADJUST 5 // Higher adjust, higher min speed, has to be positive

// Ball Track
#define NO_BALL_THRESH 4
#define IR_FRONT_THRESH 130
#define IR_BACK_THRESH 120 
#define IR_RESPONSE 0.8



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}



void loop() {
  // put your main code here, to run repeatedly:


  // Is the bot at risk of going out of bounds / in a place where there's no reason to be there?
  
  // 2021 bot
  //distFront = coordCorners[0][1] = coordCorners[1][1] = ultTopFront.getDist() - 4;
  //distBack = coordCorners[2][1] = coordCorners[3][1] = (ultMidLeft.getDist() + ultMidRight.getDist())/2 - 5;
  //distLeft = coordCorners[0][0] = coordCorners[2][0] = ultTopLeft.getDist() - 5;
  //distRight = coordCorners[1][0] = coordCorners[3][0] = ultTopRight.getDist() - 5;
  
  // 2019 bot
  distFront = coordCorners[0][1] = coordCorners[1][1] = ultTopFront.getDist() - 3;
  distBack = coordCorners[2][1] = coordCorners[3][1] = (ultMidLeft.getDist() + ultMidRight.getDist())/2 - 6;
  distLeft = coordCorners[0][0] = coordCorners[2][0] = ultTopLeft.getDist() - 2;
  distRight = coordCorners[1][0] = coordCorners[3][0] = ultTopRight.getDist() - 2;
  
  if (
    // Any side of bot too near to wall
    (distFront < BOT_NO_GO_SIDE_DIST)
    || (distBack < BOT_NO_GO_SIDE_DIST)
    || (distLeft < BOT_NO_GO_SIDE_DIST)
    || (distRight < BOT_NO_GO_SIDE_DIST)
    // Bot within corner exclusion zone
    || ((distFront < BOT_NO_GO_CORNER_DIST) && (distLeft < BOT_NO_GO_CORNER_DIST))
    || ((distFront < BOT_NO_GO_CORNER_DIST) && (distRight < BOT_NO_GO_CORNER_DIST))
    || ((distBack < BOT_NO_GO_CORNER_DIST) && (distLeft < BOT_NO_GO_CORNER_DIST))
    || ((distBack < BOT_NO_GO_CORNER_DIST) && (distRight < BOT_NO_GO_CORNER_DIST))
  ) {
    // Yes - Bot is on the line (TEMTs) or too near to wall (Ultrasound)
    // Move back into the field
    worstCorner = 0;
    distCorner = sqrt(pow(coordCorners[0][0], 2) + pow(coordCorners[0][1], 2));
    
    for (int i=1; i<4; i++) {
      if (sqrt(pow(coordCorners[i][0], 2) + pow(coordCorners[i][1], 2)) < distCorner) {
        distCorner = sqrt(pow(coordCorners[i][0], 2) + pow(coordCorners[i][1], 2));
        worstCorner = i;
      }
    }
    
    moveAngle = atan2(coordCentre[1]-coordCorners[worstCorner][1], coordCentre[0]-coordCorners[worstCorner][0]);
    switch (worstCorner) {
      case 0:
        // Front Left Corner, Move Back Right
        moveAngle += 90;
      case 1:
        // Front Right Corner, Move Back Left
        moveAngle = 270 - moveAngle;
      case 2:
        // Back Left Corner, Move Front Right
        moveAngle = 90 - moveAngle;
      case 3:
        // Back Right Corner, Move Front Left
        moveAngle += 270;
    }
    
    base.move(slowdownSpeed(), moveAngle, rotationRate);
    return;
  
  } else {
    // No - Bot is within bounds
    ;
  }


  // Is the ball on the field?

  frontHigh = irFront.maxVal();
  backHigh = irBack.maxVal();

  if ((frontHigh <= NO_BALL_THRESH) && (backHigh <= NO_BALL_THRESH)) {
    // No - IR reading above threshold
    // Move to neutral position
    return;

  } else {
    // Yes - Ball is on the field
  }


  // Does the bot have the ball?

  if ((irFront.maxVal() <= 120) && ((irFront.maxChannel() < 3) || (irFront.maxChannel() > 5))) {
    // No - TEMT reading above threshold (2021 bot)
    // No - Front IR reading below threshold (2019 bot) 
    // Move towards ball
    
    ballAngle = ball.getDeg();

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

    base.move(slowdownSpeed(), moveAngle, rotationRate);
    return;
  
  } else {
    // Yes - Bot is in posession of the ball
    // Move towards opponent's goal

    base.move(slowdownSpeed(), 0, rotationRate);
    return;
  }
}



// For whenever imu gives a reading
void serialEvent5() {
  if (imu.decode()) {
    if (bearingInit == NULL) {
      // Initialise bearing on startup
      bearingInit = imu.getMagZ();

    } else {
      // Compare current bearing with initial bearing value
      bearingOffset = imu.getMagZ() - bearingInit;
      if (bearingOffset > 180) bearingOffset -= 360;
      else if (bearingOffset < -180) bearingOffset += 360;
      // Adjust rotationRate accordingly
      rotationRate = -bearingOffset * IMU_ROTATION_RATE_SCALE
    }
  }
}



// Check if in slowdown zone
double slowdownSpeed() {
  // speed = max_speed * (dist-20+const)/(slowdowndist+const)
  // const = 5 for min speed = 0.25
  return min(
    BOT_MAX_SPEED,
    BOT_MAX_SPEED
    * (min(distLeft, distRight) - BOT_NO_GO_SIDE_DIST + BOT_SLOWDOWN_ADJUST) 
    / (BOT_SLOWDOWN_DIST + BOT_SLOWDOWN_ADJUST)
  );
}