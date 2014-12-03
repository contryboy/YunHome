#include "ArmController.h"

ArmController::ArmController()
	: servo2(2, ArmServo::DEFAULT_FULL_US_RANGE, ArmServo::DEFAULT_MIDDLE_US),
	  servo3(3, ArmServo::DEFAULT_FULL_US_RANGE, ArmServo::DEFAULT_MIDDLE_US),
	  servo4(4, ArmServo::DEFAULT_FULL_US_RANGE, ArmServo::DEFAULT_MIDDLE_US),
	  servo5(5, ArmServo::DEFAULT_FULL_US_RANGE, ArmServo::DEFAULT_MIDDLE_US),
	  servo6(6, ArmServo::DEFAULT_FULL_US_RANGE, ArmServo::DEFAULT_MIDDLE_US),
	  servo7(7, ArmServo::DEFAULT_FULL_US_RANGE, ArmServo::DEFAULT_MIDDLE_US)
{

}

void ArmController::begin()
{
	Serial.begin(FIXED_DRIVER_BAUD);
}


void ArmController::setAllServoInMiddle()
{
	moveServo(servo2, 0);
	moveServo(servo3, 0);
	moveServo(servo4, 0);
	moveServo(servo5, 0);
	moveServo(servo6, 0);
	moveServo(servo7, 0);
}

void ArmController::moveServo(ArmServo &servo, int degreeAgainstMiddle)
{
	Serial.println(servo.getMoveCommand(degreeAgainstMiddle));
}
