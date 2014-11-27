#ifndef TRACKEDVEHICLE_H_
#define TRACKEDVEHICLE_H_

#include "MotorController.h"

class TrackedVehicle {

private:
	MotorController leftWheelMotor;
	MotorController rightWheelMotor;

public:
	TrackedVehicle();

	void begin();
	/**
	 * speed: speed of the vehicle (0~255)
	 * angel: 0: strait; <0: left; >0: right
	 */
	void move(bool forward, int speed, int angel);
	void stop();

};

#endif /* TRACKEDVEHICLE_H_ */
