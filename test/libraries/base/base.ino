#include "motor.h"
#include "base.h"

Motor motorFrontLeft(1, 2);
Motor motorFrontRight(3, 4);
Motor motorBackLeft(5, 6);
Motor motorBackRight(7, 8);
Base base(motorFrontLeft, motorFrontRight, motorBackLeft, motorBackRight);

void setup() {}

void loop() {
  // put your main code here, to run repeatedly:

  // Rotate on the spot
  base.rotate(0.1);
  delay(10000);
  // Stop moving
  base.move(0, 0, 0);
  delay(10000);
  // Rotate on the spot
  base.move(0, 0, 0.1);
  delay(10000);
  // Stop moving
  base.move(0, 45, 0);
  delay(10000);

  // Move forward
  base.move(0.1, 0, 0);
  delay(10000);
  // Move backward
  base.move(0.1, 180, 0);
  delay(10000);
  // Move forward
  base.move(-0.1, 180, 0);
  delay(10000);
  // Move backward
  base.move(-0.1, 0, 0);
  delay(10000);

  // Move right
  base.move(0.1, 90, 0);
  delay(10000);
  // Move left
  base.move(0.1, 270, 0);
  delay(10000);
  // Move right
  base.move(-0.1, 270, 0);
  delay(10000);
  // Move left
  base.move(-0.1, 90, 0);
  delay(10000);

  // Move diagonal (45°)
  base.move(0.1, 45, 0);
  delay(10000);
  // Move diagonal (225°)
  base.move(0.1, 225, 0);
  delay(10000);
  // Move diagonal (45°)
  base.move(-0.1, 225, 0);
  delay(10000);
  // Move diagonal (225°)
  base.move(-0.1, 45, 0);
  delay(10000);

  // Move diagonal (135°)
  base.move(0.1, 135, 0);
  delay(10000);
  // Move diagonal (315°)
  base.move(0.1, 315, 0);
  delay(10000);
  // Move diagonal (135°)
  base.move(-0.1, 315, 0);
  delay(10000);
  // Move diagonal (315°)
  base.move(-0.1, 135, 0);
  delay(10000);

  // Move diagonal (30°)
  base.move(0.1, 30, 0);
  delay(10000);
  // Move diagonal (210°)
  base.move(0.1, 210, 0);
  delay(10000);
  // Move diagonal (30°)
  base.move(-0.1, 210, 0);
  delay(10000);
  // Move diagonal (210°)
  base.move(-0.1, 30, 0);
  delay(10000);

  // Move slight forward arc right
  base.move(0.1, 45, 0.1);
  delay(10000);
  // Move slight forward arc left
  base.move(0.1, 315, -0.1);
  delay(10000);
  // Move slight backward arc right
  base.move(-0.1, 315, -0.1);
  delay(10000);
  // Move slight backward arc left
  base.move(-0.1, 45, 0.1);
  delay(10000);
}
