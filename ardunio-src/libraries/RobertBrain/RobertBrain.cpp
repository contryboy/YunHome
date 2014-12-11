/*
 * RobertBrain.cpp
 *
 *  Created on: Dec 4, 2014
 *      Author: zhangdong
 */

#include "RobertBrain.h"

RobertBrain::RobertBrain(RobertEye &robertEye, ArmController &armController, TrackedVehicle &vehicle,
		uint16_t targetObjectSignatureNumber, uint16_t containerObjectSignatureNumber)
	:m_robertEye(robertEye), m_armController(armController), m_vehicle(vehicle), m_currentMode(INIT),
	 m_targetObjectSignatureNumber(targetObjectSignatureNumber), m_containerObjectSignatureNumber(containerObjectSignatureNumber)
{

}

void RobertBrain::think() {

	//Serial.print("current mode: ");
	//Serial.println(m_currentMode);

	ActionResult result = runActionOfMode(m_currentMode);
	m_currentMode = transiteMode(m_currentMode, result);
}

RobertBrain::ActionMode RobertBrain::transiteMode(ActionMode oldMode, ActionResult oldModeActionResult) {

	if(REPEAT == oldModeActionResult) {
		return oldMode;
	} else {
		switch(oldMode) {
			case(INIT):
				if(OK == oldModeActionResult) return DETECTING_TARGET_OBJECT;
				break;
			case(DETECTING_TARGET_OBJECT):
				if(OK == oldModeActionResult) return APPROCHING_OBJECT;
				break;
			case(APPROCHING_OBJECT):
				if(OK == oldModeActionResult) return ADJUSTING_POSITION_DISTANCE;
				break;
			case(ADJUSTING_POSITION_DISTANCE):
				if(OK == oldModeActionResult) return ADJUSTING_POSITION_DEGREE;
				break;
			case(ADJUSTING_POSITION_DEGREE):
				if(OK == oldModeActionResult) return FETCHING_TENNIS_BALL;
				break;
			case(FETCHING_TENNIS_BALL):
				if(OK == oldModeActionResult) return DETECTING_CONTAINER;
				break;
			case(DETECTING_CONTAINER):
				if(OK == oldModeActionResult) return APPROCHING_CONTAINER;
				break;
			case(APPROCHING_CONTAINER):
				if(OK == oldModeActionResult) return RELEASING_TENNIS_BALL;
				break;
			case(RELEASING_TENNIS_BALL):
				if(OK == oldModeActionResult) return STEPING_BACK;
				break;
			case(STEPING_BACK):
				if(OK == oldModeActionResult) return INIT;
				break;
			}
	}

	return UNKNOWN;
}

RobertBrain::ActionResult RobertBrain::runActionOfMode(ActionMode actionMode) {
	switch(m_currentMode) {
		case(INIT):
			return init();
			break;
		case(DETECTING_TARGET_OBJECT):
			return detectObject(m_targetObjectSignatureNumber);
			break;
		case(APPROCHING_OBJECT):
			return approchObject(m_targetObjectSignatureNumber, TARGET_DISTANCE_MM_TO_OBJECT);
			break;
		case(ADJUSTING_POSITION_DISTANCE):
			return adjustPositionDistance();
			break;
		case(ADJUSTING_POSITION_DEGREE):
			return adjustPositionDegree();
			break;
		case(FETCHING_TENNIS_BALL):
			return fetchTennisBall();
			break;
		case(DETECTING_CONTAINER):
			return detectObject(m_containerObjectSignatureNumber);
			break;
		case(APPROCHING_CONTAINER):
			return approchObject(m_containerObjectSignatureNumber, TARGET_DISTANCE_MM_TO_CONTAINER);
			break;
		case(RELEASING_TENNIS_BALL):
			return releaseTennisBall();
			break;
		case(STEPING_BACK):
			return stepBack();
			break;
	}
}

RobertBrain::ActionResult RobertBrain::init() {
	//Init action can be done here if it is required.
	return OK;
}

RobertBrain::ActionResult RobertBrain::detectObject(uint16_t objectSignature) {

	Block object = m_robertEye.getBiggestObject(objectSignature);

	if (m_robertEye.isValidObject(object)) {
		m_vehicle.stop();
		delay(20);

		int offsetXToMiddle = m_robertEye.getXOffsetToMiddle(object);
		if (offsetXToMiddle < 0) {
			m_currentCircleDirection = true;
			m_vehicle.circle(m_currentCircleDirection, calculateCircleSpeedByOffset(offsetXToMiddle));
		} else if (offsetXToMiddle > 0) {
			m_currentCircleDirection = false;
			m_vehicle.circle(m_currentCircleDirection, calculateCircleSpeedByOffset(offsetXToMiddle));
		} else {
			m_vehicle.stop();
			return OK;
		}
	} else {
		//Serial.println(object.width);
		//if no object found, circle to looking for.
		m_vehicle.circle(m_currentCircleDirection, TrackedVehicle::MAX_SPEED_VALUE);
	}

	return REPEAT;
}


