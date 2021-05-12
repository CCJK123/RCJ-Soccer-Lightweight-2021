#include "motor.h"
#include "base.h"
#include "ultrasound.h"

Motor motorFrontLeft(6, 7);
Motor motorFrontRight(8, 9);
Motor motorBackLeft(4, 5);
Motor motorBackRight(2, 3);
Base base(motorFrontLeft, motorFrontRight, motorBackLeft, motorBackRight);
Ultrasound ultMidLeft(A9);
Ultrasound ultMidRight(A20);
Ultrasound ultTopLeft(A1);
Ultrasound ultTopFront(A2);
Ultrasound ultTopRight(A0);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  // Raw Readings
  Serial.print("ultMidLeft= ");
  Serial.print(ultMidLeft.getDist());
  Serial.print(" ultMidRight= ");
  Serial.print(ultMidRight.getDist() + 1000);
  Serial.print(" ultTopLeft= ");
  Serial.print(ultTopLeft.getDist() + 2000);
  Serial.print(" ultTopFront= ");
  Serial.print(ultTopFront.getDist() + 3000);
  Serial.print(" ultTopRight = ");
  Serial.print(ultTopRight.getDist() + 4000);
  Serial.println();

  // Move Based On Readings
/*  // Front Back
  if (ultTopFront.getDist() > (ultMidLeft.getDist() + ultMidRight.getDist()) / 2) {
    base.move(0.2, 0, 0);
  } else {
    base.move(0.2, 180, 0);
  }
  // Left Right
  if (ultTopLeft.getDist() > ultTopRight.getDist()) {
    base.move(0.2, 270, 0);
  } else {
    base.move(0.2, 90, 0);
  }*/
  // Both
  if (ultTopFront.getDist() > (ultMidLeft.getDist() + ultMidRight.getDist()) / 2) {
    // Forward
    if (ultTopLeft.getDist() > ultTopRight.getDist()) {
      // Left
      base.move(0.2, 315, 0);
    } else {
      // Right
      base.move(0.2, 45, 0);
    }
  } else {
    // Backward
    if (ultTopLeft.getDist() > ultTopRight.getDist()) {
      // Left
      base.move(0.2, 225, 0);
    } else {
      // Right
      base.move(0.2, 135, 0);
    }
  }
  
  delay(10);
}
