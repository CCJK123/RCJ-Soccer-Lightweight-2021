#include "ir.h"

IR::IR() {}

void IR::begin(int wire) {
  if (wire == 0) {
    Wire.begin();
  } else {
    Wire1.begin();
  }
}

int IR::getData(int wire, int channel) {
  if (wire == 0) {
    Wire.beginTransmission(0x01);
    Wire.write(channel); Wire.endTransmission();
    Wire.requestFrom(0x01,1);
    
    while(!Wire.available());
    return Wire.read();
  } else {
    Wire1.beginTransmission(0x01);
    Wire1.write(channel); Wire1.endTransmission();
    Wire1.requestFrom(0x01,1);
    
    while(!Wire1.available());
    return Wire1.read();
  }
}

int IR::maxVal(int wire) {
  return getData(wire, 9);
}

int IR::maxChannel(int wire) {
    return getData(wire, 8);
}