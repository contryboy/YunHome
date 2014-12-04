/*
 * RobertBrain.h
 *
 *  Created on: Dec 4, 2014
 *      Author: zhangdong
 */

#ifndef ROBERTBRAIN_H_
#define ROBERTBRAIN_H_

#include <Arduino.h>
#include "ArmController.h"
#include "TrackedVehicle.h"
#include "ArmServo.h"
#include "RobertEye.h"

class RobertBrain {
public:
	enum ActionMode {INIT, DETECTING_OBJECT, CHECKING_IF_OBJECT_IN_EYE, DRIVE_TO_OBJECT};

private:
	ActionMode m_currentMode;
	RobertEye &m_robertEye;
	ArmController &m_armController;
	TrackedVehicle &m_vehicle;

	int calculateCircleSpeedByOffset(int offset);
public:
	RobertBrain(RobertEye &robertEye, ArmController &armController, TrackedVehicle &vehicle);

public:
	void start();
	bool checkIsObjectInEye();
	void trackObject();
};

#endif /* ROBERTBRAIN_H_ */
