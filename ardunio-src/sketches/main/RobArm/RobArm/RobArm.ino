
#include <Servo.h> 
#include "ArmController.h"
#include "ArmServo.h"
#include "TrackedVehicle.h"

ArmServo myservo2(8, 90, 40, 120, 5);
ArmServo myservo3(9, 90, 40, 120, 8);
ArmServo myservo4(10, 90, 40, 120, 10);
ArmServo myservo5(11, 90, 40, 120, 10);
ArmServo myservo6(12, 90, 40, 120, 10);
ArmServo myservo7(13, 90, 40, 120, 10);

TrackedVehicle vehicle;

const int stepAngel = 2;
const int stepDelay = 100;

void setup() 
{ 
  
  Serial.begin(57600);

  // for debugging, wait until a serial console is connected
  //delay(4000);
  //while (!Serial) { ; }
  //Serial.print("Start... ");
  
  myservo2.begin();
  myservo3.begin();
  myservo4.begin();
  myservo5.begin();
  myservo6.begin();
  myservo7.begin();
  
  vehicle.begin();
  
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  
} 
 
void loop() 
{ 
  delay(5000);
  while(true) {
    testVehicle();
    testArm();
  }
} 

void testVehicle() {
  
    vehicle.move(true, 255, 0);
    delay(2000);
    vehicle.stop();
    delay(2000);
    vehicle.move(false, 255, 0);
    delay(2000);
    vehicle.stop();
    delay(2000);
  
}

void testArm() {
  
    
    myservo7.moveToAngel(120);
    myservo3.moveToAngel(120);
    myservo4.moveToAngel(120);
    myservo5.moveToAngel(120);
    myservo2.moveToAngel(110);
    myservo6.moveToAngel(120);
    
    delay(500);
    myservo7.moveToAngel(40);
    myservo3.moveToAngel(40);
    myservo4.moveToAngel(40);
    myservo5.moveToAngel(40);
    myservo2.moveToAngel(60);
    myservo6.moveToAngel(40);
    
    
    delay(500);
    myservo2.moveToAngel(90);
    myservo7.moveToAngel(90);
    myservo3.moveToAngel(90);
    myservo4.moveToAngel(90);
    myservo5.moveToAngel(90);
    myservo6.moveToAngel(90);
    
    delay(2000); 
}

