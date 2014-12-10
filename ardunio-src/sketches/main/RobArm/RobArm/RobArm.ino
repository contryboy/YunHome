
#include <Servo.h> 
#include <SPI.h>  
#include <Pixy.h>
#include "ArmController.h"
#include "TrackedVehicle.h"
#include "ArmServo.h"
#include "RobertEye.h"
#include "DistanceMeasure.h"
#include "RobertBrain.h"

const static uint16_t TENNIS_SIGNATURE_NUMBER = 1;//signature 1
const static uint16_t CONTAINER_SIGNATURE_NUMBER = 19; // color code signature, cc1 and cc2 makes it 19 (010 011)

RobertEye robertEye;
ArmController armController;
TrackedVehicle vehicle;
RobertBrain robertBrain(robertEye, armController, vehicle, TENNIS_SIGNATURE_NUMBER, CONTAINER_SIGNATURE_NUMBER);

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
  /*armController.prepareGestureForRelease();
  delay(10000);
  armController.setAllServoInMiddle();
  delay(10000);*/
} 

