#include <arduino.h>

int data = 2;
int clock = 3;
int latch = 4;

int leftEye = 0;
int rightEye = 1;

void updateLEDS(int);

void setup(){
  pinMode(data, OUTPUT);
  pinMode(clock,OUTPUT);
  pinMode(latch,OUTPUT);
}

void loop(){
  int level = 3;
  int leftLevel = analogRead(leftEye);
  int rightLevel = analogRead(rightEye);

  level = (leftLevel-rightLevel);

  level = map(level,-400,400,0,7);

  updateLEDS(1 << level);
  //delay(250);
}

void updateLEDS(int value){
  digitalWrite(latch, LOW);
  shiftOut(data, clock, MSBFIRST, value);
  digitalWrite(latch, HIGH);
}
