/*
 * File: main.cpp
 * Description: main
 */

#include <iostream>
#include <unistd.h>
#include "GPIO.h"
#include "uln2003.h"
#include "tsop38238.h"
#include "angleFinder.h"

using namespace std;
using namespace exploringRPi;

int main(int argc, char* argv[]) {
  Stepper* r_stepper = new ULN2003(6, 16, 20, 21, "RightStepper");
  Stepper* l_stepper = new ULN2003(22, 27, 17, 4, "LeftStepper");
  IRReceiver* r_receiver = new TSOP38238(12);
  IRReceiver* l_receiver = new TSOP38238(25);

  r_stepper->startRotation(Stepper::CW);
  l_stepper->startRotation(Stepper::CCW);
  int i=0;
  while(true) {
    cout << "Check #: " << i++ << endl;
    cout << "Left: " << l_receiver->lightDetected() << endl;
    cout << "Right: " << r_receiver->lightDetected() << endl;
    usleep(1000000);
  }

  AngleFinder* r_angleFinder = new AngleFinder(r_stepper, r_receiver, "RightAngleFinder");
//  angleFinder->setTaskPeriod(10);
//  angleFinder->start();
//  angleFinder->waitForShutdown();
}
