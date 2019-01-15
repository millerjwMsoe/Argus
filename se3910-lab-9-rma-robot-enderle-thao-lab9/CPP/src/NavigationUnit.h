/*
 * NavigationUnit.h
 *
 *  Created on: Oct 11, 2018
 *      Author: se3910
 */

#ifndef PI_SRC_NAVIGATIONUNIT_H_
#define PI_SRC_NAVIGATIONUNIT_H_

#include "CommandQueue.h"
#include "ADReader.h"
#include <stdint.h>
#include <vector>
using namespace std;

class NavigationUnit : public PeriodicTask {
private:

	CommandQueue* driveQueue;
	CommandQueue* instructionQueue;
	ADReader* dataReader;

	uint16_t thresholds[5] = {512, 512, 512, 512, 512};
	uint16_t whites[5] = {1023, 1023, 1023, 1023, 1023};
	uint16_t blacks[5] = {0, 0, 0, 0, 0};

	vector<int> listWhites = {}; 
	vector<int> listBlacks= {}; 

	bool lineFollowingActive = false;

	void calibrateWhite();
	void calibrateBlack();
	void setThresholds();
	int getMedian(vector<int> calibrationVector);

public:
	NavigationUnit(CommandQueue* driveQueue, CommandQueue* instructionQueue, string threadName);
	~NavigationUnit();

	ADReader* getADReaderInstance();

	void run();
	void stop();
	void start();

	void startLineFollowing();
	void stopLineFollowing();
};

#endif /* LAB_6_LINE_FOLLOWING_ROBOT_THAO_ENDERLE_LAB6_PI_SRC_NAVIGATIONUNIT_H_ */
