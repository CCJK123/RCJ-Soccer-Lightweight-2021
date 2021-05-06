#include "ultrasound.h"

Ultrasound ultrasoundLeft(9);
Ultrasound ultrasoundRight(20);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print(ultrasoundLeft.getDist());
  Serial.print(",");
  Serial.println(ultrasoundRight.getDist());
  delay(100);
}

// Lower bound for ultrasound readings is 20 +- 1