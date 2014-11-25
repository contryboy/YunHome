
#include <Servo.h> 
#include "ArmController.h"
#include "ArmServo.h"


ArmServo myservo2(2, 90, 40, 120, 5);
ArmServo myservo3(3, 90, 40, 120, 8);
ArmServo myservo4(4, 90, 40, 120, 10);
ArmServo myservo5(5, 90, 40, 120, 10);
ArmServo myservo6(6, 90, 40, 120, 10);
ArmServo myservo7(7, 90, 40, 120, 10);

const int stepAngel = 2;
const int stepDelay = 100;

void setup() 
{ 
  myservo2.begin();
  myservo3.begin();
  myservo4.begin();
  myservo5.begin();
  myservo6.begin();
  myservo7.begin();
} 
 
void loop() 
{ 
  
  
  
  delay(5000);
  
  while(true)
  {
    
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
} 


