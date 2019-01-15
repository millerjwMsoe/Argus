/*
 * File: DiagUnit.h
 * Created: Oct 11, 2018
 * Author: Jonathan Enderle
 */

#ifndef DIAG_UNIT_H
#define DIAG_UNIT_H

#include <string>
#include "RunnableClass.h"

class ADReader;
class CommandQueue;


class DiagUnit : public RunnableClass {
public:
	/**
	 * Constructor
	 * @param referencequeue CommandQueue
	 * @param threadName Name of thread
	 */
	DiagUnit(CommandQueue* referencequeue, std::string threadName);

	/**
	 * Constructor
	 * @param referencequeue CommandQueue
	 * @param adReference the ADReader
	 * @param threadName Name of thread
	 */
	DiagUnit(CommandQueue* referencequeue, ADReader* adReference, std::string threadName);

	/**
	 * Destructor
	 */
	virtual ~DiagUnit();

	/**
	 * Run program-specific logic on its own thread.
	 */
	void run();

private:
	CommandQueue* referencequeue;
	ADReader* adReader;


};


#endif /* DIAG_UNIT_H */
