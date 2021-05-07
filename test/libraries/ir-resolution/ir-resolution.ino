#include <ir.h>

IR irFront(0);
IR irBack(1);

int maxVal, maxChannel, leftHigh, rightHigh;
double angle;
double diff, diffLeft, diffRight;

//int irAngles[] = {-1, 270, 300, 330, 0, 30, 60, 90};
int frontDeg[] = {-1, 90, 60, 30, 0, 330, 300, 270};
int backDeg[] = {-1, 270, 240, 210, 180, 150, 120, 90};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  if (irFront.maxVal() > irBack.maxVal()) {
    // get raw readings
    maxVal = irFront.maxVal(); maxChannel = irFront.maxChannel();
  //  Serial.print(irFront.maxVal()); Serial.print(" "); Serial.println(irFront.maxChannel());
    diff = 15.0; // half of the fov (30 deg)
  
    if (maxChannel != 7) {
      leftHigh = irFront.one(maxChannel + 1);
    } else {
      diff = 0;
      leftHigh = irBack.one(1);
    }
  
    if (maxChannel != 1) {
      rightHigh = irFront.one(maxChannel - 1);
    } else {
      diff = 0;
      rightHigh = irBack.one(7);
    }
   
    diffLeft = maxVal - leftHigh;
    diffRight = maxVal - rightHigh;
  
    if (leftHigh > rightHigh) { // ball is to the left
      angle = frontDeg[maxChannel]-diff*(1-diffLeft/diffRight);
    } else { // ball is to the right
      angle = frontDeg[maxChannel]+diff*(1-diffRight/diffLeft);
    }
  } else {
    // get raw readings
    maxVal = irBack.maxVal(); maxChannel = irBack.maxChannel();
  //  Serial.print(irBack.maxVal()); Serial.print(" "); Serial.println(irBack.maxChannel());
    diff = 15.0; // half of the fov (30 deg)
  
    if (maxChannel != 7) {
      leftHigh = irBack.one(maxChannel + 1);
    } else {
      diff = 0;
      leftHigh = irFront.one(1);
    }
  
    if (maxChannel != 1) {
      rightHigh = irBack.one(maxChannel - 1);
    } else {
      diff = 0;
      rightHigh = irFront.one(7);
    }
   
    diffLeft = maxVal - leftHigh;
    diffRight = maxVal - rightHigh;
  
    if (leftHigh > rightHigh) { // ball is to the left
      angle = backDeg[maxChannel]-diff*(1-diffLeft/diffRight);
    } else { // ball is to the right
      angle = backDeg[maxChannel]+diff*(1-diffRight/diffLeft);
    }
  }
  
  if (angle<0) {
    angle += 360;
  }
//  Serial.print(maxVal);
//  Serial.print(" ");
//  Serial.print(maxChannel);
//  Serial.print(" ");
  Serial.println(angle);
  delay(100);
} 

// yellow scl a5
// brown sda a4 
