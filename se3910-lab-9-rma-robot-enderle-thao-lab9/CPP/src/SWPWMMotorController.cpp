/*
 * File: SWPWMMotorController.cpp
 * Created: 10/4/2018
 * Author: Jonathan Enderle
 */

#include "SWPWMMotorController.h"
#include "TaskRates.h"
#include <iostream>

using namespace std;
using exploringRPi::GPIO;

SWPWMMotorController::SWPWMMotorController(int in1pin, int in2pin, int epin, std::string threadName) : PeriodicTask(threadName) {
	forwardPin = new GPIO(in1pin);
	backwardPin = new GPIO(in2pin);
	enablePin = new GPIO(epin);

	forwardPin->setDirection(GPIO::OUTPUT);
	backwardPin->setDirection(GPIO::OUTPUT);
	enablePin->setDirection(GPIO::OUTPUT);

}

SWPWMMotorController::~SWPWMMotorController() {
	delete forwardPin;
	delete backwardPin;
	delete enablePin;
}

void SWPWMMotorController::setDutyCycle(int dc) {
	dutyCycle = dc;
}

/*
 * This method will set the direction for the motor.
 * The directions are as follows: negataive indicates reverse, 0 indicates stopped, and positive indicates forward.
 */
void SWPWMMotorController::setDirection(int dir) {
	// GPIO::HIGH means logical low.
	if(dir > 0) {
		backwardPin->setValue(GPIO::HIGH);
		forwardPin->setValue(GPIO::LOW);
	} else if(dir < 0) {
		forwardPin->setValue(GPIO::HIGH);
		backwardPin->setValue(GPIO::LOW);
	} else {
		backwardPin->setValue(GPIO::HIGH);
		forwardPin->setValue(GPIO::HIGH);
	}
}

void SWPWMMotorController::start() {
	PeriodicTask::setTaskPeriod(PWM_TASK_RATE);
	PeriodicTask::setPriority(PWM_TASK_PRIORITY);
	PeriodicTask::start();
}

// This should run every 1 ms (or whatever PeriodicTask is set to)
void SWPWMMotorController::run() {
	const int PERIOD = 20;

	count = (count + 1) % PERIOD;

	if(count < (dutyCycle/5)) {
		enablePin->setValue(GPIO::HIGH);
	} else {
		enablePin->setValue(GPIO::LOW);
	}

}

void SWPWMMotorController::stop() {
	// TODO - what network socket??
	RunnableClass::stop();
}

