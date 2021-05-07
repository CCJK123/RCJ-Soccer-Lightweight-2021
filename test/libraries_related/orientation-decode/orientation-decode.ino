#define ph Serial.println("hi");
typedef unsigned char uc;

byte packet[7];

void setup() {
  // put your setup code here, to run once:
  Serial1.begin(115200);
  Serial.begin(9600);

packet[0] = 's';
packet[1] = 'n';
packet[2] = 'p';
packet[3] = 0x00;
packet[4] = 0x71;
packet[5] = 0x01;
packet[6] = 0xc2;

}

void loop() {
  Serial1.write(packet, 7);
}

enum st {
  S, N, P, PT, AD, DB, CS1, CS2
} state = S;
byte dataPos;
byte regPos;

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
      Serial.println("----- PACKET -----");
      Serial.println(b, BIN);
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
    if (b != 0x71) {state = S; break;}
      Serial.println(" --- ADDRESS  --- ");
      Serial.println(b, HEX);
      Serial.println(" --- REGISTER --- ");
      state = DB;
      break;
    case DB:
      Serial.println(b);
      if (regPos == 1) {
        regPos = 4;
        if (dataPos == 1) state = CS1;
        else {
          dataPos--;
          Serial.println(" --- REGISTER --- ");
          }
      } else regPos--;
      break;
    case CS1:
      Serial.println(" --- CHECKSUM --- ");
      Serial.println(b, BIN);
      state = CS2;
      break;
    case CS2:
      Serial.println(" --- CHECKSUM --- ");
      Serial.println(b, BIN);
      state = S;
      break;
  }
}