#include "Arduino.h"
#include "UM7.h"
#include "orientation.h"

Orientation::Orientation(HardwareSerial &serial) : UM7(serial) {
  _serialPort = &serial;

  _serialPort -> begin(115200); // Set baud rate on &serial to read at 115200 bps for the MCU
  UM7::set_sensor_baud_rate(115200); // Set the UM7 baud rate to output at 115200 bps to match the MCU

  // Set euler and all processed datasets to 255 Hz
  UM7::set_euler_rate(255);
  UM7::set_all_processed_rate(255);
}

bool Orientation::decode() {
  return UM7::decode(_serialPort -> read());
}

float Orientation::getYaw() {
  if (UM7::yaw < 0) {
    return 360 + UM7::yaw;
  } else {
    return UM7::yaw;
  }
}

float Orientation::getMagZ() {
  float magZ = (atan2(UM7::mag_x,UM7::mag_y) * 180) / 3.1415;
  if (magZ < 0) {
    return 360 + magZ;
  } else {
    return magZ;
  }
}

void Orientation::zeroGyros() {
  UM7::zero_gyros();
}

void Orientation::calibrateAcc() {
  UM7::calibrate_accelerometers();
}

void Orientation::setMiscSettings() {
  UM7::set_misc_ssettings(false, false, false, true);
}
