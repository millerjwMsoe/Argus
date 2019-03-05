/*
 * File: RunnableClass.cpp
 * Description: Virtual base class that mimics Java's Runnable interface.
 *   Adapted from code by Dr. Walter Schilling.
 */

#include "RunnableClass.h"
#include <thread>
#include <string>
#include <iostream>
#include <iomanip>
#include <sys/types.h>
#include <unistd.h>
#include <sys/syscall.h>


RunnableClass::RunnableClass() {

}

RunnableClass::~RunnableClass() {
	if (myThread != NULL) {
		delete myThread;
	}
}

void RunnableClass::stop() {
	keepGoing = false;
}

void RunnableClass::start() {
	myThread = new std::thread(&RunnableClass::invokeRun, this);
}

void RunnableClass::invokeRun()
{
	run();
}


bool RunnableClass::isShutdown() {
	return !keepGoing;
}

void RunnableClass::waitForShutdown() {
	if (myThread != NULL) {
		myThread->join();
	}
}


