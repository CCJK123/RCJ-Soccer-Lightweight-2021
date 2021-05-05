#include "base.h"

Base::Base(Motor motorFrontLeft, Motor motorFrontRight, Motor motorBackLeft, Motor motorBackRight) :
  _motorFrontLeft(motorFrontLeft),
  _motorFrontRight(motorFrontRight),
  _motorBackLeft(motorBackLeft),
  _motorBackRight(motorBackRight)
{}

void Base::rotate(double speed) {
  _motorFrontLeft.setSpeed(speed);
  _motorFrontRight.setSpeed(speed);
  _motorBackLeft.setSpeed(speed);
  _motorBackRight.setSpeed(speed);
}

void Base::move(double speed, float angleDeg, double rotationRate) {
  /*
    Angle input is relative to front of robot
    Angle for calculations is relative to NE diagonal of robot (so it lines up with a pair of the motors)
    Thus to convert angle input to angle for calculations, add 45° to angleDeg
  */
  angleDeg += 45;
  // Convert angle from degrees to radians
  float angleRad = angleDeg * (float) PI / (float) 180;

  // Initialise variables for motor speed
  double NESpeed, NWSpeed, NESpeedAdjusted, NWSpeedAdjusted;
  // Calculate speed in NE and NW directions (directions are relative to robot)
  NESpeed = speed * sin(angleRad);
  NWSpeed = speed * cos(angleRad);
  /*
    The robot can move in a set direction (set by angleDeg) at a set speed (set by speed)
    The robot can also rotate on the spot at a set speed (set by rotationRate)
    Thus the robot can be stationary (speed = 0, rotationRate = 0), 
                       move in a straight line (speed = (constant) i, rotationRate = 0),
                       rotate on the spot (speed = 0, rotationRate = (constant) i), or
                       move in an arc (speed = (constant) i, rotationRate = (constant) i)
    
    diagSpeedAdjusted is used to account for rotationRate
    When rotationRate != 0, diagSpeedAdjusted reduces the speed of one of the motors in a diagonal motor pair
    This induces an either clockwise or anticlockwise rotation of the robot
  */
  if (rotationRate > (double) 1) rotationRate = (double) 1;
  else if (rotationRate < (double) -1) rotationRate = (double) -1;
  NESpeedAdjusted = NESpeed - 2 * NESpeed * abs(rotationRate);
  NWSpeedAdjusted = NWSpeed - 2 * NWSpeed * abs(rotationRate);
  
  // Determine whether to set each motor to diagSpeed or diagSpeedAdjusted

  // For the pair of motors that move in direction of NE diagonal (Front Left & Back Right motor)
  if (angleDeg >= 0 && angleDeg <= 180) {
    // Intention to move in NE direction
    if (rotationRate >= 0) {
      // Intention to rotate clockwise
      _motorFrontLeft.setSpeed(NESpeed);
      _motorBackRight.setSpeed(NESpeedAdjusted);
    } else {
      // Intention to rotate anticlockwise
      _motorFrontLeft.setSpeed(NESpeedAdjusted);
      _motorBackRight.setSpeed(NESpeed);
    } 
  } else {
    // Intention to move in SW direction
    if (rotationRate >= 0) {
      // Intention to rotate clockwise
      _motorFrontLeft.setSpeed(NESpeedAdjusted);
      _motorBackRight.setSpeed(NESpeed);
    } else {
      // Intention to rotate anticlockwise
      _motorFrontLeft.setSpeed(NESpeed);
      _motorBackRight.setSpeed(NESpeedAdjusted);
    }
  }

  // For the pair of motors that move in direction of NW diagonal (Front Right & Back Left motor)
  if ((angleDeg >= 90 && angleDeg <= 270) ==  false) {
    // Intention to move in NW direction
    if (rotationRate >= 0) {
      // Intention to rotate clockwise
      _motorFrontRight.setSpeed(NWSpeedAdjusted);
      _motorBackLeft.setSpeed(NWSpeed);
    } else {
      // Intention to rotate anticlockwise
      _motorFrontRight.setSpeed(NWSpeed);
      _motorBackLeft.setSpeed(NWSpeedAdjusted);
    }
  } else {
    // Intention to move in SE direction
    if (rotationRate >= 0) {
      // Intention to rotate clockwise
      _motorFrontRight.setSpeed(NWSpeed);
      _motorBackLeft.setSpeed(NWSpeedAdjusted);
    } else {
      // Intention to rotate anticlockwise
      _motorFrontRight.setSpeed(NWSpeedAdjusted);
      _motorBackLeft.setSpeed(NWSpeed);
    }
  }
}
