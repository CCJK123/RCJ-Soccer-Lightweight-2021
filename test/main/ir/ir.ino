#include <ir.h>
//#define DB_IR
#define DB_BALL

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

IR ir_front;
int to_query[]={0, 5, 6, 7, 1, 2, 3, 4};
int angles_front[]={0, 90, 60, 30, 0, 330, 300, 270};

int front_high, back_high, front_ch, back_ch, left_high, right_high;

double ball;
double diff_left, diff_right, diff;

//Find angle and intensity of IR ball
void ir_ball(){
  //Get raw readings
  front_high = ir_front.maxVal();
  front_ch = ir_front.maxChannel();
//  Serial.print(front_high); Serial.print(" "); Serial.println(front_ch);

//  if(front_high > back_high){ //ball in front
  if (true) {
    diff = 15.0;
    if(front_ch != 7) left_high = ir_front.one(to_query[front_ch+1]); //check sensor to the left
    else { // left_high = ir_backto.one(to_query[1]); 
      diff = 0.0; } // use other IR

    if(front_ch != 1) right_high = ir_front.one(to_query[front_ch-1]); //check sensor to the right
    else { // right_high = ir_back.one(to_query[7]);
      diff = 0.0; } // use other IR
 
    diff_left = front_high-left_high;
    diff_right = front_high-right_high;

    if(left_high > right_high) ball = angles_front[front_ch]-(diff-((diff_left/diff_right)*diff)); //ball is slightly to the left
    else ball = (diff-((diff_right/diff_left)*diff))+angles_front[front_ch]; //ball is slightly to the right
    if(ball < 0) ball += 360.0;

//    lb = 0.0; ub = 2.0;
//    if(ball >= 345 || ball <= 15) front_mul = constrain(((double)(BALL_MAX-front_high))/FRONT_BALL_DIST_TRESH, lb, ub);
//    else front_mul = 2.0;
  } else { //ball in back
//    diff = 15.0;
//    back_mul = ((double)back_high)/BACK_BALL_DIST_TRESH;
//    if(back_mul > 1.0) back_mul = 1.0;
//
//    if(back_ch != 7) left_high = ir_back.one(to_query[back_ch+1]); //ball is slightly to the left
//    else { left_high = ir_front.one(to_query[1]); diff = 0.0; }
//    if(back_ch != 1) right_high = ir_back.one(to_query[back_ch-1]); //ball is slightly to the right
//    else { right_high = ir_front.one(to_query[7]); diff = 0.0; }
//    diff_left = back_high-left_high;
//    diff_right = back_high-right_high;
//
//    if(left_high > right_high) ball = angles_back[back_ch]-(diff-((diff_left/diff_right)*diff)); //ball is slightly to the left
//    else ball = (diff-((diff_right/diff_left)*diff))+angles_back[back_ch]; //ball is slightly to the right
//    if(ball < 0) ball += 360.0;
  }
  #ifdef DB_IR
    for(int i = 1; i <= 7; i++){ Serial.print(ir_front.one(to_query[i])); Serial.print(" "); }
    Serial.println();
//    for(int i = 1; i <= 7; i++){ Serial.print(ir_back.one(to_query[i])); Serial.print(" "); }
//    Serial.println();
  #endif
  #ifdef DB_BALL
//    Serial.print("IR: "); Serial.println(front_high); // max(front_high, back_high)
    Serial.print("ANG: "); Serial.println(ball);
  #endif
  
  /*c++;
  if(ball >= 180) t += 360-ball;
  else t += ball;
  Serial.println((int) (t/c));*/
}

void loop() {
  // put your main code here, to run repeatedly:
  ir_ball();
}
