/*
 * File: CollisionSensingRobotController.h
 * Created: Oct 11, 2018
 * Author: Jonathan Enderle
 */

#ifndef COLLISION_SENSING_ROBOT_CONTROLLER_H
#define COLLISION_SENSING_ROBOT_CONTROLLER_H

#include <string>
#include "RobotController.h"

class CollisionSensor;
class Horn;

class CollisionSensingRobotController : public RobotController {

public:

	/**
	 * Construct a sensing controller given the sensor pin numbers
	 * @param queue CommandQueue
	 * @param leftSensorPin GPIO pin number for the left sensor
	 * @param rightSensorPin GPIO pin number for the right sensor
	 * @param threadName Name of the thread
	 */
	CollisionSensingRobotController(CommandQueue* queue, int leftSensorPin, int rightSensorPin, std::string threadName);

	/**
	 * Destructor
	 */
	virtual ~CollisionSensingRobotController();

	/**
	 * Run the logic of the CollisionSensingRobotController on its own thread.
	 */
	void run();

	/**
	 * Stop the thread
	 */
	void stop();



protected:

	CollisionSensor* lcs;
	CollisionSensor* rcs;
	Horn* robotHorn;

};


#endif /* COLLISION_SENSING_ROBOT_CONTROLLER_H */
