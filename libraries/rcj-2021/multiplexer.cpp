#include "multiplexer.h"

Multiplexer::Multiplexer(uint8_t address) {
    _address = address; // 8 possible addresses for multiplexer from 0x70 to 0x77
    Wire.begin();
}

void Multiplexer::select(uint8_t channel) { // selects one out of the 8 possible channels
    if (channel > 7) return;
 
    Wire.beginTransmission(_address);
    Wire.write(1 << channel);
    Wire.endTransmission();
}

void Multiplexer::stop() { // disables all channels on multiplexer
    Wire.beginTransmission(_address);
    Wire.write(0);
    Wire.endTransmission();
}