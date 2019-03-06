/*
 * File: angleFinder.cpp
 * Description: Uses IR Receiver and Stepper to find angle of incident light
 */

#include <iostream>
#include "angleFinder.h"

using namespace std;

AngleFinder::AngleFinder(Stepper stepper, IRReceiver receiver, string threadName) : PeriodicTask (threadName) {
    m_stepper = stepper;
    m_receiver = receiver;
}

void AngleFinder::run() {
    if(m_receiver->lightDetected()) {
        cout << "Bin at: " << m_stepper->getAngle() << endl;
    } else {
        cout << "Bin not found." << endl;
        m_stepper->rotate(Stepper::CW);
    }
}