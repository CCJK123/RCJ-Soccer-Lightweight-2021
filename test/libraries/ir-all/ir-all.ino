#include <ir.h>

IR ir;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print(ir.one(1));
  Serial.print(" ");
  Serial.print(ir.one(2));
  Serial.print(" ");
  Serial.print(ir.one(3));
  Serial.print(" ");
  Serial.print(ir.one(4));
  Serial.print(" ");
  Serial.print(ir.one(5));
  Serial.print(" ");
  Serial.print(ir.one(6));
  Serial.print(" ");
  Serial.print(ir.one(7));
  Serial.print(" ");
  Serial.print(ir.maxVal());
  Serial.print(" ");
  Serial.print(ir.maxChannel());
  Serial.print("\n");
  delay(100);
} 

// yellow scl a5
// brown sda a4 void setup() {
  // put your setup code here, to run once:
