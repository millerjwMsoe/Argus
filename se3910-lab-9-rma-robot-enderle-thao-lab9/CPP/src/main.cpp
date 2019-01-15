/*
 * main.cpp

 *
 *  Created on: Mar 3, 2015
 *      Author: student
 */
#include <pthread.h>
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <thread>
#include "GPIO.h"
#include "NetworkManager.h"
#include "RobotController.h"
#include "NetworkCommands.h"
#include "RobotCfg.h"
#include "CollisionSensingRobotController.h"
#include "NavigationUnit.h"
#include "DiagUnit.h"
#include "CameraController.h"
#include "TaskRates.h"
#include "ImageCapturer.h"

using namespace std;

/**
 * This is the main program.  It will instantiate a network manager and robot controller as well as a Command Queue.
 * It will then block until the user enters a message on the console.
 * This will then cause it to shutdown the other classes and wait for their threads to terminate.
 */
int main(int argc, char* argv[]) {
	if (argc != 3) {
		printf("Usage: %s <machine> <port>\n", argv[0]);
		exit(0);
	}

	CommandQueue *driveQueue = new CommandQueue();
	CommandQueue *navigationCommandQueue = new CommandQueue();
	CommandQueue *diagQueue = new CommandQueue();
	CommandQueue *cameraQueue = new CommandQueue();

	CommandQueue *array[4];
	array[0] = driveQueue;
	array[1] = navigationCommandQueue;
	array[2] = diagQueue;
	array[3] = cameraQueue;

	//Declare a pair of players
	NetworkManager nm(9090, array, "Network Manager");
	CollisionSensingRobotController mc(driveQueue, DL, DR, "Col. Sensing Ctrl");
	NavigationUnit navUnit(driveQueue, navigationCommandQueue, "Nav Unit");
	DiagUnit diagnosticsUnit(diagQueue, navUnit.getADReaderInstance(), "Diagnostics");

	CameraController cc(cameraQueue, 1, 0x40, "Camera Ctrl");
	cc.setTaskPeriod(CAMERA_CONTROLLER_TASK);
	cc.setPriority(CAMERA_CONTROLLER_TASK_PRIORITY);
	cc.start();

	Camera* myCamera = new Camera("Camera", 640, 360);
	ImageTransmitter* it = new ImageTransmitter(argv[1], atoi(argv[2]));
	myCamera->start(CAMERA_CAPTURE_TASK_PRIORITY);

	ImageCapturer *is = new ImageCapturer("Image Streamer", myCamera, it, 320,
			180);
	is->setTaskPeriod(CTM_TASK_PERIOD);
	is->setPriority(CTM_TASK_PRIORITY);
	is->start();

	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	// Start each of the two threads up.
	nm.start();
	mc.start();

	navUnit.setTaskPeriod(NAV_TASK_RATE);
	navUnit.setPriority(NAV_TASK_PRIORITY);
	navUnit.start();
	diagnosticsUnit.start();

	char msg[1024];
	msg[0] = 0;

	while (strcmp(msg, "quit") != 0) {
		cin >> msg;
		RunnableClass::printThreads();
	}

	nm.stop();
	mc.stop();
	navUnit.stop();
	diagnosticsUnit.stop();

	// Wait for the threads to die.
	nm.waitForShutdown();
	mc.waitForShutdown();

	delete driveQueue;
	delete navigationCommandQueue;
}

