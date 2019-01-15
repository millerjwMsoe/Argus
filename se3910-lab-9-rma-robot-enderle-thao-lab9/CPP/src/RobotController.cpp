/*
 * RobotController.cpp
 *
 *  Created on: Oct 4, 2018
 *      Author: se3910
 */

#include "RobotController.h"
#include "SWPWMMotorController.h"
#include "GPIO.h"
#include "NetworkCommands.h"
#include <string>
#include <iostream>
#include <thread>


using namespace exploringRPi;
using namespace std;

/*
This method will instantiate a new instance of the robot controller.
Parameters:
	[queue	This is the instance of the queue that will be used to send commands to the robot.]
Instantiate a new instance of the SWPWM Motor controller to control the left motor.
Instantiate a new instance of the SWPWM Motor Controller to control the right motor.
By default, set the speed to 0%.
 */
RobotController::RobotController(CommandQueue* queue, std::string threadName) : RunnableClass(threadName) {
	this->referenceQueue = queue;

	this->leftMotor = new SWPWMMotorController(12, 13, 6, "leftMotor");
	this->rightMotor= new SWPWMMotorController(20, 21, 26, "rightMotor");

	leftMotor->setDutyCycle(0);
	rightMotor->setDutyCycle(0);

	leftMotor->start();
	rightMotor->start();
}

/*
This method destroy the existing instance of the robot controller.
This is the destructor for the class. It will clean up any allocated resources.
 */
RobotController::~RobotController() {
	delete leftMotor;
	delete rightMotor;
}

void RobotController::run() {
	cout << "RobotController::run() BEGIN" << endl;
	while (keepGoing){
		int returnVal = RobotController::referenceQueue->dequeue();
		if( (returnVal & MOTORDIRECTIONBITMAP) == MOTORDIRECTIONBITMAP) {
			int direction = returnVal & MOTORDIRECTIONS;
			processMotionControlCommand(direction);
			currentOperation = direction;
		} else if ( (returnVal & SPEEDDIRECTIONBITMAP) == SPEEDDIRECTIONBITMAP) {
			int speed = returnVal - SPEEDDIRECTIONBITMAP;
			processSpeedControlCommand(speed);
			currentSpeed = speed;
		}
	}
}

/*
 * This method will stop the thread and its execution.
 * In the case of this particular class, it will also shutdown the network socket.
 */
void RobotController::stop() {
	leftMotor->setDirection(0); // stop
	rightMotor->setDirection(0); // stop
	RunnableClass::stop();
}

int RobotController::processMotionControlCommand(int value) {
	if (value == STOP){
		leftMotor->setDirection(0); // stop
		rightMotor->setDirection(0); // stop

	} else if (value == (FORWARD | LEFT) ) {
		leftMotor->setDirection(0); // stop
		rightMotor->setDirection(1); // forward

	} else if (value == FORWARD) {
		leftMotor->setDirection(1); // forward
		rightMotor->setDirection(1); //forward

	} else if (value == (FORWARD | RIGHT) ) {
		leftMotor->setDirection(1); // forward
		rightMotor->setDirection(0); //stop

	} else if (value == (BACKWARD | LEFT) ) {
		leftMotor->setDirection(0); // stop
		rightMotor->setDirection(-1); // backward

	} else if (value == BACKWARD) {
		leftMotor->setDirection(-1);
		rightMotor->setDirection(-1);

	} else if (value == (BACKWARD | RIGHT) ) {
		leftMotor->setDirection(-1); // backward
		rightMotor->setDirection(0); // stop

	} else if (value == LEFT) {
		leftMotor->setDirection(-1);
		rightMotor->setDirection(1);

	} else if (value == RIGHT) {
		leftMotor->setDirection(1);
		rightMotor->setDirection(-1);
	}

	return 0;
}

int RobotController::processSpeedControlCommand(int value) {
	leftMotor->setDutyCycle(value);
	rightMotor->setDutyCycle(value);
	return 0;
}