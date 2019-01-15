/*
 * PCA9685Driver.h
 *
 *  Created on: Jul 2, 2018
 *      Author: se3910
 */

#ifndef PCA9685DRIVER_H_
#define PCA9685DRIVER_H_

#include "I2CDevice.h"
#include <stdint.h>

class PCA9685Driver {
private:
	exploringRPi::I2CDevice *device;
	unsigned int address;
	unsigned int bus;



public:
	PCA9685Driver(unsigned int bus, unsigned int deviceAddress);
	virtual ~PCA9685Driver();

	void setPwm(unsigned int channel, uint16_t onTime, uint16_t offTime);
	/**
	 * This method will set the width of the given pulse.
	 * @param width The width is the time the pulse will be on, given in us.
	 */
	void setPulseWidth(unsigned int channel, uint16_t width);

	void init();
	void shutdown();



};

#endif /* PCA9685DRIVER_H_ */
