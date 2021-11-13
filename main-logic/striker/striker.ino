// Bot States
bool isBotStriker = true
bool goalieStriker = false

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
Ultrasound ultMidLeft(A18);   //A9
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

// Out of goal Zones
#define BOT_GOAL_Y_WIDTH 30
#define BOT_OUT_OF_GOAL_X_DIST (25 + 31)
#define BOT_OUT_OF_GOAL_Y_DIST (BOT_GOAL_Y_WIDTH + 25 + 25) // 25 + 25 (Goal - No-go)
int coordGoalCentre[2] = {91, 121};


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  // Is the bot at risk of going out of bounds / in a place where there's no reason to be there?
  //distFront = coordCorners[0][1] = coordCorners[1][1] = ultTopFront.getDist() - 4;
  //distBack = coordCorners[2][1] = coordCorners[3][1] = (ultMidLeft.getDist() + ultMidRight.getDist())/2 - 5;
  //distLeft = coordCorners[0][0] = coordCorners[2][0] = ultTopLeft.getDist() - 5;
  //distRight = coordCorners[1][0] = coordCorners[3][0] = ultTopRight.getDist() - 5;
  //For our bot ^
  //For 2019 bot v
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
    base.move(BOT_MAX_SPEED, moveAngle, rotationRate);
    return;
  } else {
    // No - Bot is within bounds
    ;
  }

  // Is the ball on the field?
  if () {
    // No - Ball is far away/blocked when grabbed - IR reading below threshold
    // Move to neutral position
    return;
  } else {
    // Yes - Ball is on the field
  }

  // Does the bot have the ball? Or is the ball stationary?
  if () {
    // Yes - Bot is in posession of the ball - TEMT reading below threshold (or IR reading higher than threshold)
    // Or Yes - Ball is stationary (do not implement yet)
    if (!isBotStriker) {
      // Bot is Goalie
      // Act as striker
      goalieStriker = true;
    }
    // Move towards opponent's goal
    return;
  } else {
    // No - Ball far - High light intensity - TEMT reading above threshold
    if (isBotStriker) {
      // Move towards ball - Ball track
    } else {
      // Act as Goalie
      // Pass
      ;
    }
  }

  // Goalie
  // Is the bot outside the goal?
  // Check current location of bot, compare with location of goal
  // xc means x component
  // taking top left as (0,0), and bottom as own goal
  if (!isBotStriker) {
    if (
      (distLeft < BOT_OUT_OF_GOAL_X_DIST)
      || (distRight < BOT_OUT_OF_GOAL_X_DIST)
    ) {
      // Yes - Bot is outside the goal
      // Move back to the goal
    } else {
      // No - Bot is in the goal
      // Move towards the ball
    }
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