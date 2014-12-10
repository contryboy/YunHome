#ifndef TRACKEDVEHICLE_H_
#define TRACKEDVEHICLE_H_

#include "MotorController.h"

class TrackedVehicle {

public:
	//the lowest value that can move the vehicle
	const static int MIN_SPEED_VALUE = 220;
	const static int MAX_SPEED_VALUE = 255;

private:
	MotorController leftWheelMotor;
	MotorController rightWheelMotor;

public:
	TrackedVehicle();

	void begin();

	/**
	 * If speed > 0, forward
	 * if speed = 0, stop
	 * if speed < 0, backward
	 */
	void move(int leftWheelSpeed, int RightWheelSpeed);

	void circle(bool left, int speed);

	void stop();

};

#endif /* TRACKEDVEHICLE_H_ */
