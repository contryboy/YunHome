
#include <Servo.h> 
 
Servo myservo2; 
Servo myservo3;
Servo myservo4;
Servo myservo5;
Servo myservo6;
Servo myservo7;

const int stepAngel = 2;
const int stepDelay = 100;

void setup() 
{ 
  myservo2.attach(2);
  myservo3.attach(3);
  myservo4.attach(4);
  myservo5.attach(5);
  myservo6.attach(6);
  myservo7.attach(7);
  
  
  setServoAngel(myservo2, 90, 10);
  setServoAngel(myservo3, 90, 10);
  setServoAngel(myservo4, 90, 10);
  setServoAngel(myservo5, 90, 10);
  setServoAngel(myservo7, 90, 10);  
  setServoAngel(myservo6, 90, 10);
  
} 
 
void loop() 
{ 
  
  
  
  delay(5000);
  
  while(true)
  {
    
    setServoAngel(myservo7, 130, 5);
    setServoAngel(myservo3, 130, 8);
    setServoAngel(myservo4, 130, 10);
    setServoAngel(myservo5, 130, 10);
    setServoAngel(myservo2, 110, 2);
    
    setServoAngel(myservo6, 125, 10);
    
    delay(500);
    setServoAngel(myservo7, 40, 5);
    setServoAngel(myservo3, 40, 8);
    setServoAngel(myservo4, 40, 10);
    setServoAngel(myservo5, 40, 10);
    setServoAngel(myservo2, 60, 2);
    
    setServoAngel(myservo6, 60, 10);
    
    delay(500);
    setServoAngel(myservo2, 90, 2);
    setServoAngel(myservo7, 90, 5);
    setServoAngel(myservo3, 90, 8);
    setServoAngel(myservo4, 90, 10);
    setServoAngel(myservo5, 90, 10);
    
    setServoAngel(myservo6, 90, 10);
    delay(2000); 
    
  } 
} 

void setServoAngel(Servo &servo, int targetAngel, int speedXX) {
  
  int currentStepDelay = stepDelay/speedXX;
  
  int currentAngel = servo.read();
  
  if(targetAngel > currentAngel) {
    while(currentAngel < targetAngel) {
      currentAngel += stepAngel;
      servo.write(currentAngel);
      delay(currentStepDelay);
    }
    
  } else if (targetAngel < currentAngel) {
    while(currentAngel > targetAngel) {
      currentAngel -= stepAngel;
      servo.write(currentAngel);
      delay(currentStepDelay);
    }
  }

}

