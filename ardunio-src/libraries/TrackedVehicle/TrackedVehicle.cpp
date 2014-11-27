#include "TrackedVehicle.h"
#include <Arduino.h>

TrackedVehicle::TrackedVehicle()
	//PWM pin for left is 3; for right is 6.
	: leftWheelMotor(3, 2, 4), rightWheelMotor(6, 5, 7){
}

void TrackedVehicle::begin() {
	leftWheelMotor.begin();
	rightWheelMotor.begin();
}
/**
 * speed: speed of the vehicle (0~255)
 * angel: 0: strait; <0: left; >0: right
 */
void TrackedVehicle::move(bool forward, int speed, int angel) {

	Serial.println("TrackedVehicle.forward()" );
	Serial.println(forward);
	Serial.println(speed);

	leftWheelMotor.run(forward, speed);
	rightWheelMotor.run(!forward, speed);
}

void TrackedVehicle::stop() {
	leftWheelMotor.stop();
	rightWheelMotor.stop();
}
