#include "ir.h"

IR::IR(int wire) {
    _wire = wire;
    if (_wire == 0) {
        Wire.begin();
    } else {
        Wire1.begin();
    }
}

int IR::one(int channel) {
    if (channel <= 7) {
        // Channel:      1 2 3 4 5 6 7
        // No. to Write: 5 6 7 1 2 3 4
        int mapping[] = {5, 6, 7, 1, 2, 3, 4};
        channel = mapping[channel-1];
    }
  if (_wire == 0) {
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

int IR::maxVal() {
    return one(9);
}

int IR::maxChannel() {
    return one(8);
}
