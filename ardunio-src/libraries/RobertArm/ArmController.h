#ifndef ____ArmController__
#define ____ArmController__

#include "ArmServo.h"

class ArmController
{
public:
	ArmServo servo2;
	ArmServo servo3;
	ArmServo servo4;
	ArmServo servo5;
	ArmServo servo6;
	ArmServo servo7;

public:
	ArmController();
	void begin();
	void moveServo(ArmServo &servo, int degreeAgainstMiddle);
	void setAllServoInMiddle();
	void prepareGestureForFetch();
	void clipTennisBall();
	void handUp();
	void prepareGestureForRelease();
	void releaseTennisBall();
};

#endif /* defined(____ArmController__) */
