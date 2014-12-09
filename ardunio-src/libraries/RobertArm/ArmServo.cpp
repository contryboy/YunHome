#include "ArmServo.h"



ArmServo::ArmServo(int connectorNumber, long fullUs, long middleUs, int speed, bool forwardDirection)
{
	m_connectorNumber = connectorNumber;
	m_fullUs = fullUs;
	m_middleUs = middleUs;
	m_forwardDirection = forwardDirection;
	m_maxAngelAgainstMiddle = DEFAULT_MAX_ANGEL_AGAINST_MIDDLE;
	m_minAngelAgainstMiddle = DEFAULT_MIN_ANGEL_AGAINST_MIDDLE;
	m_speed = speed;
	
}

void ArmServo::setMiddleUs(int middleUs)
{
	m_middleUs = middleUs;
}

String ArmServo::getMoveCommand(int angelOffsetInDegree) {
	long offsetInUs = angelOffsetInDegree * m_fullUs / 180;
	offsetInUs = m_forwardDirection ? offsetInUs : (0 - offsetInUs);
	long absoluteInUs = m_middleUs + offsetInUs;
	return String("#") + m_connectorNumber + " P" + absoluteInUs + " S" + m_speed + " ";
}
