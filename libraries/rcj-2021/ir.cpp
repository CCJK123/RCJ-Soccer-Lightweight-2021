#include "ir.h"

IR::IR() {
    Wire.begin();
}

int IR::one(int channel) {
    Wire.beginTransmission(0x01);
    Wire.write(channel); Wire.endTransmission();
    Wire.requestFrom(0x01,1);
    
    while(!Wire.available());
    return Wire.read();
}

int IR::maxVal() {
    return one(9);
}

int IR::maxChannel() {
    return one(8);
}