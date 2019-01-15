/**
 * @file
 * @author  Walter Schilling (schilling@msoe.edu)
 * @version 1.0
 *
 * @section LICENSE This is a piece of a template solution to the lab.
 *
 *
 * @section DESCRIPTION
 *      This file allows the user to read values from an A/D device on the robot.
 */
#ifndef ADREADER_H_
#define ADREADER_H_

#include "PeriodicTask.h"
#include "GPIO.h"
#include <string>
#include <mutex>

#define NUMBER_OF_AD_CHANNELS (11)

class ADReader: public PeriodicTask {
private:
	uint16_t dataValues[NUMBER_OF_AD_CHANNELS] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	uint16_t maxDataValue[NUMBER_OF_AD_CHANNELS] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	uint16_t minDataValue[NUMBER_OF_AD_CHANNELS] = { 0xFFFF, 0xFFFF, 0xFFFF,
			0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF};

	exploringRPi::GPIO *csIOPin;
	exploringRPi::GPIO *addressIOPin;
	exploringRPi::GPIO *clockPin;
	exploringRPi::GPIO *doutPin;

	/**
	 * This mutex prevents simultaneous access from multiple threads.
	 */
	std::mutex dataMutex;

	/**
	 * This method will cause the sensors to be read. When this is invoked, all 11 A/D channels will be read and populated into the array.
	 */
	void readSensors();

public:
	/**
	 * This is the constructor for the A/D reader.
	 * @param csPinNumber  This is the chip select GPIO pin.  For the Alphabot2, this pin is 5.
	 * @param clockPinNumber This is the clock pin that is to be used to clock in the data.  On the alphabot 2, this pin is 25.
	 * @param addressPinNumber This is the address pin on the A/D reader.  On the alphabot 2, this is GPIO 24.
	 * @param dinPinNumber This is the data pin.  On the alphabot 2, data is present on GPIO 23.
	 * @param threadName This is the name of the thread that this task is to use.
	 */
	ADReader(int csPinNumber, int clockPinNumber, int addressPinNumber,
			int dinPinNumber, std::string threadName);
	/**
	 * This method will clean up after the A/D reader is completed.
	 */
	virtual ~ADReader();

	/**
	 * This method will read the value from a given A/D channel.
	 * @param channel This is the channel that is to be read.  When invoked, the most recently read value will be returned.
	 * @return The return value will be 0<=returnValue<=1023, representing the 10 bit value read from the sensor.  The value returned will be the most recently read value.
	 */
	uint16_t readChannelValue(unsigned int channel);
	/**
	 * This method will read the maximum value from a given A/D channel.
	 * @param channel This is the channel that is to be read.  When invoked, the max value will be returned.
	 * @return The return value will be 0<=returnValue<=1023, representing the 10 bit value read from the sensor.  The value returned will be the max read value.
	 */
	uint16_t readChannelMax(unsigned int channel);
	/**
	 * This method will read the minimum value from a given A/D channel.
	 * @param channel This is the channel that is to be read.  When invoked, the min value will be returned.
	 * @return The return value will be 0<=returnValue<=1023, representing the 10 bit value read from the sensor.  The value returned will be the min read value.
	 */

	uint16_t readChannelMin(unsigned int channel);

	/**
	 * This is the run method for the class.  It contains the code that is to run periodically on the given thread.
	 */
	void run();
	/**
	 * this method will stop the thread and its execution.  In the case of this particular class, it will also shutdown the network socket.
	 */
	void stop();
};

#endif /* ADREADER_H_ */
