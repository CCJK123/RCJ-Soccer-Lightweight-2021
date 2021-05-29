#include "temt.h"
#include "led.h"

LED led(12);

Temt temts[13] = {
  Temt(A0, 100), // front-facing for ball
  Temt(A12, 100),
  Temt(A5, 1024),
  Temt(A6, 1024),
  Temt(A10, 1024),
  Temt(A11, 1024),
  Temt(A4, 1024),
  Temt(A9, 1024),
  Temt(A8, 1024),
  Temt(A7, 1024),
  Temt(A3, 1024),
  Temt(A2, 1024),
  Temt(A1, 1024)
};

int writeValue;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial1.begin(9600);
}

bool isOnLine() {
  for (int i = 1; i < 13; i++) {
    if (i == 12) {
      Serial.print(" ");
      Serial.println(temts[i].getVal());
      
    } else {
      Serial.print(" ");
      Serial.print(temts[i].getVal());
    }
//    if (temts[i].isOnLine()) return true;
  }
  return false;
}

bool ballDetected() {
  return !temts[0].isOnLine();
}

void loop() {
  led.on();
  // put your main code here, to run repeatedly:
  if (!ballDetected() && !isOnLine()) { // no ball detected AND not on line
    writeValue = 0;
  } else if (ballDetected() && !isOnLine()) { // ball detected AND not on line
    writeValue = 1;
  } else if (!ballDetected() && isOnLine()) { // no ball detected AND on line
    writeValue = 2;
  } else if (ballDetected() && isOnLine()) { // ball detected AND on line
    writeValue = 3;
  }
  Serial1.write(writeValue);
  Serial.println(writeValue);
  delay(100);
}
