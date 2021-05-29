#include "motor.h"
#include "base.h"

Motor motorFrontLeft(6, 7);
Motor motorFrontRight(8, 9);
Motor motorBackLeft(4, 5);
Motor motorBackRight(2, 3);
Base base(motorFrontLeft, motorFrontRight, motorBackLeft, motorBackRight);

void setup() {}

void loop() {
  // put your main code here, to run repeatedly:
  int delayLength = 3000;
  float motorSpeed = 0.2;
  delay(delayLength);

  // Move forward
  base.move(motorSpeed, 0, 0);
  delay(delayLength);
  // Move backward
  base.move(motorSpeed, 180, 0);
  delay(delayLength);

  // Move right
  base.move(motorSpeed, 90, 0);
  delay(delayLength);
  // Move left
  base.move(motorSpeed, 270, 0);
  delay(delayLength);

  // Move diagonal (45°)
  base.move(motorSpeed, 45, 0);
  delay(delayLength);
  // Move diagonal (225°)
  base.move(motorSpeed, 225, 0);
  delay(delayLength);
  
  // Move diagonal (135°)
  base.move(motorSpeed, 135, 0);
  delay(delayLength);
  // Move diagonal (315°)
  base.move(motorSpeed, 315, 0);
  delay(delayLength);
  
  // Rotate on the spot
  base.rotate(motorSpeed);
  delay(delayLength);
  // Stop moving
  base.move(0, 0, 0);
  delay(delayLength);
  // Rotate on the spot
  base.rotate(-motorSpeed);
  delay(delayLength);
  // Stop moving
  base.move(0, 0, 0);
  delay(600000);
}