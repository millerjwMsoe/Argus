/*
 * CameraController.cpp
 *
 *  Created on: Jul 4, 2018
 *      Author: se3910
 */

#include "CameraController.h"
#include "PCA9685Driver.h"
#include <string>
#include "NetworkCommands.h"
#include <iostream>
#include "TaskRates.h"

CameraController::CameraController(CommandQueue *thequeue, unsigned int bus,
		unsigned int deviceAddress, std::string threadName) :
		PeriodicTask(threadName) {
	this->controlHardware = new PCA9685Driver(bus, deviceAddress);
	cameraqueue = thequeue;
}

CameraController::~CameraController() {
	delete this->controlHardware;
}

void CameraController::setElevation(int elevation) {
	if ((elevation < 90) && (elevation > -45)) {
		desiredElevation = elevation;
	}

}
void CameraController::setRotation(int rotation) {
	if ((rotation < 90) && (rotation > -90)) {
		desiredRotation = rotation;
	}
}

/**
 * This virtual method is the start method.  It must be implemented in child classes.  The purpose of this method is to instantiate a new thread and invoke the run method.
 */
void CameraController::start() {
	controlHardware->init();
	PeriodicTask::start();
}
/**
 * This is the virtual run method.  It will execute the given code that is to be executed by this class.
 */
void CameraController::run() {

	// See if there is anything that needs to be done with the queue.
	if (cameraqueue->hasItem()) {
		// Dequeue the item.
		int command = cameraqueue->dequeue();
		std::cout << ((command & ~ELEVATION_FLAG) & ~AZMUTH_FLAG) << "\n";

		if (command & ELEVATION_FLAG == ELEVATION_FLAG) {
			std::cout << "Elevation";
			setElevation((command & ~ELEVATION_FLAG) - 180);
		}
		if (command & AZMUTH_FLAG == AZMUTH_FLAG) {
			// Stop the robot from any motion.
			setRotation((command & ~AZMUTH_FLAG) - 180);
			std::cout << "Azimuth";
		}
	}

	// Setup the elevation to the right value.
	{
		if (elevation > desiredElevation) {
			if ((elevation - desiredElevation) < 2) {
				elevation = desiredElevation;
			} else {
				elevation = elevation - 2;
			}

		} else if (elevation < desiredElevation) {
			if ((desiredElevation - elevation) < 2) {
				elevation = desiredElevation;
			} else {
				elevation = elevation + 2;
			}
		} else {
			// Nothing needs to be done with elevation.
		}

		// Now write out the PWM value.
		int value = 1500 + (elevation * 1000) / 90;
		controlHardware->setPulseWidth(1, value);
	}

	// Setup the rotation to the right value.
	{
		if (rotation > desiredRotation) {
			if ((rotation - desiredRotation) < 2) {
				rotation = desiredRotation;
			} else {
				rotation = rotation - 2;
			}

		} else if (rotation < desiredRotation) {
			if ((desiredRotation - rotation) < 2) {
				rotation = desiredRotation;
			} else {
				rotation = rotation + 2;
			}
		} else {
			// Nothing needs to be done with rotation.
		}

		// Now write out the PWM value.
		int value = 1500 + (rotation * 1000) / 90;
		controlHardware->setPulseWidth(0, value);
	}
}


