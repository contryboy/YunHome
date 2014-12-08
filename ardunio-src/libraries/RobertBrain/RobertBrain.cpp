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
	}



}


void RobertBrain::detectObject() {

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

	Block object = m_robertEye.getBiggestObject();

	int distance = DistanceMeasure::getDistanceInMm();
	//Serial.print(distance);
	//Serial.println("mm");

	if (m_robertEye.isValidObject(object)) {

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


void RobertBrain::adjustPositionDistance() {

	Block object = m_robertEye.getBiggestObject();


	//Serial.print(distance);
	//Serial.println("mm");

	if (m_robertEye.isValidObject(object)) {
		m_vehicle.stop();//make the volt stable for measure distance
		delay(50);

		int distance = DistanceMeasure::getDistanceInMm();
		if(distance < (TARGET_DISTANCE_MM_TO_OBJECT - POSITION_DISTANCE_MM_ACCURACY)) {
			m_vehicle.move(0-TrackedVehicle::MAX_SPEED_VALUE, 0-TrackedVehicle::MAX_SPEED_VALUE);
		} else if(distance > (TARGET_DISTANCE_MM_TO_OBJECT + POSITION_DISTANCE_MM_ACCURACY)){
			m_vehicle.move(TrackedVehicle::MAX_SPEED_VALUE, TrackedVehicle::MAX_SPEED_VALUE);
		} else {
			//m_currentMode = POSITION_DISTANCE_ADJUSTED;
		}

	} else {
		//Object missing in eye
		//Serial.println("Object missing");
		m_vehicle.stop();
	}
}

int RobertBrain::calculateApprochSpeed(int distance) {
	return 220;
	//if(distance > SLOW_DOWN_DISTANCE) {
	//	return TrackedVehicle::MAX_SPEED_VALUE;
	//} else {
	//	return TrackedVehicle::MIN_SPEED_VALUE;
	//}

}

int RobertBrain::calculateCircleSpeedByOffset(int offset) {
  return TrackedVehicle::MIN_SPEED_VALUE + (TrackedVehicle::MAX_SPEED_VALUE-TrackedVehicle::MIN_SPEED_VALUE) * abs(offset) / RobertEye::MIDDLE_X;
}
