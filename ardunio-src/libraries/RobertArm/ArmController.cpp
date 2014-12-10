#include "ArmController.h"

ArmController::ArmController()
	: servo2(2, ArmServo::DEFAULT_FULL_US_RANGE, ArmServo::DEFAULT_MIDDLE_US - 50, ArmServo::DEFAULT_SPEED, false),
	  servo3(3, ArmServo::DEFAULT_FULL_US_RANGE, ArmServo::DEFAULT_MIDDLE_US + 50, ArmServo::DEFAULT_SPEED, true),
	  servo4(4, ArmServo::DEFAULT_FULL_US_RANGE, ArmServo::DEFAULT_MIDDLE_US + 30, ArmServo::DEFAULT_SPEED, false),
	  servo5(5, ArmServo::DEFAULT_FULL_US_RANGE, ArmServo::DEFAULT_MIDDLE_US - 100, ArmServo::DEFAULT_SPEED, true),
	  servo6(6, ArmServo::DEFAULT_FULL_US_RANGE, ArmServo::DEFAULT_MIDDLE_US, ArmServo::DEFAULT_SPEED, false),
	  servo7(7, ArmServo::DEFAULT_FULL_US_RANGE, ArmServo::DEFAULT_MIDDLE_US + 10, ArmServo::DEFAULT_SPEED, true)
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

void ArmController::clipTennisBall() {
	moveServo(servo6, 55);
}

void ArmController::handUp() {
	moveServo(servo2, 0);
	delay(2000);
	moveServo(servo3, 0);
	moveServo(servo4, 0);
}

void ArmController::prepareGestureForFetch() {
	moveServo(servo2, 66);
	moveServo(servo3, 43);
	moveServo(servo4, 60);
}

void ArmController::prepareGestureForRelease() {
	moveServo(servo2, 30);
	moveServo(servo3, 40);
	moveServo(servo4, 20);
}

void ArmController::releaseTennisBall() {
	moveServo(servo6, 0);
}

