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
#include "DistanceMeasure.h"

class RobertBrain {
public:
	enum ActionMode {INIT, DETECTING_OBJECT, OBJECT_DETECTED, APPROCHING_OBJECT, OBJECT_APPROCHED, ADJUSTING_POSITION_DISTANCE,
		POSITION_DISTANCE_ADJUSTED, OBJECT_MISSED, DRIVE_TO_OBJECT};

private:

	const static int TARGET_DISTANCE_MM_TO_OBJECT = 150;
	const static int SLOW_DOWN_DISTANCE = 500;
	const static int POSITION_DISTANCE_MM_ACCURACY = 10;

	ActionMode m_currentMode;
	RobertEye &m_robertEye;
	ArmController &m_armController;
	TrackedVehicle &m_vehicle;

	bool m_currentCircleDirection = true;

	int calculateCircleSpeedByOffset(int offset);
	int calculateApprochSpeed(int distance);
public:
	RobertBrain(RobertEye &robertEye, ArmController &armController, TrackedVehicle &vehicle);

public:
	void think();

private:
	void detectObject();
	void approchObject();
	void adjustPositionDistance();
};

#endif /* ROBERTBRAIN_H_ */
