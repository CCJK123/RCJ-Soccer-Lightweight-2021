#include <Wire.h> 

class IR {
  public:
    IR() {
     Wire.begin();
    }
    
    int one(int channel) {  
        Wire.beginTransmission(0x01);
          Wire.write(channel); Wire.endTransmission();
        Wire.requestFrom(0x01,1);
        
        while(!Wire.available());
        return Wire.read();
    }
    
    int maxVal() {
      return one(9);
    }
    
    int maxiChannel() {
      return one(8);
    }
};

/*
Wire Connections
Yellow - SCL - Arduino A5 Pin
Brown - SDA - Arduino A4 Pin 
*/

IR ir;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(ir.maximum());
  delay(10);
}