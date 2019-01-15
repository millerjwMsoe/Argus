/*
 * Horn.h
 *
 *  Created on: Oct 11, 2018
 *      Author: se3910
 */

#ifndef PI_SRC_HORN_H_
#define PI_SRC_HORN_H_

#include "GPIO.h"
#include "PeriodicTask.h"
using namespace std;

class Horn : public PeriodicTask {
private:
	exploringRPi::GPIO *hornPin;

	int hornCount = -1;
	int length = 0;
	int repititionTime = 1;

public:
	Horn(int gpioPin, string threadName);
	~Horn();

	void soundHorn();
	void pulseHorn(int length, int period);
	void silenceHorn();
	void run();
};




#endif /* LAB_6_LINE_FOLLOWING_ROBOT_THAO_ENDERLE_LAB6_PI_SRC_HORN_H_ */
