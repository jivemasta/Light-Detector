#include <arduino.h>

//Digital Pins
int data = 2;
int clock = 3;
int latch = 4;

//Analog Pins
int leftEye = 0;
int rightEye = 1;

void updateLEDS(int);

void setup(){
  //Set Pins to output
  pinMode(data, OUTPUT);
  pinMode(clock,OUTPUT);
  pinMode(latch,OUTPUT);
}

void loop(){
  //the direction of the light source
  int level = 0;

  //Get the voltage on each analog pin
  int leftLevel = analogRead(leftEye);
  int rightLevel = analogRead(rightEye);

  //cancel out the values to get the direction of light
  level = (leftLevel-rightLevel);

  //map the result to a value between 0 and 7 which corresponds to each led
  level = map(level,-400,400,0,7);

  //update the leds by left shifting 0b00000001
  //each binary digit is the 'address' of an led
  updateLEDS(1 << level);
}

void updateLEDS(int value){
  //put the latch to low to shift the bits in
  digitalWrite(latch, LOW);

  //write the data to the shift register
  shiftOut(data, clock, MSBFIRST, value);

  //put the latch back to high
  digitalWrite(latch, HIGH);
}
