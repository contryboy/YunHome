/*
 * DistanceMeasure.h
 *
 *  Created on: Dec 8, 2014
 *      Author: zhangdong
 */

#ifndef DISTANCEMEASURE_H_
#define DISTANCEMEASURE_H_

#include <Arduino.h>

class DistanceMeasure {
private:
	/** When range pin is unplug(high) or high, parameter is 3096; when it's low, parameter is 1024*/
	const static int RANGE_PARAMETER = 1024;
	const static int DISTANCE_SENSOR_PIN = A5;
	const static int VCC_SENSOR_PIN = A4;

public:
	/**
	 * Measure the distance in mm.
	 */
	static int getDistanceInMm() {
		  // read the value from the sensor:
		  int sensorValue = analogRead(DISTANCE_SENSOR_PIN);
		  int vccValue = analogRead(VCC_SENSOR_PIN);

		  Serial.print(sensorValue);
		  Serial.print("/");
		  Serial.print(vccValue);
		  Serial.print(" ");

		  int distance = (double)RANGE_PARAMETER * (double)sensorValue/(double)vccValue;
		  Serial.print(distance);
		  Serial.println("mm");

		  return distance;
	}
};

#endif /* DISTANCEMEASURE_H_ */
