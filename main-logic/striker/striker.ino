#include <cmath>

#include "motor.h"
Motor motorFrontLeft(6, 7);
Motor motorFrontRight(8, 9);
Motor motorBackLeft(4, 5);
Motor motorBackRight(2, 3);

#include "base.h"
Base base(motorFrontLeft, motorFrontRight, motorBackLeft, motorBackRight);
double speed; float angleDeg; double rotationRate;

#include "orientation.h"
Orientation imu(Serial5);
float bearingInit = NULL;
float bearingOffset;

#include "ultrasound.h"
Ultrasound ultMidLeft(A9);
Ultrasound ultMidRight(A20);
Ultrasound ultTopLeft(A1);
Ultrasound ultTopFront(A2);
Ultrasound ultTopRight(A0);
int distFront, distBack, distLeft, distRight, coordCorners[4][2], worstCorner;
double distCorner;
int coordCentre[2] = {91, 121};

#include "ball.h"
#include "ir.h"
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


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  // Is the bot at risk of going out of bounds / in a place where there's no reason to be there?
  distFront = coordCorners[0][1] = coordCorners[1][1] = ultTopFront.getDist();
  distBack = coordCorners[2][1] = coordCorners[3][1] = (ultMidLeft.getDist() + ultMidRight.getDist()) / 2;
  distLeft = coordCorners[0][0] = coordCorners[2][0] = ultTopLeft.getDist();
  distRight = coordCorners[1][0] = coordCorners[3][0] = ultTopRight.getDist();
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
    angleDeg = atan2(coordCentre[1]-coordCorners[worstCorner][1], coordCentre[0]-coordCorners[worstCorner][0]);
    if (worstCorner == 0) {
      // Front Left Corner, Move Back Right
      angleDeg += 90;
    } else if (worstCorner == 1) {
      // Front Right Corner
      angleDeg = 270 - angleDeg;
    } else if (worstCorner == 2) {
      // Back Left Corner
      angleDeg = 90 - angleDeg;
    } else if (worstCorner == 3) {
      // Back Right Corner
      angleDeg += 270;
    }
    base.move(BOT_MAX_SPEED, angleDeg, rotationRate);
    return;
  } else {
    // No - Bot is within bounds
    ;
  }

  // Is the ball on the field?
  if () {
    // No - IR reading above threshold
    // Move to neutral position
    return;
  } else {
    // Yes - Ball is on the field
  }

  // Does the bot have the ball?
  if () {
    // No - TEMT reading above threshold
    // Move towards ball
    return;    
  } else {
    // Yes - Bot is in posession of the ball
    // Move towards opponent's goal
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
  // when dist 20, speed 0.25
  // when dist 25, speed 0.50
  // when dist 30, speed 0.75
  // when dist 35, speed 1.00
  // speed = max_speed * (dist-20+const)/(slowdowndist+const)
  // speed = BOT_MAX_SPEED * (dist - BOT_NO_GO_SIDE_DIST + BOT_SLOWDOWN_ADJUST) / (BOT_SLOWDOWN_DIST + BOT_SLOWDOWN_ADJUST)
  // const = 5 for min speed = 0.25
  return min(
    BOT_MAX_SPEED,
    BOT_MAX_SPEED * (min(distLeft, distRight) - BOT_NO_GO_SIDE_DIST + BOT_SLOWDOWN_ADJUST) / (BOT_SLOWDOWN_DIST + BOT_SLOWDOWN_ADJUST));
}