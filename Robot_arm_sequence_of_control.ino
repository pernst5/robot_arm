// This code is a hard coded sequence of motions for the small servo robotic arm. This code picks up a small basket and moves it and drops it off in a new location. Video in photos

#include <Servo.h>
Servo Elbow;  
int Elbow_pin = 4; 
Servo Shoulder; 
int Shoulder_pin = 3; 
Servo base; 
int base_pin = 2; 

double AngleBase;
double AngleShoulder;
double AngleElbow;

double AngleXL; // the angle between the base x coord. and the hypotenus length l

float sideLength = 6.7; // side length in cm
float x; // the x cordinate of the end (cm)
float y; // the y cordinate of the end (cm)
float hypLength = sqrt(2)*sideLength; // set inital hypotenus length to make a 45,45,90 triangle

int Xpot = A3; // Potentiometer pin to control x motion
int Ypot = A4; // Potentiometer pin to control y motion

void setup() {
  Elbow.attach(Elbow_pin); 
  Shoulder.attach(Shoulder_pin);
  base.attach(base_pin);

  Serial.begin(9600);
}

void loop() {
  base.write(180);
  set_arm_position (6,6);
    delay(1000);

  //Pick up pay load
  for ( int theta = 180 ; theta > 0 ; theta = theta - 1) {
  base.write(theta);
    delay(10); }
  for ( x = 4 ; x < 11 ; x = x + .1) {
  set_arm_position (x,3.5);
    delay(50); }
  delay(1000);

   //Move pay load
  set_arm_position (11,4);
    delay(200);
  set_arm_position (11,6);
    delay(500);
  set_arm_position (6,6);
  for ( x = 11 ; x > 6 ; x = x - .1) {
  set_arm_position (x,6);
    delay(50); }
  set_arm_position (6,8);
    delay(500);
  for ( int theta = 0 ; theta < 100 ; theta = theta + 1) {
  base.write(theta);
    delay(20);
  }
  set_arm_position (8,8);
    delay(1000);

  //Set down payload
  set_arm_position (8,6);
    delay(1000);
  for ( x = 8 ; x > 6 ; x = x - .1) {
  set_arm_position (x,6);
    delay(10); }
    delay(1000);
  base.write(180);
  set_arm_position (6,6);
    delay(100000);
}


void set_arm_position (float x, float y) {   
  // Calculate base angle and the hypotenus length
  double AngleXLrad = atan(y/x); // base angle in radians 
  AngleXL = 180. / PI * AngleXLrad; // AngleXL in degrees 
  //Serial.print("AngleXL is ");
  //Serial.println(AngleXL);  

  hypLength = x / cos(AngleXLrad);
  // Serial.print("hypLength is ");
  // Serial.println(hypLength);  

  
    // Calculate angles based on side length and hypotenus length
    AngleShoulder = acos(hypLength / (2 * sideLength)); // AngleShoulder in radians 
    AngleShoulder = 180. / PI * AngleShoulder; // AngleShoulder in radians 
    AngleElbow = 180 - 2 * AngleShoulder; // AngleShoulder in degrees
     
  
    AngleShoulder = AngleShoulder + AngleXL;
    //Serial.println(AngleShoulder);
    Shoulder.write(AngleShoulder);
  
    AngleElbow = 180 - AngleElbow;
    //Serial.println(AngleElbow);
    Elbow.write(AngleElbow);
}
