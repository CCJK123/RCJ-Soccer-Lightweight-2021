#include <temt.h>

Temt temt(A0, 670);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(temt.update());
  Serial.println(temt.updatePercent());
  delay(100);
}
