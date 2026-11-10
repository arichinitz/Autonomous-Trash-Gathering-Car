
#include "HUSKYLENS.h";
//#include “SoftwareSerial.h”

HUSKYLENS huskylens;
void printResult(HUSKYLENSResult result);

// Motor control pins (adjust to match your specific motor driver)
int ena = 3;  // ENA for Motor 1
int in1 = 4;  // IN1 for Motor 1
int in2 = 5;  // IN2 for Motor 1
int enb = 6;  // ENB for Motor 2
int in3 = 7;  // IN3 for Motor 2
int in4 = 8;  // IN4 for Motor 2

bool objectFound = false;

void setup() {
// Motor pin setup
pinMode(ena, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enb, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  // Enable both motors (set ENA and ENB to HIGH)
  analogWrite(ena, 200);  // Enable Motor 1
  analogWrite(enb, 200);  // Enable Motor 2

// HuskyLens and serial communication
Serial.begin(115200);
Wire.begin();

while (!huskylens.begin(Wire)) {
Serial.println(F("Connection Failed!"));
}

// “ALGORITHM_OBJECT_TRACKING”
// “ALGORITHM_FACE_RECOGNITION”
// “ALGORITHM_OBJECT_RECOGNITION”
// “ALGORITHM_LINE_TRACKING”
// “ALGORITHM_COLOR_RECOGNITION”
// “ALGORITHM_TAG_RECOGNITION”
// “ALGORITHM_OBJECT_CLASSIFICATION”

// Start in object classification mode
huskylens.writeAlgorithm(ALGORITHM_COLOR_RECOGNITION);
delay(500);
}

void loop() {

while (objectFound == false) {

  Serial.println(F("circling"));
digitalWrite(in1, HIGH);  // Motor 1 forward
  digitalWrite(in2, LOW);   // Motor 1 forward
  digitalWrite(in3, LOW);  // Motor 2 backwards
  digitalWrite(in4, HIGH);   // Motor 2 backwards
delay(100);

digitalWrite(in1, LOW);  // Motor 1 forward
  digitalWrite(in2, LOW);   // Motor 1 forward
  digitalWrite(in3, LOW);  // Motor 2 backwards
  digitalWrite(in4, LOW);   // Motor 2 backwards
delay(300);


// Serial.println(F("circling"));
// digitalWrite(in1, HIGH);  // Motor 1 forward
//   digitalWrite(in2, LOW);   // Motor 1 forward
//   digitalWrite(in3, LOW);  // Motor 2 backwards
//   digitalWrite(in4, HIGH);   // Motor 2 backwards
// delay(1000);

huskylens.request();
HUSKYLENSResult result = huskylens.read();
printResult(result);
if (result.ID == 1) {
objectFound = true;
}
}

Serial.println(F("FOUND"));
while (objectFound == true) {

huskylens.request();
HUSKYLENSResult result = huskylens.read();
printResult(result);

moveForward(1000);

if (result.xCenter < 140) {
// Object is left of center, turn right
turnLeft(150);
} else if (result.xCenter > 180) {
// Object is right of center, turn left
turnRight(150);
} else {
//Object is centered, move forward

moveForward(1000);
}

}

}


void moveForward(int speed) {
digitalWrite(in1, HIGH);  // Motor 1 forward
  digitalWrite(in2, LOW);   // Motor 1 forward
  digitalWrite(in3, HIGH);  // Motor 2 forward
  digitalWrite(in4, LOW);   // Motor 2 forward
  delay(speed);
//Serial.println(F("Driving Straight"));
}

void turnLeft(int speed) {
digitalWrite(in1, HIGH);  // Motor 1 forward
  digitalWrite(in2, LOW);   // Motor 1 forward
  digitalWrite(in3, LOW);  // Motor 2 forward
  digitalWrite(in4, HIGH);   // Motor 2 forward
  delay(speed);
}

void turnRight(int speed) {
digitalWrite(in1, LOW);  // Motor 1 forward
  digitalWrite(in2, HIGH);   // Motor 1 forward
  digitalWrite(in3, HIGH);  // Motor 2 forward
  digitalWrite(in4, LOW);   // Motor 2 forward
  delay(speed);
}

void printResult(HUSKYLENSResult result) {
if (result.command == COMMAND_RETURN_BLOCK) {
Serial.println(String() + F("X Center")+ result.xCenter +F(" Y Center") + result.yCenter + F(" Width") + result.width + F(" Height") + result.height + F(" Color")  + result.ID);
} else if (result.command == COMMAND_RETURN_ARROW) {
//Serial.println(String() + F(“Arrow:xOrigin=”) + result.xOrigin + F(“,yOrigin=”) + result.yOrigin + F(“,xTarget=”) + result.xTarget + F(“,yTarget=”) + result.yTarget + F(“,ID=”) + result.ID);
} else {
Serial.println(F("Object Unknown!"));
}
}