#include <Servo.h>
Servo Elbow;  
int Elbow_pin = 3; 
Servo Shoulder; 
int Shoulder_pin = 9; 
Servo base; 
int base_pin = 12;
Servo claw; 
int claw_pin = 11; 

double AngleBase;
double AngleShoulder;
double AngleElbow;

double AngleXL; // the angle between the base x coord. and the hypotenus length l

float sideLength = 10.2; // side length in cm
float x; // the x cordinate of the end (cm)
float y; // the y cordinate of the end (cm)
float hypLength = sqrt(2)*sideLength; // set inital hypotenus length to make a 45,45,90 triangle

int Xpot = A5; // Potentiometer pin to control x motion
int Ypot = A4; // Potentiometer pin to control y motion

void setup() {
  Elbow.attach(Elbow_pin); 
  Shoulder.attach(Shoulder_pin);
  base.attach(base_pin);

  Serial.begin(9600);
 // Shoulder.write(90);
 // Elbow.write(90);
//  delay(50000);
}

void loop() {
  //base.write(0);
  /*
  Serial.println("What x do you want?");
  while(Serial.available()==0) { }
  x = Serial.parseFloat();
  Serial.print("x set to ");
  Serial.println(x);  

  Serial.println("What y do you want?");
  while(Serial.available()==0) { }
  y = Serial.parseFloat();
  Serial.print("y set to ");
  Serial.println(y);  
  
  delay(1000);
  
*/
  
  int XpotValue = analogRead(Xpot);
  int YpotValue = analogRead(Ypot);
  x = XpotValue / 90.0;
  Serial.print("x is ");
  Serial.print(x);
  Serial.print("       ");
  y = YpotValue / 90.0;
  Serial.print("y is ");
  Serial.println(y);
  delay(100);

  


  
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
     
  
    AngleShoulder = 180 - (AngleShoulder + AngleXL);
    Serial.println(AngleShoulder);
    Shoulder.write(AngleShoulder);
  
    AngleElbow = 180 - AngleElbow;
    Serial.println(AngleElbow);
    Elbow.write(AngleElbow);
  
    // delay(1000);
}
