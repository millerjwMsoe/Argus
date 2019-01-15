/*
 * File: CollisionSensingRobotController.h
 * Created: Oct 11, 2018
 * Author: Jonathan Enderle
 */


#include "CollisionSensingRobotController.h"
#include "CollisionSensor.h"
#include "Horn.h"
#include "RobotCfg.h"
#include "NetworkCommands.h"

#include <iostream>

using exploringRPi::GPIO;
using namespace std;

CollisionSensingRobotController::CollisionSensingRobotController(CommandQueue* queue, int leftSensorPin, int rightSensorPin, string threadName) : RobotController(queue, threadName) {
	lcs = new CollisionSensor(leftSensorPin, queue, "Left Collision Sensor");
	rcs = new CollisionSensor(rightSensorPin, queue, "Right Collision Sensor");

	lcs->start();
	rcs->start();

	// TODO: horn
	robotHorn = new Horn(BUZZER, "hornThread");
	robotHorn->start();
}

CollisionSensingRobotController::~CollisionSensingRobotController() {
	delete lcs;
	delete rcs;
}

void CollisionSensingRobotController::run() {
	cout << "CollisionSensingRobotController::run() BEGIN" << endl;
	while (keepGoing){
		int returnVal = referenceQueue->dequeue();
		// cout << "SKEEEEET: " << returnVal << endl;

		if((returnVal & COLLISIONBITMAP) == COLLISIONBITMAP) { // the message is talking about a collision
			int message = returnVal & 0x0000FFFF; // Only look at last 2 bytes
			if(message == COLLISION_SENSED) { // take evasive action
				robotHorn->soundHorn();
				bool leftBlocked = lcs->isObstructed();
				bool rightBlocked = rcs->isObstructed();

				if(leftBlocked && rightBlocked) {
					processMotionControlCommand(STOP);
				} else if (leftBlocked) {
					processMotionControlCommand(RIGHT);
				} else { // rightBlocked
					processMotionControlCommand(LEFT);
				}

			} else { // message == COLLISION_CLEARED
				processMotionControlCommand(currentOperation); // clear; resume normal operation
				robotHorn->silenceHorn();
			}

		} else { // process the command normally

			// Copied from RobotController.cpp
			if( (returnVal & MOTORDIRECTIONBITMAP) == MOTORDIRECTIONBITMAP) {
				int direction = returnVal & MOTORDIRECTIONS;
				if (direction == BACKWARD) {
					// cout << "SKRRRRRT" << direction << endl;
					robotHorn->pulseHorn(125, 250);
				} else {
					robotHorn->pulseHorn(0, 250);
				}
				processMotionControlCommand(direction);
				currentOperation = direction;
			} else if ( (returnVal & SPEEDDIRECTIONBITMAP) == SPEEDDIRECTIONBITMAP) {
				int speed = returnVal - SPEEDDIRECTIONBITMAP;
				processSpeedControlCommand(speed);
				currentSpeed = speed;
			} // do reverse check here

		}
	}
}

void CollisionSensingRobotController::stop() {
	lcs->stop();
	rcs->stop();
	RobotController::stop();
}