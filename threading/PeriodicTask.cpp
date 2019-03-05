/*
 * File: PeriodicTask.cpp
 * Description: A periodic task that runs on its own thread.
 *   Adapted from code by Dr. Walter Schilling.
 */

#include "PeriodicTask.h"
#include <iostream>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace std::chrono;

PeriodicTask::PeriodicTask() { }

PeriodicTask::~PeriodicTask() { }

void PeriodicTask::setTaskPeriod(uint32_t period) {
	taskPeriod = period;
}

void PeriodicTask::waitForNextExecution(microseconds remainingSleepTime) {
	this_thread::sleep_for(remainingSleepTime);
}

/**
 * This is a private method that will be used by start to invoke the run method.
 */
void PeriodicTask::invokeRun() {
	// Indicate that the thread has been started.
	keepGoing = true;
	while (keepGoing == true) {
		high_resolution_clock::time_point start = high_resolution_clock::now();

		run(); // run the task.

		high_resolution_clock::time_point end = high_resolution_clock::now();
		microseconds executionTime = duration_cast<microseconds>(end - start);
		microseconds remainingSleepTime = milliseconds(taskPeriod) - executionTime;

		waitForNextExecution(remainingSleepTime);
	}
}

void PeriodicTask::start() {
	myThread = new thread(&PeriodicTask::invokeRun, this);
}
