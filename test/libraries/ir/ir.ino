#include "ir.h"

/*
Wire Connections
Yellow - SCL - Arduino A5 Pin
Brown - SDA - Arduino A4 Pin 
*/

IR ir;
int i2cPort = 0;

void setup() {
  // put your setup code here, to run once:
  ir.begin(i2cPort);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print(ir.maxVal(i2cPort));
  Serial.print(" ");
  Serial.print(ir.maxChannel(i2cPort));
  Serial.print("\n");
  delay(100);
}