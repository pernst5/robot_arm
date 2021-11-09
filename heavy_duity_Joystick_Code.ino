#include <Servo.h>

#define joyX A0
#define joyY A1

#define joy2X A2
#define joy2Y A3

const int shoulder_pin = 9;
const int elbow_pin = 3;
const int joyButton = 10;
const int clawServoPin = 11;
const int baseServoPin = 12;

Servo elbow; 
Servo shoulder;
Servo baseServo;
Servo clawServo;

int basePosition = 90;
int clawServoPos = 30;
int shoulderPos = 90;
int elbowPos = 90;

void setup(){
clawServo.attach(clawServoPin);
clawServo.write(clawServoPos);
baseServo.attach(baseServoPin);
baseServo.write(basePosition);
shoulder.attach(shoulder_pin);
shoulder.write(shoulderPos);
elbow.attach(elbow_pin);
elbow.write(elbowPos);
digitalWrite(joyButton, HIGH);
}

void loop(){
int i;
i=0;


  int xValue;
  int yValue;
  int x2Value;
  int y2Value;
  int buttonVal = 0;

  bool clawState = false; //false for opne, true for closed
  xValue = analogRead(joyX);
  yValue = analogRead(joyY);
  y2Value = analogRead(joy2Y);
  buttonVal = digitalRead(joyButton);
 


  if(xValue > 550){
    basePosition = basePosition + 1;
    baseServo.write(basePosition);
    delay(20);
  }


  if(xValue < 450){
    basePosition = basePosition - 1;
    baseServo.write(basePosition);
        delay(20);
  }

  if(yValue > 550){
    shoulderPos = shoulderPos + 1;
    shoulder.write(shoulderPos);
    delay(20);
  }

  if(yValue < 450){
    shoulderPos = shoulderPos - 1;
    shoulder.write(shoulderPos);
        delay(20);
  }

  if(y2Value > 550){
    elbowPos = elbowPos - 1; 
    elbow.write(elbowPos);
    delay(20);
  }

  if(y2Value < 450){
    elbowPos = elbowPos + 1;
    elbow.write(elbowPos);
        delay(20 );
  }



  //claw control
  
  if (buttonVal == 1)
  {
       clawServo.write(30);  
  }
  else {
    clawServo.write(180);
  }

i++;
}