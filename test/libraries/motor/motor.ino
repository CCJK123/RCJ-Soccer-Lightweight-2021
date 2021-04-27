#include "motor.h"

Motor motor1(3, 5);
Motor motor2(6, 9);

void setup() {}

void loop() {
  // put your main code here, to run repeatedly:
  motor1.setSpeed(0.1);
  motor2.setSpeed(0.1);
  /*delay(2000);
  motor1.setSpeed(0);
  motor2.setSpeed(0);
  delay(2000);
  motor1.setSpeed(-0.1);
  motor2.setSpeed(-0.1);
  delay(2000);
  motor1.setSpeed(0);
  motor2.setSpeed(0);
  delay(2000);*/
}
