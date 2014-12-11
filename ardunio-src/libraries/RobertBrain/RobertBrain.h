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
private:
	enum ActionMode {
		UNKNOWN,
		INIT,
		DETECTING_TARGET_OBJECT,
		APPROCHING_OBJECT,
		ADJUSTING_POSITION_DEGREE,
		ADJUSTING_POSITION_DISTANCE,
		FETCHING_TENNIS_BALL,
		DETECTING_CONTAINER,
		APPROCHING_CONTAINER,
		RELEASING_TENNIS_BALL,
		STEPING_BACK
	};

	enum ActionResult {
		OK, REPEAT
	};

	const static int TIME_PAUSE_FOR_MODE_CHANGE = 500;
	const static int TARGET_DISTANCE_MM_TO_OBJECT = 130;
	const static int TARGET_DISTANCE_MM_TO_CONTAINER = 100;
	const static int SLOW_DOWN_DISTANCE = 300;
	const static int POSITION_DISTANCE_MM_ACCURACY = 3;
	const static int APPROCH_FAR_MIDDLE_CHECK_ACCURACY = 10;
	const static int APPROCH_CLOSE_MIDDLE_CHECK_ACCURACY = 3;


	ActionMode m_currentMode;
	RobertEye &m_robertEye;
	ArmController &m_armController;
	TrackedVehicle &m_vehicle;

	uint16_t m_targetObjectSignatureNumber;
	uint16_t m_containerObjectSignatureNumber;

	bool m_currentCircleDirection = true;

	int calculateCircleSpeedByOffset(int offset);
	int calculateApprochSpeed(int distance);

public:
	RobertBrain(RobertEye &robertEye, ArmController &armController, TrackedVehicle &vehicle,
			uint16_t targetObjectSignatureNumber, uint16_t containerObjectSignatureNumber);
	void think();

private:

	ActionResult runActionOfMode(ActionMode actionMode);
	ActionMode transiteMode(ActionMode oldMode, ActionResult oldModeActionResult);
	ActionResult init();
	ActionResult detectObject(uint16_t objectSignature);
	ActionResult approchObject(uint16_t objectSignature, int targetDistance);
	ActionResult adjustPositionDegree();
	ActionResult adjustPositionDistance();
	ActionResult fetchTennisBall();
	ActionResult releaseTennisBall();
	ActionResult stepBack();


};

#endif /* ROBERTBRAIN_H_ */
