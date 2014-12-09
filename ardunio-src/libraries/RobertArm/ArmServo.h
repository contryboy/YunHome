#ifndef ____ArmServo__
#define ____ArmServo__

#include <Arduino.h>

#define FIXED_DRIVER_BAUD 115200

class ArmServo
{

public:
	
	//Default, 1500 is in the middle, but it is adjustble
	static const long DEFAULT_MIDDLE_US = 1500;
	//Default, a range of 1000us ~= 180 degree
	static const long DEFAULT_FULL_US_RANGE = 1500;
	
	static const int DEFAULT_SPEED = 200;
	static const int DEFAULT_MAX_ANGEL_AGAINST_MIDDLE = 40;
	static const int DEFAULT_MIN_ANGEL_AGAINST_MIDDLE = -40;

private:
	
	int m_connectorNumber;
	long m_fullUs;
	long m_middleUs;
	int m_maxAngelAgainstMiddle;
	int m_minAngelAgainstMiddle;
	
	/* Speed in us/s for servo */
	int m_speed;

	/* Depends on the hardware setup, when parameter of getMoveCommand, it should forward*/
	bool m_forwardDirection = true;

	
public:
	ArmServo(int connectorNumber, long fullUs, long middleUs, int speed, bool forwardDirection);
	void setMiddleUs(int middleUs);
	/**
	 * Get the command of moving the an offset degree against middle (90 degree)
	 */
	String getMoveCommand(int angelOffsetInDegree);
};
#endif /* defined(____ArmServo__) */
