#include "motor.h"
#include "base.h"
#include "ultrasound.h"

Motor motorFrontLeft(4, 5);   //6,7
Motor motorFrontRight(7, 8);  //8,9
Motor motorBackLeft(2, 3);    //4,5
Motor motorBackRight(9, 10);  //2,3
Base base(motorFrontLeft, motorFrontRight, motorBackLeft, motorBackRight);
Ultrasound ultMidLeft(A20);   //A9
Ultrasound ultMidRight(A14);  //A20
Ultrasound ultTopLeft(A17);   //A1
Ultrasound ultTopFront(A16);  //A2
Ultrasound ultTopRight(A15);  //A0

#include "orientation.h"
Orientation imu(Serial1);
float bearingInit = NULL;
float bearingOffset;
double rotationRate;

// Compass Correction
#define IMU_ROTATION_RATE_SCALE 0.15


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
      base.move(0.2, 315, rotationRate);
    } else {
      // Right
      base.move(0.2, 45, rotationRate);
    }
  } else {
    // Backward
    if (ultTopLeft.getDist() > ultTopRight.getDist()) {
      // Left
      base.move(0.2, 225, rotationRate);
    } else {
      // Right
      base.move(0.2, 135, rotationRate);
    }
  }
  
  delay(10);
}


// For whenever imu gives a reading
void serialEvent1() {
  if (imu.decode()) {
    if (bearingInit == NULL) {
      // Initialise bearing on startup
      Serial.println("5. Initial IMU setup");
      bearingInit = imu.getMagZ();

    } else {
      // Compare current bearing with initial bearing value
      Serial.println("6. New IMU reading");
      bearingOffset = imu.getMagZ() - bearingInit;
      if (bearingOffset > 180) bearingOffset -= 360;
      else if (bearingOffset < -180) bearingOffset += 360;
      // Adjust rotationRate accordingly
      rotationRate = -bearingOffset * IMU_ROTATION_RATE_SCALE;
    }
  }
  Serial.print(imu.getMagZ());
  Serial.print(" ");
  Serial.println(rotationRate);
}
