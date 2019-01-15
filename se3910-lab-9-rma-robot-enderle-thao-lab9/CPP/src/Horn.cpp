/*
 * Horn.cpp
 *
 *  Created on: Oct 11, 2018
 *      Author: se3910
 */

#include "Horn.h"
#include "GPIO.h"
#include <string>
#include <iostream>
#include <thread>
#include "TaskRates.h"


using namespace exploringRPi;
using namespace std;

Horn::Horn(int gpioPin, string threadName) : PeriodicTask(threadName) {
	this->hornPin = new GPIO(gpioPin);
	hornPin->setDirection(GPIO::OUTPUT);
	hornPin->setValue(GPIO::LOW);
	PeriodicTask::setTaskPeriod(HORN_TASK_RATE);
	PeriodicTask::setPriority(HORN_TASK_PRIORITY);
	PeriodicTask::start();
	this->hornCount = 0;
}


Horn::~Horn() {

}


void Horn::pulseHorn(int length, int period) {
	this->repititionTime = period;
	this->length = length;


}

void Horn::silenceHorn() {
	hornPin->setValue(GPIO::LOW);
}

void Horn::soundHorn() {
	hornPin->setValue(GPIO::HIGH);
}

void Horn::run() {
	hornCount = (hornCount + 1) % repititionTime;

	if(hornCount < length) {
		hornPin->setValue(GPIO::HIGH);
	} else {
		hornPin->setValue(GPIO::LOW);
	}
}
