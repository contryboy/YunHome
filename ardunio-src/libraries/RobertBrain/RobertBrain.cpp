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

void RobertBrain::start() {
	while(true) {
		trackObject();
		delay(50);
	}
}

bool RobertBrain::checkIsObjectInEye() {

	return m_robertEye.getObjectCount() > 0;
}

void RobertBrain::trackObject() {

	boolean currentDirection = true;

	while(true) {
		Block object = m_robertEye.getBiggestObject();
		if (m_robertEye.isValidObject(object)) {
			int offsetXToMiddle = m_robertEye.getXOffsetToMiddle(object);
			if (offsetXToMiddle < 0) {
				currentDirection = true;
				m_vehicle.circle(currentDirection,
						calculateCircleSpeedByOffset(offsetXToMiddle));
			} else if (offsetXToMiddle > 0) {
				currentDirection = false;
				m_vehicle.circle(currentDirection,
						calculateCircleSpeedByOffset(offsetXToMiddle));
			} else {
				m_vehicle.stop();
				return;
			}
		} else {
			//if no object found, circle to looking for.
			m_vehicle.circle(currentDirection, 255);
		}

		delay(50);
	}
}



int RobertBrain::calculateCircleSpeedByOffset(int offset) {
  return TrackedVehicle::MIN_SPEED_VALUE + (TrackedVehicle::MAX_SPEED_VALUE-TrackedVehicle::MIN_SPEED_VALUE) * abs(offset) / RobertEye::MIDDLE_X;
}
