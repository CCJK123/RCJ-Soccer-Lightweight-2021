#include <ir.h>

IR irFront(0); // uses Wire
IR irBack(1); // uses Wire1

int maxVal, maxChannel, leftHigh, rightHigh; // readings from sensor
double diff, diffLeft, diffRight;
double angle; // final output

int frontDeg[] = {-1, 90, 60, 30, 0, 330, 300, 270}; // front ir
int backDeg[] = {-1, 270, 240, 210, 180, 150, 120, 90}; // back ir

void setup() {
  Serial.begin(9600);
}

void loop() {
  if (irFront.maxVal() > irBack.maxVal()) { // ball is in front

    // get raw readings
    maxVal = irFront.maxVal();
    maxChannel = irFront.maxChannel();

    diff = 15.0; // half of the difference between each pair of channels (30 deg)
  
    if (maxChannel != 7) {
      leftHigh = irFront.one(maxChannel + 1); // checks the channel to the left (+1 because it is mounted upside down)
    } else { // maxChannel is left most channel
      leftHigh = irBack.one(1); // channel to the left is the right most channel of the back ir
      diff = 0.0; // no difference between the left most channel and the right most channel of the back ir
    }
    if (maxChannel != 1) {
      rightHigh = irFront.one(maxChannel - 1); // checks the channel to the right (-1 because it is mounted upside down)
    } else { // maxChannel is right most channel
      rightHigh = irBack.one(7); // channel to the right is the left most channel of the back ir
      diff = 0.0; // no difference between the right most channel and the left most channel of the back ir
    }
   
    diffLeft = maxVal - leftHigh; diffRight = maxVal - rightHigh; // get the difference between the maximum reading and the reading of the channels adjacent to it
  
    if (leftHigh > rightHigh) { // ball is to the left
      angle = frontDeg[maxChannel] - diff * (1 - diffLeft / diffRight);
    } else { // ball is to the right
      angle = frontDeg[maxChannel] + diff * (1 - diffRight / diffLeft);
    }

  } else { // ball is behind

    // get raw readings
    maxVal = irBack.maxVal();
    maxChannel = irBack.maxChannel();

    diff = 15.0; // half of the difference between each pair of channels (30 deg)
  
    if (maxChannel != 7) {
      leftHigh = irBack.one(maxChannel + 1); // checks the channel to the left (+1 because it is mounted upside down)
    } else { // maxChannel is left most channel
      leftHigh = irFront.one(1); // channel to the left is the right most channel of the front ir
      diff = 0.0; // no difference between the left most channel and the right most channel of the front ir
    }
    if (maxChannel != 1) {
      rightHigh = irBack.one(maxChannel - 1); // checks the channel to the right (-1 because it is mounted upside down)
    } else { // maxChannel is right most channel
      rightHigh = irFront.one(7); // channel to the right is the left most channel of the front ir
      diff = 0.0; // no difference between the right most channel and the left most channel of the front ir
    }
   
    diffLeft = maxVal - leftHigh; diffRight = maxVal - rightHigh; // get the difference between the maximum reading and the reading of the channels adjacent to it
  
    if (leftHigh > rightHigh) { // ball is to the left
      angle = backDeg[maxChannel] - diff * (1 - diffLeft / diffRight);
    } else { // ball is to the right
      angle = backDeg[maxChannel] + diff * (1 - diffRight / diffLeft);
    }

  }

  if (angle < 0) angle += 360; // corrects negative angles

  Serial.println(angle);
  delay(100);
}
