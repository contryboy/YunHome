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
	// TODO Auto-generated constructor stub

}

void RobertBrain::think() {
	Serial.print("current mode: ");
	Serial.println(m_currentMode);
	switch(m_currentMode) {
		case(INIT):
			m_currentMode = DETECTING_TARGET_OBJECT;
			break;
		case(DETECTING_TARGET_OBJECT):
			if(detectObject(m_targetObjectSignatureNumber)) {
				m_currentMode = TARGET_OBJECT_DETECTED;
			}
			break;
		case(TARGET_OBJECT_DETECTED):
			m_currentMode = APPROCHING_OBJECT;
			delay(TIME_PAUSE_FOR_MODE_CHANGE);
			break;
		case(APPROCHING_OBJECT):
			if(approchObject(m_targetObjectSignatureNumber, TARGET_DISTANCE_MM_TO_OBJECT)) {
				m_currentMode = OBJECT_APPROCHED;
			}
			break;
		case(OBJECT_APPROCHED):
			m_currentMode = ADJUSTING_POSITION_DISTANCE;
			delay(TIME_PAUSE_FOR_MODE_CHANGE);
			break;
		case(ADJUSTING_POSITION_DISTANCE):
			if(adjustPositionDistance()) {
				m_currentMode = POSITION_DISTANCE_ADJUSTED;
			}
			break;
		case(POSITION_DISTANCE_ADJUSTED):
			m_currentMode = ADJUSTING_POSITION_DEGREE;
			delay(TIME_PAUSE_FOR_MODE_CHANGE);
			break;
		case(ADJUSTING_POSITION_DEGREE):
			if(adjustPositionDegree()) {
				m_currentMode = POSITION_DEGREE_ADJUSTED;
			}
			break;
		case(POSITION_DEGREE_ADJUSTED):
			m_currentMode = PREPARE_FETCH_GESTURE;
			delay(TIME_PAUSE_FOR_MODE_CHANGE);
			break;
		case(PREPARE_FETCH_GESTURE):
			if(prepareFetchGesture()) {
				m_currentMode = FETCH_GESTURE_READY;
			}
			break;
		case(FETCH_GESTURE_READY):
			m_currentMode = CLIPPING_TENNIS_BALL;
			delay(TIME_PAUSE_FOR_MODE_CHANGE);
			break;
		case(CLIPPING_TENNIS_BALL):
			if(clipTennisBall()) {
				m_currentMode = TENNIS_BALL_CLIPPED;
			}
			break;
		case(TENNIS_BALL_CLIPPED):
			m_currentMode = HAND_UPING_WITH_BALL;
			delay(TIME_PAUSE_FOR_MODE_CHANGE);
			break;
		case(HAND_UPING_WITH_BALL):
			if(handUpWithBall()) {
				m_currentMode = HAND_UP_WITH_BALL_FINISHED;
			}
			break;
		case(HAND_UP_WITH_BALL_FINISHED):
			m_currentMode = DETECTING_CONTAINER;
			delay(TIME_PAUSE_FOR_MODE_CHANGE);
			break;
		case(DETECTING_CONTAINER):
			if(detectObject(m_containerObjectSignatureNumber)) {
				m_currentMode = CONTAINER_DETECTED;
			}
			break;
		case(CONTAINER_DETECTED):
			m_currentMode = APPROCHING_CONTAINER;
			delay(TIME_PAUSE_FOR_MODE_CHANGE);
			break;
		case(APPROCHING_CONTAINER):
			if(approchObject(m_containerObjectSignatureNumber, TARGET_DISTANCE_MM_TO_CONTAINER)) {
				m_currentMode = CONTAINER_APPROCHED;
			}
			break;
		case(CONTAINER_APPROCHED):
			m_currentMode = PREPARE_RELEASE_GESTURE;
			delay(TIME_PAUSE_FOR_MODE_CHANGE);
			break;
		case(PREPARE_RELEASE_GESTURE):
			if(prepareReleaseGesture()) {
				m_currentMode = RELEASE_GESTURE_READY;
			}
			break;
		case(RELEASE_GESTURE_READY):
			m_currentMode = RELEASING_TENNIS_BALL;
			delay(TIME_PAUSE_FOR_MODE_CHANGE);
			break;
		case(RELEASING_TENNIS_BALL):
			if(releaseTennisBall()) {
				m_currentMode = TENNIS_BALL_RELEASED;
			}
			break;
		case(TENNIS_BALL_RELEASED):
			m_currentMode = HAND_UP_AND_BACK;
			delay(TIME_PAUSE_FOR_MODE_CHANGE);
			break;
		case(HAND_UP_AND_BACK):
			if(handUpAndBack()) {
				m_currentMode = INIT;
			}
			break;
	}
}

bool RobertBrain::detectObject(uint16_t objectSignature) {

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
			return true;
		}
	} else {
		//Serial.println(object.width);
		//if no object found, circle to looking for.
		m_vehicle.circle(m_currentCircleDirection, TrackedVehicle::MAX_SPEED_VALUE);
	}

	return false;
}


bool RobertBrain::approchObject(uint16_t objectSignature, int targetDistance) {

	m_vehicle.stop();
	delay(20);

	Block object = m_robertEye.getBiggestObject(objectSignature);

	if (m_robertEye.isValidObject(object)) {
		int distance = DistanceMeasure::getDistanceInMm();
		if(distance <= targetDistance) {
			m_vehicle.stop();
			return true;

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
	return false;
}


bool RobertBrain::adjustPositionDegree() {
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
			return true;
		}
	}

	return false;
}

bool RobertBrain::adjustPositionDistance() {

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
			return true;
		}
	}
	return false;
}

bool RobertBrain::prepareFetchGesture() {
	m_armController.prepareGestureForFetch();
	delay(4000);
	return true;
}

bool RobertBrain::clipTennisBall() {
	m_armController.clipTennisBall();
	delay(3000);
	return true;
}

bool RobertBrain::handUpWithBall() {
	m_armController.handUp();
	delay(4000);
	return true;
}

bool RobertBrain::prepareReleaseGesture() {
	m_armController.prepareGestureForRelease();
	delay(4000);
	return true;
}

bool RobertBrain::releaseTennisBall() {
	m_armController.releaseTennisBall();
	delay(4000);
	return true;
}

bool RobertBrain::handUpAndBack() {
	m_armController.handUp();
	delay(4000);
	m_vehicle.move(0-TrackedVehicle::MAX_SPEED_VALUE, 0-TrackedVehicle::MAX_SPEED_VALUE);
	delay(500);
	m_vehicle.stop();
	return true;
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
