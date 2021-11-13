// Library for the Adafruit TCS34725 Color Sensor Driver
// Referenced https://learn.adafruit.com/adafruit-color-sensors/arduino-code and https://github.com/adafruit/Adafruit_TCS34725/

#include "Arduino.h"
#include <Wire.h>
#include <Adafruit_TCS34725.h>
#include "multiplexer.h"

#ifndef rgb_h
#define rgb_h

class RGB : public Multiplexer{
	public:
        RGB(uint8_t address, int channel, int threshold);
        int calcLux();
        double getPercent();
        int getThreshold();
        bool isOnLine();
	private:
        Adafruit_TCS34725 sensor;
        int _channel, _threshold;
};

#endif