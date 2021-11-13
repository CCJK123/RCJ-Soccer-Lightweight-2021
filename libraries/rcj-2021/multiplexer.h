// Library for the Adafruit TCA9548A 1-to-8 I2C Multiplexer Breakout
// Referenced https://learn.adafruit.com/adafruit-tca9548a-1-to-8-i2c-multiplexer-breakout/wiring-and-test

#include "Arduino.h"
#include <Wire.h>

#ifndef multiplexer_h
#define multiplexer_h

class Multiplexer {
    public:
        Multiplexer(uint8_t address);
        void select(uint8_t channel);
        void stop();
    private:
        uint8_t _address;
}

#endif