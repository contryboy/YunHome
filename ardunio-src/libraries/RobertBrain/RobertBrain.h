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
	enum ActionMode {INIT,
		DETECTING_TARGET_OBJECT, TARGET_OBJECT_DETECTED,
		APPROCHING_OBJECT, OBJECT_APPROCHED,
		ADJUSTING_POSITION_DEGREE, POSITION_DEGREE_ADJUSTED,
		ADJUSTING_POSITION_DISTANCE, POSITION_DISTANCE_ADJUSTED,
		PREPARE_FETCH_GESTURE, FETCH_GESTURE_READY,
		CLIPPING_TENNIS_BALL, TENNIS_BALL_CLIPPED,
		HAND_UPING_WITH_BALL, HAND_UP_WITH_BALL_FINISHED,
		DETECTING_CONTAINER, CONTAINER_DETECTED,
		APPROCHING_CONTAINER, CONTAINER_APPROCHED,
		PREPARE_RELEASE_GESTURE, RELEASE_GESTURE_READY,
		RELEASING_TENNIS_BALL, TENNIS_BALL_RELEASED,
		HAND_UP_AND_BACK
	};


private:
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

public:
	void think();

private:
	bool detectObject(uint16_t objectSignature);
	bool approchObject(uint16_t objectSignature, int targetDistance);
	bool adjustPositionDegree();
	bool adjustPositionDistance();
	bool prepareFetchGesture();
	bool clipTennisBall();
	bool handUpWithBall();
	bool prepareReleaseGesture();
	bool releaseTennisBall();
	bool handUpAndBack();
};

#endif /* ROBERTBRAIN_H_ */