RobertBrain::ActionResult RobertBrain::approchObject(uint16_t objectSignature, int targetDistance) {

	m_vehicle.stop();
	delay(20);

	Block object = m_robertEye.getBiggestObject(objectSignature);

	if (m_robertEye.isValidObject(object)) {
		int distance = DistanceMeasure::getDistanceInMm();
		if(distance <= targetDistance) {
			m_vehicle.stop();
			return OK;

		} else {
			int speed = TrackedVehicle::MAX_SPEED_VALUE;
			int middleCheckAccuracy = APPROCH_FAR_MIDDLE_CHECK_ACCURACY;

			if(distance < SLOW_DOWN_DISTANCE) {
				speed = TrackedVehicle::MIN_SPEED_VALUE;
				middleCheckAccuracy = APPROCH_CLOSE_MIDDLE_CHECK_ACCURACY;
			}

			int offsetXToMiddle = m_robertEye.getXOffsetToMiddle(object, middleCheckAccuracy);
			if (offsetXToMiddle < 0) {
				m_vehicle.move(0, speed);
			} else if (offsetXToMiddle > 0) {
				m_vehicle.move(speed, 0);
			} else {
				m_vehicle.move(speed, speed);
			}
		}

	} else {
		//Object missing in eye
		//Serial.println("Object missing");
		m_vehicle.stop();
	}
	return REPEAT;
}


RobertBrain::ActionResult RobertBrain::adjustPositionDegree() {
	m_vehicle.stop();//make the vehicle stable for measure distance
	delay(25);
	Block object = m_robertEye.getBiggestObject(m_targetObjectSignatureNumber);

	if (m_robertEye.isValidObject(object)) {
		int offsetXToMiddle = m_robertEye.getXOffsetToMiddle(object);
		if (offsetXToMiddle < 0) {
			m_vehicle.circle(true, calculateCircleSpeedByOffset(offsetXToMiddle));
		} else if (offsetXToMiddle > 0) {
			m_vehicle.circle(false, calculateCircleSpeedByOffset(offsetXToMiddle));
		} else {
			return OK;
		}
	}

	return REPEAT;
}

RobertBrain::ActionResult RobertBrain::adjustPositionDistance() {

	m_vehicle.stop();//make the volt stable for measure distance
	delay(25);

	Block object = m_robertEye.getBiggestObject(m_targetObjectSignatureNumber);

	if (m_robertEye.isValidObject(object)) {
		int distance = DistanceMeasure::getDistanceInMm();
		if(distance < (TARGET_DISTANCE_MM_TO_OBJECT - POSITION_DISTANCE_MM_ACCURACY)) {
			m_vehicle.move(0-TrackedVehicle::MIN_SPEED_VALUE, 0-TrackedVehicle::MIN_SPEED_VALUE);
		} else if(distance > (TARGET_DISTANCE_MM_TO_OBJECT + POSITION_DISTANCE_MM_ACCURACY)){
			m_vehicle.move(TrackedVehicle::MIN_SPEED_VALUE, TrackedVehicle::MIN_SPEED_VALUE);
		} else {
			return OK;
		}
	}
	return REPEAT;
}

RobertBrain::ActionResult RobertBrain::fetchTennisBall() {
	m_armController.prepareGestureForFetch();
	delay(3000);
	m_armController.clipTennisBall();
	delay(2000);
	m_armController.handUp();
	delay(3000);
	return OK;
}

RobertBrain::ActionResult RobertBrain::releaseTennisBall() {
	m_armController.prepareGestureForRelease();
	delay(3000);
	m_armController.releaseTennisBall();
	delay(2000);
	m_armController.handUp();
	delay(3000);
	return OK;
}

RobertBrain::ActionResult RobertBrain::stepBack() {
	m_vehicle.move(0-TrackedVehicle::MAX_SPEED_VALUE, 0-TrackedVehicle::MAX_SPEED_VALUE);
	delay(500);
	m_vehicle.stop();
	return OK;
}

int RobertBrain::calculateApprochSpeed(int distance) {

	if(distance > SLOW_DOWN_DISTANCE) {
		return TrackedVehicle::MAX_SPEED_VALUE;
	} else {
		return TrackedVehicle::MIN_SPEED_VALUE;
	}
}

int RobertBrain::calculateCircleSpeedByOffset(int offset) {
  return TrackedVehicle::MIN_SPEED_VALUE + (TrackedVehicle::MAX_SPEED_VALUE-TrackedVehicle::MIN_SPEED_VALUE) * abs(offset) / RobertEye::MIDDLE_X;
}
