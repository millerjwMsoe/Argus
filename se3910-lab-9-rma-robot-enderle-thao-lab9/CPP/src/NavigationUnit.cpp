/*
 * NavigationUnit.cpp
 *
 *  Created on: Oct 11, 2018
 *      Author: se3910
 */

#ifndef LAB_6_LINE_FOLLOWING_ROBOT_THAO_ENDERLE_LAB6_PI_SRC_NAVIGATIONUNIT_CPP_
#define LAB_6_LINE_FOLLOWING_ROBOT_THAO_ENDERLE_LAB6_PI_SRC_NAVIGATIONUNIT_CPP_

#include "NavigationUnit.h"
#include "NetworkCommands.h"
#include "SWPWMMotorController.h"
#include "Horn.h"
#include "GPIO.h"
#include "ADReader.h"
#include "RobotCfg.h"
#include "TaskRates.h"
#include <string>
#include <iostream>
#include <thread>
#include <algorithm>
#include <vector>


using namespace exploringRPi;
using namespace std;

NavigationUnit::NavigationUnit(CommandQueue* driveQueue, CommandQueue* instructionQueue, string threadName) : PeriodicTask(threadName) {

	this->driveQueue = driveQueue;
	this->instructionQueue = instructionQueue;
	this->dataReader = new ADReader(CHIPSEL, IOCLK, ADDR, DOUT, "ADThread");
	dataReader->setTaskPeriod(AD_TASK_RATE);
	dataReader->setPriority(AD_TASK_PRIORITY); 
	dataReader->start();


}

void NavigationUnit::start() {
	PeriodicTask::setTaskPeriod(NAV_TASK_RATE);
	PeriodicTask::setPriority(NAV_TASK_PRIORITY);
	PeriodicTask::start();
}

NavigationUnit::~NavigationUnit() {

	delete instructionQueue;
	delete driveQueue;
	delete dataReader;

}

void NavigationUnit::calibrateWhite(){
	cout << "Calibrating Whites!" << endl;
	// Force the motor to stop (IRL over something that is the color white)
	driveQueue->enqueue(STOP);
	// read each of the 5 channel (i) 25 times (j),
	// take the median for each i
	// that is the "represesentative" white value
	for (int i = 0; i <= 4; i++) {
		// clear the current list and reset the median
		int median;
		listWhites = {};
		for (int j = 0; j <= 24; j++) {
			listWhites.push_back(dataReader->readChannelValue(i));
			median = NavigationUnit::getMedian(listWhites);

		}
		whites[i] = median;
	}
	// update the "thresholds"
	NavigationUnit::setThresholds();
	cout << "Whites: ";
	for (int i = 0; i <= 4; i++) {
		cout << whites[i] << " ";;
	}
	cout << endl;
}

void NavigationUnit::calibrateBlack(){
	cout << "Calibrating Blacks!" << endl;
	// Force the motor to stop (IRL over something that is the color white)
	driveQueue->enqueue(MOTORDIRECTIONBITMAP | STOP);
	// read each of the 5 channel (i) 25 times (j),
	// take the median for each i
	// that is the "represesentative" white value
	for (int i = 0; i <= 4; i++) {
		// clear the current list and reset the median
		int median;
		listBlacks = {};
		for (int j = 0; j <= 24; j++) {
			listBlacks.push_back(dataReader->readChannelValue(i));
			median = NavigationUnit::getMedian(listBlacks);

		}
		blacks[i] = median;
	}
	// update the "thresholds"
	NavigationUnit::setThresholds();
	cout << "Blacks: ";
	for (int i = 0; i <= 4; i++) {
		cout << blacks[i]<< " ";
	}
	cout << endl;
}

void NavigationUnit::setThresholds(){
	cout << "Setting Thresholds!" << endl;
	// formula taken from packet
	for (int i = 0; i <= 4; i++){
		int threshDiff = ((whites[i] - blacks[i]) / 3) + blacks[i];
		thresholds[i] = threshDiff;
	}
	cout << "threshs: ";
	for (int i = 0; i <= 4; i++) {
		cout << thresholds[i] << " ";
	}
	cout << endl;}

int NavigationUnit::getMedian(vector<int> calibrationVector) {
	// get size
	int middle = calibrationVector.size() / 2;
	// sort the vector and return
	std::sort(calibrationVector.begin(), calibrationVector.end());
	return calibrationVector[middle];

}

