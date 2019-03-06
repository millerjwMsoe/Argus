/*
 * File: tsop38238.h
 * Description: Driver for the TSOP38238 IR receiver
 */

#ifndef TSOP38238_H_
#define TSOP38238_H_

#include "GPIO.h"
#include "irreceiver.h"

class TSOP38238: public IRReceiver {
public:

  TSOP38238(int pin);

  bool lightDetected();

  ~TSOP38238();

private:
  exploringRPi::GPIO* m_pin;

};

#endif /* TSOP38238_H_ */
