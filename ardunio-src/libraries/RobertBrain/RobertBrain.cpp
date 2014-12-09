/*
 * RobertBrain.cpp
 *
 *  Created on: Dec 4, 2014
 *      Author: zhangdong
 */

#include "RobertBrain.h"

RobertBrain::RobertBrain(RobertEye &robertEye, ArmController &armController, TrackedVehicle &vehicle)
	:m_robertEye(robertEye), m_armController(armController), m_vehicle(vehicle), m_currentMode(INIT)
{
	// TODO Auto-generated constructor stub

}

void RobertBrain::think() {
	Serial.print("current mode: ");
	Serial.println(m_currentMode);
	switch(m_currentMode) {
		case(INIT):
			m_currentMode = DETECTING_OBJECT;
			break;
		case(DETECTING_OBJECT):
			detectObject();
			break;
		case(OBJECT_DETECTED):
			m_currentMode = APPROCHING_OBJECT;
			delay(200);
			break;
		case(APPROCHING_OBJECT):
			approchObject();
			break;
		case(OBJECT_APPROCHED):
			m_currentMode = ADJUSTING_POSITION_DISTANCE;
			delay(200);
			break;
		case(ADJUSTING_POSITION_DISTANCE):
			adjustPositionDistance();
			break;
		case(POSITION_DISTANCE_ADJUSTED):
			m_currentMode = ADJUSTING_POSITION_DEGREE;
			delay(200);
			break;
		case(ADJUSTING_POSITION_DEGREE):
			adjustPositionDegree();
			break;
		case(POSITION_DEGREE_ADJUSTED):
			m_currentMode = PREPARE_FETCH_GESTURE;
			delay(200);
			break;
		case(PREPARE_FETCH_GESTURE):
			prepareFetchGesture();
			break;
		case(FETCH_POSITION_GESTURE_READY):
			m_currentMode = CLIPPING_TENNIS_BALL;
			delay(200);
			break;
		case(CLIPPING_TENNIS_BALL):
			clipTennisBall();
			break;
		case(TENNIS_BALL_CLIPPED):
			m_currentMode = HAND_UPING_WITH_BALL;
			delay(200);
			break;
		case(HAND_UPING_WITH_BALL):
			handUpWithBall();
			break;
		case(HAND_UP_WITH_BALL_FINISHED):
			//to be continued.
			break;

	}
}


void RobertBrain::detectObject() {

	m_vehicle.stop();
	delay(25);

	Block object = m_robertEye.getBiggestObject();

	if (m_robertEye.isValidObject(object)) {
		int offsetXToMiddle = m_robertEye.getXOffsetToMiddle(object);
		if (offsetXToMiddle < 0) {
			m_currentCircleDirection = true;
			m_vehicle.circle(m_currentCircleDirection, calculateCircleSpeedByOffset(offsetXToMiddle));
		} else if (offsetXToMiddle > 0) {
			m_currentCircleDirection = false;
			m_vehicle.circle(m_currentCircleDirection, calculateCircleSpeedByOffset(offsetXToMiddle));
		} else {
			m_vehicle.stop();
			m_currentMode = OBJECT_DETECTED;
			return;
		}
	} else {
		//Serial.println(object.width);
		//if no object found, circle to looking for.
		m_vehicle.circle(m_currentCircleDirection, TrackedVehicle::MAX_SPEED_VALUE);
	}
}


void RobertBrain::approchObject() {

	m_vehicle.stop();
	delay(25);

	Block object = m_robertEye.getBiggestObject();

	if (m_robertEye.isValidObject(object)) {
		int distance = DistanceMeasure::getDistanceInMm();
		if(distance <= TARGET_DISTANCE_MM_TO_OBJECT) {
			m_vehicle.stop();
			m_currentMode = OBJECT_APPROCHED;
		} else {
			int offsetXToMiddle = m_robertEye.getXOffsetToMiddle(object);
			if (offsetXToMiddle < 0) {
				m_vehicle.move(0, calculateApprochSpeed(distance));
			} else if (offsetXToMiddle > 0) {
				m_vehicle.move(calculateApprochSpeed(distance), 0);
			} else {
				m_vehicle.move(calculateApprochSpeed(distance), calculateApprochSpeed(distance));
			}
		}

	} else {
		//Object missing in eye
		//Serial.println("Object missing");
		m_vehicle.stop();
	}
}


void RobertBrain::adjustPositionDegree() {
	m_vehicle.stop();//make the vehicle stable for measure distance
	delay(25);
	Block object = m_robertEye.getBiggestObject();

	if (m_robertEye.isValidObject(object)) {
		int offsetXToMiddle = m_robertEye.getXOffsetToMiddle(object);
		if (offsetXToMiddle < 0) {
			m_vehicle.circle(true, calculateCircleSpeedByOffset(offsetXToMiddle));
		} else if (offsetXToMiddle > 0) {
			m_vehicle.circle(false, calculateCircleSpeedByOffset(offsetXToMiddle));
		} else {
			m_currentMode = POSITION_DEGREE_ADJUSTED;
			return;
		}

	}
}

void RobertBrain::adjustPositionDistance() {

	m_vehicle.stop();//make the volt stable for measure distance
	delay(25);

	Block object = m_robertEye.getBiggestObject();

	if (m_robertEye.isValidObject(object)) {
		int distance = DistanceMeasure::getDistanceInMm();
		if(distance < (TARGET_DISTANCE_MM_TO_OBJECT - POSITION_DISTANCE_MM_ACCURACY)) {
			m_vehicle.move(0-TrackedVehicle::MIN_SPEED_VALUE, 0-TrackedVehicle::MIN_SPEED_VALUE);
		} else if(distance > (TARGET_DISTANCE_MM_TO_OBJECT + POSITION_DISTANCE_MM_ACCURACY)){
			m_vehicle.move(TrackedVehicle::MIN_SPEED_VALUE, TrackedVehicle::MIN_SPEED_VALUE);
		} else {
			m_currentMode = POSITION_DISTANCE_ADJUSTED;
		}
	}
}

void RobertBrain::prepareFetchGesture() {
	m_armController.preparePositionForFetch();
	delay(4000);
	m_currentMode = FETCH_POSITION_GESTURE_READY;
}

void RobertBrain::clipTennisBall() {
	m_armController.clipTennisBall();
	delay(3000);
	m_currentMode = TENNIS_BALL_CLIPPED;
}

void RobertBrain::handUpWithBall() {
	m_armController.handUp();
	delay(4000);
	m_currentMode = HAND_UP_WITH_BALL_FINISHED;
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
