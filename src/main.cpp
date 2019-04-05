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
#include "coms.h"

using namespace std;
using namespace exploringRPi;

int main(int argc, char* argv[]) {
  Stepper* r_stepper = new ULN2003(6, 16, 20, 21, "RightStepper");
  Stepper* l_stepper = new ULN2003(22, 27, 17, 4, "LeftStepper");
  IRReceiver* r_receiver = new TSOP38238(12);
  IRReceiver* l_receiver = new TSOP38238(25);

  Coms* arduino = new Coms("RS232");
  arduino->setup();
  arduino->setTaskPeriod(1000000);
  arduino->start();

  AngleFinder* r_angleFinder = new AngleFinder(r_stepper, r_receiver, "RightAngleFinder");
  AngleFinder* l_angleFinder = new AngleFinder(l_stepper, l_receiver, "LeftAngleFinder");
  r_angleFinder->setTaskPeriod(500);
  l_angleFinder->setTaskPeriod(500);
  r_angleFinder->start();
  l_angleFinder->start();
  r_angleFinder->waitForShutdown(); // blocks

}
