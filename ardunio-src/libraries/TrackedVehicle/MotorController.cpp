/*
 * MotorController.cpp
 *
 *  Created on: Nov 26, 2014
 *      Author: zhangdong
 */

#include "MotorController.h"
#include <Arduino.h>

MotorController::MotorController(int EN_pin, int D1_pin, int D2_pin)
	:m_EN_pin(EN_pin), m_D1_pin(D1_pin), m_D2_pin(D2_pin){

}

void MotorController::begin() {
	pinMode(m_EN_pin, OUTPUT);
	pinMode(m_D1_pin, OUTPUT);
	pinMode(m_D2_pin, OUTPUT);
}

/**
 * forward: direction of the rotation
 * speed: 0~255
 */
void MotorController::run(bool forward, int speed) {
	bool d1 = !forward;
	bool d2 = forward;

	//Serial.println("MotorController.run(): ");
	//Serial.println(m_EN_pin);
	//Serial.println(m_D1_pin);
	//Serial.println(m_D2_pin);
	//Serial.println(d1);
	//Serial.println(d2);

	analogWrite(m_EN_pin, speed);
	digitalWrite(m_D1_pin, d1);
	digitalWrite(m_D2_pin, d2);

}

void MotorController::stop() {
	analogWrite(m_EN_pin, 0);
	digitalWrite(m_D1_pin, LOW);
	digitalWrite(m_D2_pin, LOW);
}
