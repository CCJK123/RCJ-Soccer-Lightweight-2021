#include <ir.h>

IR ir(0);
IR ir1(1);

int prev[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int maxval;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
} 

void loop() {
  // put your main code here, to run repeatedly:
  if (ir1.maxVal() > ir.maxVal()) {
    maxval = ir1.maxVal();
  } else {
    maxval = ir.maxVal();
  }
  for (int i = 1; i < 20; i++){
    prev[i-1]=prev[i];
  }
  prev[19] = maxval;
  int sum = 0;
  for (int i = 0; i < 20; i++) {
    sum += prev[i];
//    Serial.print(prev[i]);
//    Serial.print("    ");
  }
  int avg = sum/20;
  if (avg<4) avg=-5;
  Serial.println(avg);
  delay(10);
} 

// yellow scl a5
// brown sda a4 void setup() {
  // put your setup code here, to run once:
