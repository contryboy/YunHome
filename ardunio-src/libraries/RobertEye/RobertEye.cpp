/*
 * RobertEye.cpp
 *
 *  Created on: Dec 4, 2014
 *      Author: zhangdong
 */

#include "RobertEye.h"

RobertEye::RobertEye() {
	nullBlock.height = 0;
	nullBlock.width = 0;
}

void RobertEye::begin() {
	pixy.init();
}

void RobertEye::printObjects() {
	int j;
	int blocks;
	char buf[32];

	blocks = pixy.getBlocks();

	if (blocks) {
		sprintf(buf, "Detected %d:\n", blocks);
		Serial.print(buf);
		for (j = 0; j < blocks; j++) {
			sprintf(buf, "  block %d: ", j);
			Serial.print(buf);
			pixy.blocks[j].print();
		}
	}
}


int RobertEye::getObjectCount() {
	return pixy.getBlocks();
}

Block RobertEye::getBiggestObject(uint16_t signatureNumber) {
	int blocksCount = pixy.getBlocks();

	for(int i=0; i<blocksCount; ++i) {
		if(pixy.blocks[i].signature == signatureNumber) {
			return pixy.blocks[i];
		}
	}

	return nullBlock;
}

bool RobertEye::isValidObject(const Block &block) {
	return block.height>0 && block.width>0;
}

int RobertEye::getXOffsetToMiddle(Block& block) {
	return getXOffsetToMiddle(block, MIDDLE_CHECK_ACCURACY);
}


int RobertEye::getXOffsetToMiddle(Block& block, int accuracyInPixl) {
	int offset = block.x - MIDDLE_X;
	return abs(offset) <= accuracyInPixl ? 0 : offset;
}
