/*
 * File: CollisionSensor.h
 * Created: Oct 11, 2018
 * Author: Jonathan Enderle
 */

#ifndef COLLISION_SENSOR_H
#define COLLISION_SENSOR_H

#include <string>
#include "GPIO.h"
#include "PeriodicTask.h"
class CommandQueue;


class CollisionSensor : public PeriodicTask {

public:

	/**
	 * Constructor for a CollisionSensor
	 *
	 * @param iopin The GPIO pin associated with this sensor
	 * @param thequeue The CommandQueue to interface with
	 * @param threadName The name of the thread
	 */
	CollisionSensor(int iopin, CommandQueue* thequeue, std::string threadName);

	/**
	 * Destructor
	 */
	virtual ~CollisionSensor();

	/**
	 * Run the logic of this sensor on its own thread.
	 * Scan for collisions, account for hysteresis, and report status.
	 */
	void run();

	/**
	 * Whether the robot is obstructed
	 * @return true if obstructed, else false
	 */
	bool isObstructed();

	void start();

private:
	exploringRPi::GPIO* sensorPin;
	bool obstructed;
	CommandQueue* queue;
	int hysteresisCount;
	exploringRPi::GPIO::VALUE previousRead = exploringRPi::GPIO::HIGH;
	static const int HYSTERESIS_START = 2;

};


#endif /* COLLISION_SENSOR_H */
