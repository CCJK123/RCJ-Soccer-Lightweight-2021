#include "Arduino.h"
#include "UM7.h"

#ifndef orientation_h
#define orientation_h

class Orientation : public UM7 {
  public:
    Orientation(HardwareSerial &serial);
    bool decode();
    float getYaw();
    float getMagZ();
    void zeroGyros();
    void calibrateAcc();
    void setMiscSettings();
  private:
    HardwareSerial *_serialPort;
};

#endif