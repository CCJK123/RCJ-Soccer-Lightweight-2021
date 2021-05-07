#include <ball.h>

IR irFront(0); // uses Wire
IR irBack(1); // uses Wire1
Ball ball(irFront, irBack);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(ball.getDeg());
  delay(10);
}
