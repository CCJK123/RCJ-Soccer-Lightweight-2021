#include "ir.h"

/*
Wire Connections
Yellow - SCL - Arduino A5 Pin
Brown - SDA - Arduino A4 Pin 
*/

IR ir(0); // 0 for Wire or 1 for Wire1

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print(ir.maxVal());
  Serial.print(" ");
  Serial.print(ir.maxChannel());
  Serial.print("\n");
  delay(100);
}
