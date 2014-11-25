#ifndef ____ArmServo__
#define ____ArmServo__

#include <Servo.h>
#include <Arduino.h>

class ArmServo
{
private:
	Servo m_servo;
	int m_signalPin;
	int m_straitAngel;
	int m_maxAngel;
	int m_minAngel;
	
	/* Speed index from 1(slow) ~ 10(fast) */
	int m_defaultSpeed;
	

	static const int stepAngel = 2;
	static const int stepDelay = 100;
	
public:
	ArmServo(int signalPin, int straitAngel, int minAngel, int maxAngel, int defaultSpeed);
	void begin();
	void moveToAngel(int targetAngel);
};
#endif /* defined(____ArmServo__) */
