#define ph Serial.println("hi");
#define reg 0x8B
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
  calibGyro[4] = 0xAD;
  checksum = calibGyro[0] + calibGyro[1] + calibGyro[2] + calibGyro[3] + calibGyro[4];
  calibGyro[5] = checksum >> 8;
  calibGyro[6] = checksum & 0xFF;

  readReq[0] = 's';
  readReq[1] = 'n';
  readReq[2] = 'p';
  readReq[3] = 0x00;
  readReq[4] = reg;
  checksum = readReq[0] + readReq[1] + readReq[2] + readReq[3] + readReq[4];
  readReq[5] = checksum >> 8;
  readReq[6] = checksum & 0xFF;
}

bool bruh = true;

void loop() {
  if (bruh) {
    //Serial1.write(calibGyro, 7);
    bruh = true;
  }
  Serial1.write(readReq, 7);
   Serial1.write(calibGyro, 7);
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
    if (b != reg) {state = S; break;}
      state = DB;
      break;
    case DB:
      Serial.println(b);
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
      //int16_t i;
      //i = (((int16_t) b1) << 8) | ((int16_t) b2);
      float i;
      i = b1 << 24 | b2 << 16 | b3 << 8 | b4;
      Serial.println(i);
      //Serial.println((double) i / 91.02222);
    
      state = CS2;
      break;
    case CS2:
      state = S;
      break;
  }
}