void NavigationUnit::run() {
	if (NavigationUnit::instructionQueue->hasItem()) {
		int returnVal = NavigationUnit::instructionQueue->dequeue();
		if (returnVal == START_WHITE_CALIBRATION){
			// cout << "Calibrate white" << returnVal << endl;
			NavigationUnit::calibrateWhite();
		} else if (returnVal == START_BLACK_CALIBRATION) {
			// cout << "Calibrate black" << returnVal << endl;
			NavigationUnit::calibrateBlack();
		} else if (returnVal == START_LINE_FOLLOWING) {
			// cout << "Start value: " << returnVal << endl;
			lineFollowingActive = true;
			NavigationUnit::startLineFollowing();
		} else if (returnVal == STOP_LINE_FOLLOWING) {
			// cout << "Stop value: " << returnVal << endl;
			NavigationUnit::stopLineFollowing();
		} else {
			cout << "How did we get here?" << returnVal << endl;
		}
	} else {
		if(lineFollowingActive) {
			startLineFollowing();
		}
	}
}

void NavigationUnit::stop(){
	// stop robot
	driveQueue->enqueue(STOP);


}

void NavigationUnit::startLineFollowing() {
	// cout << "Started Line Following!" << endl;
	if (lineFollowingActive){
		// cout << "lineFollowing " << lineFollowingActive << endl;
		// start the motor moving forward
		driveQueue->enqueue(MOTORDIRECTIONBITMAP | FORWARD);
		// read sensors and determine black or white
		char currentColors[5] = {'z', 'z', 'z', 'z', 'z'};
		for (int i = 0; i <= 4; i++){
			// cout << "Logging " << i << endl;
			// determine if it is black or white
			// if the color is between the threshold values +/-
			// we will choose that color
			int sensorColor = dataReader->readChannelValue(i);

			if (sensorColor > thresholds[i] ){
				// if we are within with "white bounds" we are white
				// cout << "Found W" << endl;
				currentColors[i] = 'w';
			} else if (sensorColor < thresholds[i]) {
				// cout << "Found B" << endl;
				currentColors[i] = 'b';
			} else {
				// cout << "Ayy Lmao" << endl;
			}
			// something about adding -2?
			// todo: file:///C:/lwshare/Lab6/lab-6-line-following-robot-thao_enderle_lab6/docs/html/classNavigationUnit.html
		}

		// cout << "done with for" << endl;

		// decide directions
		if (currentColors[3] == 'b') {
			// sensor 3 is black, go forward
			driveQueue->enqueue(MOTORDIRECTIONBITMAP | FORWARD);
			// cout << "enqueuing: " << FORWARD << endl;
		} else if (currentColors[2] == 'b') {
			// sensor 2 is black, turn left
			driveQueue->enqueue(MOTORDIRECTIONBITMAP | FORWARD | LEFT);
			// cout << "enqueuing: " << (FORWARD | LEFT) << endl;
		} else if (currentColors[4] == 'b') {
			// sensor 4 is black turn right
			driveQueue->enqueue(MOTORDIRECTIONBITMAP | FORWARD | RIGHT);
			// cout << "enqueuing: " << (FORWARD | RIGHT) << endl;
		} else if (currentColors[1] == 'b') {
			// sensor 1 is black spin left
			driveQueue->enqueue(MOTORDIRECTIONBITMAP | LEFT);
			// cout << "enqueuing: " << LEFT << endl;
		} else if (currentColors[5] == 'b') {
			// sensor 5 is black spin left
			driveQueue->enqueue(MOTORDIRECTIONBITMAP | RIGHT);
			// cout << "enqueuing: " << RIGHT << endl;
		} else {
			// cout << "Found Values: ";
			// for (int i = 0; i <= 4; i++) {
			// 	// cout << currentColors[i] << " ";;
			// }
			// cout << endl;
		}
	}
}

void NavigationUnit::stopLineFollowing() {
	// stop robot
	lineFollowingActive = false;
	driveQueue->enqueue(MOTORDIRECTIONBITMAP | STOP);

}

ADReader* NavigationUnit::getADReaderInstance() {
	return dataReader;
}


#endif /* LAB_6_LINE_FOLLOWING_ROBOT_THAO_ENDERLE_LAB6_PI_SRC_NAVIGATIONUNIT_CPP_ */