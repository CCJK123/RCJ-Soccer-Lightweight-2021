#include <ir.h>

IR ir(0);

int maxVal, maxChannel, leftHigh, rightHigh;
double angle;
double diff, diffLeft, diffRight;

//int irAngles[] = {-1, 270, 300, 330, 0, 30, 60, 90};
int irAngles[] = {-1, 90, 60, 30, 0, 330, 300, 270};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // get raw readings
  maxVal = ir.maxVal(); maxChannel = ir.maxChannel();
//  Serial.print(ir.maxVal()); Serial.print(" "); Serial.println(ir.maxChannel());
  diff = 15.0; // half of the fov (30 deg)

  if (maxChannel != 1) {
    leftHigh = ir.one(maxChannel + 1);
  }

  if (maxChannel != 7) {
    rightHigh = ir.one(maxChannel - 1);
  }
 
  diffLeft = maxVal - leftHigh;
  diffRight = maxVal - rightHigh;

  if (leftHigh > rightHigh) { // ball is to the left
    angle = irAngles[maxChannel]-diff*(1-diffLeft/diffRight);
  } else { // ball is to the right
    angle = irAngles[maxChannel]+diff*(1-diffRight/diffLeft);
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
