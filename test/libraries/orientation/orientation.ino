#include "orientation.h"

Orientation imu(Serial1);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  imu.zeroGyros();
  imu.calibrateAcc();
  imu.setMiscSettings(); 
}

void loop() {
  // put your main code here, to run repeatedly:
}

void serialEvent1() {
  if (imu.decode()) {
    Serial.print(imu.getMagZ());
    Serial.print("    ");
    Serial.println(imu.getYaw());
  }
}
