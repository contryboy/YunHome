
#include <Servo.h> 
#include <SPI.h>  
#include <Pixy.h>
#include "ArmController.h"
#include "TrackedVehicle.h"
#include "ArmServo.h"
#include "RobertEye.h"
#include "DistanceMeasure.h"
#include "RobertBrain.h"

RobertEye robertEye;
ArmController armController;
TrackedVehicle vehicle;
RobertBrain robertBrain(robertEye, armController, vehicle);

void setup() 
{
  //Must call this begore do serial print, it will set the baud
  armController.begin();
  robertEye.begin();
  vehicle.begin();
  
  delay(500);
  armController.setAllServoInMiddle();
  delay(500);
} 
 
void loop() 
{ 
  robertBrain.think();
  delay(20);
} 


void testVehicle() {
  
    vehicle.move(255, 255);
    delay(1000);
    vehicle.stop();
    //delay(1000);
    //vehicle.move(-255, -255);
    //delay(1000);
    //vehicle.stop();
    //delay(1000);
  
}

void testArm() 
{
    //testServo(armController.servo2);
    //testServo(armController.servo3);
    //testServo(armController.servo4);
    testServo(armController.servo5);
    //testServo(armController.servo6);
    //testServo(armController.servo7);
}

void testServo(ArmServo &servo)
{
   armController.moveServo(servo, 20);
   delay(1000);
   armController.moveServo(servo, 0);
   delay(1000);
   armController.moveServo(servo, -20);
   delay(1000);
   armController.moveServo(servo, 0);
}

