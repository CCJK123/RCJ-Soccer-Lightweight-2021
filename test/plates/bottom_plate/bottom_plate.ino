#include "led.h"
#include "temt.h"

LED led(12);
Temt temt1(A0, 1);
Temt temt2(A12, 1);
Temt temt3(A5, 1);
Temt temt4(A6, 1);
Temt temt5(A10, 1);
Temt temt6(A11, 1);
Temt temt7(A4, 1);
Temt temt8(A9, 1);
Temt temt9(A8, 1);
Temt temt10(A7, 1);
Temt temt11(A3, 1);
Temt temt12(A2, 1);
Temt temt13(A1, 1);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  led.on();
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("temt1 = ");
  Serial.print(temt1.update());
  Serial.print(", temt2 = ");
  Serial.print(temt2.update());
  Serial.print(", temt3 = ");
  Serial.print(temt3.update());
  Serial.print(", temt4 = ");
  Serial.print(temt4.update());
  Serial.print(", temt5 = ");
  Serial.print(temt5.update());
  Serial.print(", temt6 = ");
  Serial.print(temt6.update());
  Serial.print(", temt7 = ");
  Serial.print(temt7.update());
  Serial.print(", temt8 = ");
  Serial.print(temt8.update());
  Serial.print(", temt9 = ");
  Serial.print(temt9.update());
  Serial.print(", temt10 = ");
  Serial.print(temt10.update());
  Serial.print(", temt11 = ");
  Serial.print(temt11.update());
  Serial.print(", temt12 = ");
  Serial.print(temt12.update());
  Serial.print(", temt13 = ");
  Serial.println(temt13.update());
  delay(100);
}