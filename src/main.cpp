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
  Stepper* stepper = new ULN2003(6,16,20,21, "Stepper");
  IRReceiver* receiver = new TSOP38238(12);

  AngleFinder* angleFinder = new AngleFinder(stepper, receiver, "Angle Finder");
  angleFinder->setTaskPeriod(10);
  angleFinder->start();
  angleFinder->waitForShutdown();
}
