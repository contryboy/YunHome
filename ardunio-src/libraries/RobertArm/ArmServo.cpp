#include "ArmServo.h"



ArmServo::ArmServo(int connectorNumber, int fullUs, int middleUs)
{
	m_connectorNumber = connectorNumber;
	m_fullUs = fullUs;
	m_middleUs = middleUs;

	m_maxAngelAgainstMiddle = DEFAULT_MAX_ANGEL_AGAINST_MIDDLE;
	m_minAngelAgainstMiddle = DEFAULT_MIN_ANGEL_AGAINST_MIDDLE;
	m_speed = DEFAULT_SPEED;
	
}

String ArmServo::getMoveCommand(int angelOffsetInDegree) {
	int offsetInUs = angelOffsetInDegree * m_fullUs / 180;
	int absoluteInUs = m_middleUs + offsetInUs;
	return String("#") + m_connectorNumber + " P" + absoluteInUs + " S" + m_speed + " ";
}
