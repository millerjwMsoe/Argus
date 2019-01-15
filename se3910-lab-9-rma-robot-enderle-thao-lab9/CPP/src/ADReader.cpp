/*
 * ADReader.cpp
 *
 *  Created on: Jun 29, 2018
 *      Author: se3910
 */

#include "ADReader.h"
#include "TaskRates.h"

#define SHORTPAUSE() {int ct; for (ct=0; ct < 100; ct+=2){ct++; ct--;}}

ADReader::ADReader(int csPinNumber, int clockPinNumber, int addressPinNumber,
		int dinPinNumber, std::string threadName) :
		PeriodicTask(threadName) {
	csIOPin = new exploringRPi::GPIO(csPinNumber);
	// Set the pin to be an output pin.
	csIOPin->setDirection(exploringRPi::GPIO::OUTPUT);

	// Set the pin to be high.
	csIOPin->setValue(exploringRPi::GPIO::HIGH);

	clockPin = new exploringRPi::GPIO(clockPinNumber);
	// Set the pin to be an output pin.
	clockPin->setDirection(exploringRPi::GPIO::OUTPUT);

	// Set the pin to be high.
	clockPin->setValue(exploringRPi::GPIO::LOW);

	addressIOPin = new exploringRPi::GPIO(addressPinNumber);
	// Set the pin to be an output pin.
	addressIOPin->setDirection(exploringRPi::GPIO::OUTPUT);

	// Set the pin to be high.
	addressIOPin->setValue(exploringRPi::GPIO::LOW);

	doutPin = new exploringRPi::GPIO(dinPinNumber);
	// Set the pin to be an output pin.
	doutPin->setDirection(exploringRPi::GPIO::INPUT);
}

ADReader::~ADReader() {

	delete csIOPin;
	delete addressIOPin;
	delete clockPin;
	delete doutPin;
}

uint16_t ADReader::readChannelValue(unsigned int channel) {
	uint16_t retValue = 0;
	if (channel < NUMBER_OF_AD_CHANNELS) {
		std::lock_guard<std::mutex> guard(dataMutex);
		// Obtain the correct item from the array.
		retValue = dataValues[channel];
	}
	return retValue;
}
uint16_t ADReader::readChannelMax(unsigned int channel) {
	uint16_t retValue = 0;
	if (channel < NUMBER_OF_AD_CHANNELS) {
		std::lock_guard<std::mutex> guard(dataMutex);
		// Obtain the correct item from the array.
		retValue = maxDataValue[channel];
	}
	return retValue;

}
uint16_t ADReader::readChannelMin(unsigned int channel) {
	uint16_t retValue = 0;
	if (channel < NUMBER_OF_AD_CHANNELS) {
		std::lock_guard<std::mutex> guard(dataMutex);
		// Obtain the correct item from the array.
		retValue = minDataValue[channel];
	}
	return retValue;
}


/**
 * This is the run method for the class.  It contains the code that is to run periodically on the given thread.
 */
void ADReader::run() {
		readSensors();
}

void ADReader::readSensors() {
	// Note: The following table defines which of the 11 channels are active and actually read.
	// Other channels will return a 0 by default.
#define NUMBER_OF_ACTIVE_CHANNELS (6)
	static uint8_t activeChannels[NUMBER_OF_ACTIVE_CHANNELS] = {0, 1, 2, 3, 4, 10};
	
	
	// This code is based upon the python code provided as sample code for this robot and the AD Sensor.
	unsigned int currentChannel = 0;

	for (currentChannel = 0; currentChannel < NUMBER_OF_ACTIVE_CHANNELS; currentChannel++) {
		// Set the CS low.
		csIOPin->setValue(exploringRPi::GPIO::LOW);
		SHORTPAUSE();

		// Write out the address and simultaneously read in the 10 data bits.  The 4 bit address goes first.
		// Note that after the address is sent, 0's will be clocked for the rest of the values.
		unsigned int bitNumber;
		uint8_t tmp = (activeChannels[(currentChannel + 1 )%NUMBER_OF_ACTIVE_CHANNELS] ) << 4;
		uint16_t data = 0;

		for (bitNumber = 0; bitNumber < 10; bitNumber++) {
			// Send out the bits for the address.
			if (tmp & 0x80) {
				// Send out a 1 on the address bus.
				addressIOPin->setValue(exploringRPi::GPIO::HIGH);

			} else {
				// Send out a 0.
				addressIOPin->setValue(exploringRPi::GPIO::LOW);
			}
			// Shift tmp 1 bit to the left.
			tmp = tmp << 1;

			// Now read in the data bit.
			data = data << 1;
			if (doutPin->getValue() == exploringRPi::GPIO::HIGH) {
				data |= 0x0001;
			}

			// Set the clock high.
			clockPin->setValue(exploringRPi::GPIO::HIGH);

			SHORTPAUSE();

			// Set the clock low.
			clockPin->setValue(exploringRPi::GPIO::LOW);

			SHORTPAUSE();
		}
		// All 10 bits have been read.
		{
			// Lock the mutex.
			std::lock_guard<std::mutex> guard(dataMutex);
			// Write the data in.
			dataValues[activeChannels[(currentChannel)]] = data;

			if (data < minDataValue[activeChannels[(currentChannel)]]) {
				minDataValue[activeChannels[(currentChannel)]] = data;
			}
			if (data > maxDataValue[activeChannels[(currentChannel)]]) {
				maxDataValue[activeChannels[(currentChannel)]] = data;
			}
		}
		// Wait a bit for the next DA to complete.
		// This takes at a max 21 microseconds.  However, our delay is being set longer than that for stability purposes.
		std::this_thread::sleep_for(std::chrono::microseconds(50));
	}
	// Restore the chip select value.
	csIOPin->setValue(exploringRPi::GPIO::HIGH);

}
/**
 * this method will stop the thread and its execution.  In the case of this particular class, it will also shutdown the network socket.
 */
void ADReader::stop() {
	keepGoing = false;
}

