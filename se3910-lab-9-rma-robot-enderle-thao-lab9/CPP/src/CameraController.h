/**
 * @file CameraController.h
 * @author  Walter Schilling (schilling@msoe.edu)
 * @version 1.0
 *
 * @section LICENSE This is a piece of a template solution to the lab.
 *
 *
 * @section DESCRIPTION
 *      This file allows the user to control the position of the camera.
 */

#ifndef CAMERACONTROLLER_H_
#define CAMERACONTROLLER_H_

#include "PeriodicTask.h"
#include "PCA9685Driver.h"
#include "CommandQueue.h"

class CameraController: public PeriodicTask {
private:
	/**
	 * This is the current angle either above or below level.
	 */
	int elevation = 0;
	int desiredElevation = 0;
	/**
	 * This is the current rotation, between -90 and 90, with 0 being straight ahead.
	 */
	int rotation = 0;
	int desiredRotation = 0;

	/**
	 * This is the hardware that will control the angle and elevation.
	 */
	PCA9685Driver *controlHardware = NULL;

	/**
	 * This is the queue that is attached to the camera.
	 */
	CommandQueue *cameraqueue;

public:
	CameraController(CommandQueue *thequeue, unsigned int bus, unsigned int deviceAddress,
			std::string threadName);
	virtual ~CameraController();

	void setElevation(int elevation);
	void setRotation(int rotation);

	/**
	 * This virtual method is the start method.  It must be implemented in child classes.  The purpose of this method is to instantiate a new thread and invoke the run method.
	 */
	void start();
	/**
	 * This is the virtual run method.  It will execute the given code that is to be executed by this class.
	 */
	void run();


};

#endif /* CAMERACONTROLLER_H_ */
