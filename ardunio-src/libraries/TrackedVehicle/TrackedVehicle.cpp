#include "TrackedVehicle.h"
#include <Arduino.h>

TrackedVehicle::TrackedVehicle()
	//PWM pin for left is 3; for right is 6.
	: leftWheelMotor(3, 4, 2), rightWheelMotor(6, 5, 7){
}

void TrackedVehicle::begin() {
	leftWheelMotor.begin();
	rightWheelMotor.begin();
}

/**
 * If speed > 0, forward
 * if speed = 0, stop
 * if speed < 0, backward
 */
void TrackedVehicle::move(int leftWheelSpeed, int rightWheelSpeed) {

	leftWheelMotor.run(leftWheelSpeed > 0, abs(leftWheelSpeed)); //for left wheel motor, same direction as vehicle
	rightWheelMotor.run(rightWheelSpeed < 0, abs(rightWheelSpeed)); //for left wheel motor, contract direction as vehicle
}

void TrackedVehicle::circle(bool left, int speed) {
	move((left ? 0-speed : speed), (left ? speed: 0-speed));
}

void TrackedVehicle::stop() {
	leftWheelMotor.stop();
	rightWheelMotor.stop();
}
