/*
 * File: SWPWMMotorController.h
 * Created: 10/4/2018
 * Author: Jonathan Enderle
 */

#ifndef SWPWMMOTORCONTROLLER_H
#define SWPWMMOTORCONTROLLER_H

#include <string>
#include "PeriodicTask.h"
#include "GPIO.h"

class SWPWMMotorController: public PeriodicTask {
public:
	/**
	 * Constructor
	 *
	 * @param in1pin This is the 1 pin for the motor controller.
	 * @param in2pin This is the pin number for the #2 pin of the motor.
	 * @param epin This is the number for the enable pin of the controller.
	 * @param threadName Name of the thread
	 */
	SWPWMMotorController(int in1pin, int in2pin, int epin, std::string threadName);

	/**
	 * Destructor
	 */
	virtual ~SWPWMMotorController();

	/**
	 * Set duty cycle.
	 *
	 * Values outside of the range 0 to 100 will be ignored.
	 *
	 * @param dc duty cycle
	 */
	void setDutyCycle(int dc);

	/**
	 * Set direction for the motor.
	 *
	 * the directions are as follows: negative indicates reverse,
	 * 0 indicates stopped, and positive indicates forward.
	 *
	 * @param dir direction
	 */
	void setDirection(int dir);

	/**
	 * Start new thread running the run method
	 */
	void start();

	/**
	 * This is the run method for the class.
	 * It contains the code that is to run periodically
	 * on the given thread.
	 */
	void run();

	/**
	 * this method will stop the thread and its execution.
	 * In the case of this particular class,
	 * it will also shutdown the network socket.
	 */
	void stop();

private:
	exploringRPi::GPIO* forwardPin;
	exploringRPi::GPIO* backwardPin;
	exploringRPi::GPIO* enablePin;
	int dutyCycle = 0;
	int count = 0;
};

#endif /* SWPWMMOTORCONTROLLER_H */
