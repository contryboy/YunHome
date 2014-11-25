#include "ArmServo.h"



ArmServo::ArmServo(int signalPin, int straitAngel, int minAngel, int maxAngel, int defaultSpeed)
{
	m_signalPin = signalPin;
	m_straitAngel = straitAngel;
	m_minAngel = minAngel;
	m_maxAngel = maxAngel;
	m_defaultSpeed = defaultSpeed;
	
}

void ArmServo::begin()
{
	m_servo.attach(m_signalPin);
	m_servo.write(m_straitAngel);
}

void ArmServo::moveToAngel(int targetAngel) {
  
  int currentStepDelay = stepDelay/m_defaultSpeed;
  
  int currentAngel = m_servo.read();
  
  if(targetAngel > currentAngel) {
    while(currentAngel < targetAngel && currentAngel < m_maxAngel) {
      currentAngel += stepAngel;
      m_servo.write(currentAngel);
      delay(currentStepDelay);
    }
    
  } else if (currentAngel > targetAngel) {
    while(currentAngel > targetAngel && currentAngel > m_minAngel) {
      currentAngel -= stepAngel;
      m_servo.write(currentAngel);
      delay(currentStepDelay);
    }
  }

}
