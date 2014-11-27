/*
 * MotorController.h
 *
 *  Created on: Nov 26, 2014
 *      Author: zhangdong
 */

#ifndef MOTORCONTROLLER_H_
#define MOTORCONTROLLER_H_

class MotorController {
public:
	/* Pin for control the speed (connected to ENA/ENB)*/
	int m_EN_pin;
	/* Pin1 for control the direction (connected to A1/B2)*/
	int m_D1_pin;
	/* Pin2 for control the direction (connected to A2/B2)*/
	int m_D2_pin;


public:
	MotorController(int EN_pin, int D1_pin, int D2_pin);
	void begin();
	/**
	 * forward: direction of the rotation
	 * speed: 0~255
	 */
	void run(bool forward, int speed);

	void stop();
};

#endif /* MOTORCONTROLLER_H_ */
