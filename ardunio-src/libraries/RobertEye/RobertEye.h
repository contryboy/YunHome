/*
 * RobertEye.h
 *
 *  Created on: Dec 4, 2014
 *      Author: zhangdong
 */

#ifndef ROBERTEYE_H_
#define ROBERTEYE_H_

#include <Arduino.h>
#include <Pixy.h>


class RobertEye {

public:
	const static int MIDDLE_X = 163;
	//if x is with +/- MIDDLE_RANGE of middle, consider it still in middle
	const static int MIDDLE_RANGE = 3;

private:
	Pixy pixy;
	/* nullBlock, which has 0 height and width, is used to indicate there is no object seen */
	Block nullBlock;
public:
	RobertEye();

	void begin();
	void printObjects();
	Block getBiggestObject();
	int getObjectCount();
	bool isValidObject(const Block &block);
	/**
	 * Get the x offset to middle, <0 means left, 0 means middle, >0 means right.
	 */
	int getXOffsetToMiddle(Block& block);
};

#endif /* ROBERTEYE_H_ */
