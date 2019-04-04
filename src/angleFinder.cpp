/*
 * File: angleFinder.cpp
 * Description: Uses IR Receiver and Stepper to find angle of incident light
 */

#include <iostream>
#include "angleFinder.h"

using namespace std;

AngleFinder::AngleFinder(Stepper* stepper, IRReceiver* receiver, string threadName) : PeriodicTask (threadName) {
    m_stepper = stepper;
    m_receiver = receiver;
    m_seeking = true;
    m_searchCount = 1;
    m_start = 0;
    m_target = m_start + m_searchCount*m_searchAngle;
    m_direction = Stepper::CW;
}

void AngleFinder::run() {
    if(m_receiver->lightDetected()) { // currently getting signal
        cout << "Bin at: " << m_stepper->getAngle() << endl;
        m_stepper->stopRotation();
        m_seeking = false;
    } else if(!m_seeking) { // just lost signal -> start looking
        cout << "Lost signal." << endl;
        m_seeking = true;
        m_searchCount = 1;
        double current = m_stepper->getAngle();
        m_target = current + m_searchCount*m_searchAngle;
        m_direction = Stepper::CW;
        m_stepper->startRotation(m_direction);
    } // else: already seeking signal

    if(m_seeking) {
        cout << "Seeking..." << endl;
        if(m_direction == Stepper::CW) {
            if(m_stepper->getAngle() > m_target) {
                m_searchCount++;
                m_direction = opposite(m_direction);
                m_target = m_start - m_searchCount*m_searchAngle;
                m_stepper->startRotation(m_direction);
            }
        } else { // m_direction == Stepper::CCW
                m_searchCount++;
                m_direction = opposite(m_direction);
                m_target = m_start + m_searchCount*m_searchAngle;
                m_stepper->startRotation(m_direction);
        }
    }
}

Stepper::DIRECTION AngleFinder::opposite(Stepper::DIRECTION dir) {
    if(dir == Stepper::CW) {
        return Stepper::CCW;
    } else {
        return Stepper::CW;
    }
}
