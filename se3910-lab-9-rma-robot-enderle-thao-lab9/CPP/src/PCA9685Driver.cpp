/*
 * PCA9685Driver.cpp
 *
 *  Created on: Jul 2, 2018
 *      Author: se3910
 */

#include "PCA9685Driver.h"
#include "pca9685_reg.h"
#include <chrono>
#include <thread>

PCA9685Driver::PCA9685Driver(unsigned int bus, unsigned int deviceAddress) {

	this->device= new exploringRPi::I2CDevice(bus, deviceAddress);
	this->bus=bus;
	this->address=deviceAddress;
}

PCA9685Driver::~PCA9685Driver() {
	delete device;
}

void PCA9685Driver::init()
{
	this->device->open();
	this->device->writeRegister(MODE1, 0b00110001); // Setting mode to sleep so we can change the default PWM frequency

	// Wait 1 ms
	std::this_thread::sleep_for(std::chrono::milliseconds((1)));

	// Write the prescale to setup a 20 ms period.
	this->device->writeRegister(PRE_SCALE, 0x79); // Setting mode to sleep so we can change teh default PWM frequency

	// Wait 1 ms
	std::this_thread::sleep_for(std::chrono::milliseconds((1)));

	// Set the preferred mode.
	this->device->writeRegister(MODE1, 0xa1); // Setting mode to sleep so we can change teh default PWM frequency

	// Wait 1 ms
	std::this_thread::sleep_for(std::chrono::milliseconds((1)));

	// Set the preferred mode.
	this->device->writeRegister(MODE2, 0b00000100); // Set to our prefered mode[Output logic state not inverted, Outputs change on STOP,
													// totem pole structure, When OE = 1 (output drivers not enabled), LEDn = 0]
}


void PCA9685Driver::setPwm(unsigned int channel, uint16_t onTime, uint16_t offTime)
{
	unsigned int startingAddress;

	startingAddress = 0x06 + 4 * channel;

	// Write to the given channel the on and off time.
	this->device->writeRegister(startingAddress, onTime & 0x00FF);
	this->device->writeRegister(startingAddress+1, (onTime>>8) & 0x00FF);
	this->device->writeRegister(startingAddress+2, offTime & 0x00FF);
	this->device->writeRegister(startingAddress+3, (offTime>>8) & 0x00FF);
}
/**
 * This method will set the width of the given pulse.
 * @param width The width is the time the pulse will be on, given in us.
 */
void PCA9685Driver::setPulseWidth(unsigned int channel, uint16_t width)
{
	uint16_t pulse = (uint16_t)(((uint32_t)width * 4096) / 20000);
	setPwm(channel, 0, pulse);
}


void PCA9685Driver::shutdown()
{

}
