/*
 * File: tsop38238.cpp
 * Description: Driver for the TSOP38238 IR receiver
 */

#include "uln2003.h"

using namespace std;
using namespace exploringRPi;

ULN2003::ULN2003(int pin) {
    m_pin = new GPIO(pin);
    m_pin->setDirection(GPIO::INPUT);
}

bool TSOP38238::lightDetected() {
    GPIO::VALUE pinStatus = m_pin->getValue();
    if(pinStatus == GPIO::HIGH) {
        return false;
    } else {
        return true;
    }
}


void TSOP38238::startThread() {
  threadStarted = true;
  this->setTaskPeriod(1);
  this->start();
}

TSOP38238::~TSOP38238() {
  delete m_pin;
}

