bool ballDetected, isOnLine;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial1.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
}

void serialEvent1() {
  int readValue = Serial1.read();
  if (readValue == 0) { // no ball detected AND not on line
    ballDetected = false;
    isOnLine = false;
  } else if (readValue == 1) { // ball detected AND not on line
    ballDetected = true;
    isOnLine = false;
  } else if (readValue == 2) { // no ball detected AND on line
    ballDetected = false;
    isOnLine = true;
  } else if (readValue == 3) { // ball detected AND on line
    ballDetected = true;
    isOnLine = true;
  }
  
  Serial.print(readValue);
  Serial.print(ballDetected);
  Serial.println(isOnLine);
}
