#include <Wire.h> 

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Wire.beginTransmission(0x01);
  Wire.write(8); Wire.endTransmission();
  Wire.requestFrom(0x01,1);
  while(!Wire.available());
  Serial.println(Wire.read());
  delay(100);
} 

// yellow scl a5
// brown sda a4 
