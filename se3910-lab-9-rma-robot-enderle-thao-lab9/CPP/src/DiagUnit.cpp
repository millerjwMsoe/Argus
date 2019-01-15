/*
 * File: DiagUnit.h
 * Created: Oct 11, 2018
 * Author: Jonathan Enderle
 */


#include "DiagUnit.h"
#include "ADReader.h"
#include "CommandQueue.h"
#include "NetworkCommands.h"
#include <iostream>


using namespace std;


DiagUnit::DiagUnit(CommandQueue* referencequeue, string threadName) : RunnableClass(threadName) {
	this->referencequeue = referencequeue;
	this->adReader = nullptr;
}

DiagUnit::DiagUnit(CommandQueue* referencequeue, ADReader* adReference, std::string threadName) : RunnableClass(threadName) {
	this->referencequeue = referencequeue;
	this->adReader = adReference;
}


DiagUnit::~DiagUnit() {
	delete referencequeue;
}


void DiagUnit::run() {
	while (RunnableClass::keepGoing){
		cout << "Keep Going Status (DiagUnit):" << RunnableClass::keepGoing << endl;
		int returnVal = DiagUnit::referencequeue->dequeue();
		if (returnVal == DIAGNOSTIC_REPORT_REQUEST ) {
			printThreads();
		} else if (returnVal == DIAGNOSTIC_RESET_REQUEST){
			resetAllThreadInformation();
		} else if (returnVal == DIAGNOSTIC_BATTERY_VOLTAGE_DISPLAY_REQUEST) {
			// value 1023 = 5 volts = 10 volts 
			// 10 * count / 1024
			int count = adReader->readChannelValue(10);
			count = 10 * count / 1024;
			cout << "Battery Voltage: " << count << endl;	

		} 

	}
}




