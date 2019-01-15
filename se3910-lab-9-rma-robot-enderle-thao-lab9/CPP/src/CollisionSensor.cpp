/*
 * File: CollisionSensor.cpp
 * Created: Oct 11, 2018
 * Author: Jonathan Enderle
 */

#include "CollisionSensor.h"
#include "PeriodicTask.h"
#include "CommandQueue.h"
#include "NetworkCommands.h"
#include "TaskRates.h"

using exploringRPi::GPIO;
using namespace std;


CollisionSensor::CollisionSensor(int iopin, CommandQueue* thequeue, string threadName) : PeriodicTask(threadName) {
	sensorPin = new GPIO(iopin);
	sensorPin->setDirection(GPIO::DIRECTION::INPUT);
	queue = thequeue;
	obstructed = false;
	hysteresisCount = HYSTERESIS_START;
}

CollisionSensor::~CollisionSensor() {
	delete sensorPin;
}

void CollisionSensor::run() {
	bool currentlyObstructed = false;

	if(sensorPin->getValue() == GPIO::LOW) { // Sensor is low: obstructed
		currentlyObstructed = true;
	} // else: false

	if( currentlyObstructed != obstructed ) {
		hysteresisCount--;
	} else {
		hysteresisCount = HYSTERESIS_START; // if current reading matches stored one, reset the count.
	}

	// If it's been different long enough, update the stored value & send a message
	if(hysteresisCount < 0) {
		obstructed = currentlyObstructed;
		int message = COLLISIONBITMAP;
		if(obstructed) {
			message = message | COLLISION_SENSED;
		} else {
			message = message | COLLISION_CLEARED;
		}
		queue->enqueue(message);
	}

}

bool CollisionSensor::isObstructed() {
	return obstructed;
}

void CollisionSensor::start() {
	PeriodicTask::setTaskPeriod(COLLISION_SENSING_TASK_RATE);
	PeriodicTask::setPriority(COLLISION_SENSING_TASK_PRIORITY);
	PeriodicTask::start();
}


