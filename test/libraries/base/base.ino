#include "motor.h"
#include "base.h"

Motor motor1(3, 5);
Motor motor2(6, 9);
Base base(motor1, motor2, motor1, motor2);

void setup() {}

void loop() {
  // put your main code here, to run repeatedly:
  base.rotate(0.1);
}
