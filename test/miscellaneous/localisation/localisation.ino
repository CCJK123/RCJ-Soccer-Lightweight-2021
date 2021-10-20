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
  Serial.print(ultMidRight.getDist() + 500);
  Serial.print(" ultTopLeft= ");
  Serial.print(ultTopLeft.getDist() + 1000);
  Serial.print(" ultTopFront= ");
  Serial.print(ultTopFront.getDist() + 1500);
  Serial.print(" ultTopRight = ");
  Serial.print(ultTopRight.getDist() + 2000);
  Serial.print(" ");

  // Confidence
  double length = min((ultMidLeft.getDist() + ultMidRight.getDist()) / 2 + ultTopFront.getDist() - 9, 243);
  double breadth = min(ultTopLeft.getDist() + ultTopRight.getDist() - 9, 182);
  double fieldArea = 182;
  if (length > 208) fieldArea *= 243;
  else fieldArea *= 208;
  double confidence = 1 - length * breadth / fieldArea;

/*  // Calculated Readings
  Serial.print("length = ");
  Serial.print(length);
  Serial.print(" breadth = ");
  Serial.print(breadth);
  Serial.print(" fieldArea = ");
  Serial.print(fieldArea);
  Serial.print(" confidence = ");
  Serial.print(confidence);
*/  
  Serial.println();
  delay(10);
}


// double speed
