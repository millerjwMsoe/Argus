/**
 * @file
 * @author  Walter Schilling (schilling@msoe.edu)
 * @version 1.0
 *
 * @section LICENSE This is a piece of a template solution to the lab.
 *
 *
 * @section DESCRIPTION
 *      This class is a controller for the robot.  It is responsible for managing the operation of the motors based upon incoming commands
 *      from the command queue.
 */

#ifndef ROBOTCONTROLLER_H
#define ROBOTCONTROLLER_H

#include <pthread.h>
#include <string>
#include "GPIO.h"
#include "CommandQueue.h"
#include "SWPWMMotorController.h"
#include "RunnableClass.h"


using namespace exploringRPi;

class RobotController : public RunnableClass {
protected:
	/**
	 * This is a pointer to the queue that will be sued for receiving commands.  Commands can come from the network or other portions of the robot.
	 */
	CommandQueue* referenceQueue;
	/**
	 * This is a pointer to the left motor within the robot.  This will drive the left wheel.
	 */
	SWPWMMotorController* leftMotor;
	/**
	 * This is a pointer to the right motor which drives the right wheel.
	 */
	SWPWMMotorController* rightMotor;

	/**
	 * This is the current speed for the robot.
	 */
	int currentSpeed=0;

	/**
	 * This is the current operation that the robot is performing.
	 */
	int currentOperation=0;

	/**
	 * This method will process a command that is related to motion control.
	 * @param value This is the command that was received.
	 * @return This is the command that was last processed.  Under normal circumstances, it is exactly the value as the value passed in.
	 */
	int processMotionControlCommand(int value);
	/**
	 * This method will process a command that is related to speed control.
	 * @param value This is the command that was received.
	 * @return This is the speed that was set.
	 */
	int processSpeedControlCommand(int value);

public:
	/**
	 * This method will instantiate a new instance of the robot controller.
	 * @param queue This is the instance of the queue that will be used to send commands to the robot.
	 * @param threadName This is the name given to the executing thread.  It is a simple, string that is human readable.
	 */
	RobotController(CommandQueue* queue, std::string threadName);

	/**
	 * This method destroy the existing instance of the robot controller.
	 */
	virtual ~RobotController();
	/**
	 * This is the run method for the class.  It contains the code that is to run periodically on the given thread.
	 */
	void run();
	/**
	 * this method will stop the thread and its execution.  In the case of this particular class, it will also shutdown the network socket.
	 */
	void stop();
};

#endif /* ROBOTCONTROLLER_H */
