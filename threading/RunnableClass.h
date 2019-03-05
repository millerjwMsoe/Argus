/*
 * File: RunnableClass.h
 * Description: Virtual base class that mimics Java's Runnable interface.
 *   Adapted from code by Dr. Walter Schilling.
 */

#ifndef RUNNABLECLASS_H_
#define RUNNABLECLASS_H_

#include <thread>
#include <string>
#include <list>
#include <sys/types.h>

/**
 * This is the runnable class, which mimics the runnable interface from Java.  It is a virtual class which should not directly be instantiated.
 */
class RunnableClass {
protected:
	/**
	 * This is the instance of the thread that is to be executed by this class.  At instantiation it is NULL.  It will be instantiated when the start method of the class is invoked.
	 */
	std::thread *myThread=NULL;
	/**
	 * This method will determine whether or not the given thread is to continue executing.
	 */
	bool keepGoing=true;


private:
	/**
	 * This is a private method that will be used by start to invoke the run method.
	 */
	void invokeRun();

public:

	/**
	 * This is the default constructor for the class.
	 */
	RunnableClass();
	/**
	 * This is the default destructor for the class.  It must properly clean up the instantiated thread.
	 */
	virtual ~RunnableClass();

	/**
	 * This virtual method is the start method.  It must be implemented in child classes.  The purpose of this method is to instantiate a new thread and invoke the run method.
	 */
	virtual void start();

	/**
	 * This is the virtual run method.  It will execute the given code that is to be executed by this class.
	 */
	virtual void run()=0;
	/**
	 * This method will stop the execution of the given class.
	 */
	virtual void stop();
	/**
	 * This method will determine if the given thread is shutdown.
	 * @return The return will be true if the thread is shutdown or false otherwise.
	 */
	bool isShutdown();
	/**
	 * This method will block waiting for the given thread to terminate before continuing.
	 */
	void waitForShutdown();

};

#endif /* RUNNABLECLASS_H_ */
