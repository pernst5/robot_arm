#include <Servo.h>
Servo top;  
int top_pin = 4; 
Servo mid; 
int mid_pin = 3; 
Servo base; 
int base_pin = 2; 
int i;

const int VRyPin = A1;
const int VRxPin = A0;
const int SWPin  = 6;

int VRx = 0;        // value read from the horizontal pot
int VRy = 0;        // value read from the vertical pot
int SW = 0;         // value read from the switch

float AngleBase = 90;
float AngleMid = 90;
float AngleTop = 90;

void setup() {
  top.attach(top_pin); 
  mid.attach(mid_pin);
  base.attach(base_pin);

  Serial.begin(9600);
  pinMode(SWPin,INPUT_PULLUP);
}

void loop() {
  VRx = analogRead(VRxPin);
  VRy = analogRead(VRyPin);
  SW = digitalRead(SWPin);

  // print the results to the Serial Monitor:
  Serial.print("VRrx = ");
  Serial.print(VRx);
  Serial.print("\tVRry = ");
  Serial.print(VRy);
  Serial.print("\tSW = ");
  Serial.println(SW);

 // delay(100);

  AngleBase = (180./1023) * VRx;
  Serial.println(AngleBase);
  base.write(AngleBase);

  AngleMid = -(180./1023) * VRy + 180;
  Serial.println(AngleMid);
  mid.write(AngleMid);
/*
  top.write(90);
  mid.write(90);
  base.write(90);

  delay(1000);

for(i=0 ; i<180 ; i++){
  base.write(i);
  delay(50);
  }
  
    mid.write(0);
    delay(800);
    mid.write(90);
    delay(200);
  
for(i=180 ; i>0 ; i--){
  base.write(i);
  delay(50);
  }
  
    mid.write(180);
    delay(800);
    mid.write(90);
    delay(200);
*/
}
