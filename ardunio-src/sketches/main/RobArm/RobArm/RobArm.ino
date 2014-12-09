
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
  
  delay(1500);
  armController.setAllServoInMiddle();
  delay(500);
} 
 
void loop() 
{ 
  robertBrain.think();
  delay(25);
  /*armController.preparePositionForFetch();
  delay(10000);
  armController.setAllServoInMiddle();
  delay(10000);*/
} 

