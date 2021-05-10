#include "Arduino.h"
#include <UM7.h>

#ifndef orientation_h
#define orientation_h

class Orientation : public UM7 {
  public:
    Orientation(HardwareSerial &serial);
    bool decode();
    float getYaw();
    void zeroGyros();
    void calibrateAcc();
  private:
    HardwareSerial *_serialPort;
};

#endif