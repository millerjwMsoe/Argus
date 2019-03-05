/*
 * File: PeriodicTask.h
 * Description: A periodic task that runs on its own thread.
 *   Adapted from code by Dr. Walter Schilling.
 */

#ifndef PERIODICTASK_H_
#define PERIODICTASK_H_

#include "RunnableClass.h"

#include <chrono>

class PeriodicTask: public RunnableClass {
public:
	/**
	 * This is the default constructor for the class.
	 */
	PeriodicTask();

	/**
	 * This method will clean up from the periodic task and its execution.
	 */
	virtual ~PeriodicTask();

	/**
	 * This will set the period for the given task.
	 * @param period This is the period, given in ms, between executions of this task.
	 */
	void setTaskPeriod(uint32_t period);

	/**
	 * This method will suspend execution until the next period has been reached.  It will do this by blocking.
	 */
	void waitForNextExecution(std::chrono::microseconds remainingSleepTime);

	virtual void start();

private:
	/**
	 * This variable sets the period for the task.  The period defines the length of time from one invocation until the next invocation.  The task period is given in ms.
	 */
	uint32_t taskPeriod = 0;

	/**
	 * This is a private method that will be used by start to invoke the run method.
	 */
	void invokeRun();

};

#endif /* PERIODICTASK_H_ */
