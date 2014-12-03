
#include <Servo.h> 
#include <SPI.h>  
#include <Pixy.h>
#include "ArmController.h"
#include "TrackedVehicle.h"
#include "ArmServo.h"

//Pixy pixy;

ArmController armController;

TrackedVehicle vehicle;

void setup() 
{
  //Must call this begore do serial print, it will set the baud
  armController.begin();
  
  Serial.print("Starting...\n");
  
  //pixy.init();
  vehicle.begin();
  
  armController.setAllServoInMiddle();
  delay(1000);
} 
 
void loop() 
{ 
  /*int j;
  uint16_t blocks;
  char buf[32]; 
  
  blocks = pixy.getBlocks();
  
  if (blocks)
  {
      sprintf(buf, "Detected %d:\n", blocks);
      Serial.print(buf);
      for (j=0; j<blocks; j++)
      {
        sprintf(buf, "  block %d: ", j);
        Serial.print(buf); 
        pixy.blocks[j].print();
      }
  }  */
  
  //testVehicle();
  testArm();
  delay(1000);
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

void testArm() 
{
    testServo(armController.servo2);
    testServo(armController.servo3);
    testServo(armController.servo4);
    testServo(armController.servo5);
    testServo(armController.servo6);
    testServo(armController.servo7);
}

void testServo(ArmServo &servo)
{
   armController.moveServo(servo, 20);
   delay(1000);
   armController.moveServo(servo, 0);
   delay(1000);
   armController.moveServo(servo, -10);
   delay(1000);
   armController.moveServo(servo, 0);
}

