#define ph Serial.println("hi");
#define reg 0xAD
// 0x57 raw gyro z
// 0x71 yaw

typedef unsigned char uc;

byte calibGyro[7];
byte readReq[7];

void setup() {
  // put your setup code here, to run once:
  Serial1.begin(115200);
  Serial.begin(9600);

  uint16_t checksum;

  calibGyro[0] = 's';
  calibGyro[1] = 'n';
  calibGyro[2] = 'p';
  calibGyro[3] = 0x00;
  calibGyro[4] = 0xB3;
  checksum = 's' + 'n' + 'p' + 0 + 0xB3;
  calibGyro[5] = checksum >> 8;
  calibGyro[6] = checksum & 0xFF;
}

bool bruh = true;

void loop() {
  delay(4000);
  if (bruh == true) {
    Serial1.write(calibGyro, 7);
//    bruh = false;
  }
}

enum st {
  S, N, P, PT, AD, DB, CS1, CS2
} state = S;
byte dataPos;
byte regPos;

byte b1;
byte b2;
byte b3;
byte b4;

void serialEvent1() {
  byte b = Serial1.read();
  switch (state) {
    case S:
//      Serial.println("-----------SNP------------");
      if (b == 's') state = N;
      else state = S;
      break;
    case N:
      if (b == 'n') state = P;
      else state = S;
      break;
    case P:
      if (b == 'p') state = PT;
      else state = S;
      break;
    case PT:
      Serial.println("---PT---");
      Serial.println(b);
      if (!(b & 128)) state = S;
      else if (b & 3) state = S;
      else if (b & 64) {
        state = AD;
        dataPos = b & 60;
        dataPos >>= 2;
        regPos = 4;
      } else {
        state = AD;
        dataPos = 1;
        regPos = 4;
      }
      break;
    case AD:
    Serial.println("---AD---");
    Serial.println(b);
//    Serial.println("--ENDAD--");
    if (b != reg) {state = S; break;}
      state = DB;
      break;
    case DB:
//      Serial.println("---DB---");
//      Serial.println(b);
      if (regPos == 4) b1 = b;
      if (regPos == 3) b2 = b;
      if (regPos == 2) b3 = b;
      if (regPos == 1) b4 = b;
      if (regPos == 1) {
        regPos = 4;
        if (dataPos == 1) state = CS1;
        else {
          dataPos--;
          }
      } else regPos--;
      break;
    case CS1:
      Serial.println("---CS1---");
      Serial.println(b);
      int16_t i; // for yaw and raw gyro z
      i = (((int16_t) b1) << 8) | ((int16_t) b2); // for yaw and raw gyro z
      //float i; // for gyro bias z
      //i = b1 << 24 | b2 << 16 | b3 << 8 | b4; // for gyro bias z
//      Serial.println(i); // for raw gyro z 
//      Serial.println((double) i / 91.02222); // for yaw
    
      state = CS2;
      break;
    case CS2:
      Serial.println("---CS2---");
      Serial.println(b);
      state = S;
      break;
  }
}
