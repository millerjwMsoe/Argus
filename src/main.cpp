/*
 * File: main.cpp
 * Description: main
 */

#include <iostream>
#include <unistd.h>
#include "GPIO.h"
#include "uln2003.h"
#include "tsop38238.h"


using namespace std;
using namespace exploringRPi;

int main(int argc, char* argv[]) {
  Stepper* stepper = new ULN2003(6,16,20,21, "Stepper");
  IRReceiver* receiver = new TSOP38238(12);

  stepper->rotate(Stepper::CW, 360);
  cout << receiver->lightDetected() << endl;
  sleep(5);
  stepper->rotate(Stepper::CCW, 180);
  cout << receiver->lightDetected() << endl;
  sleep(3);
  cout << stepper->getAngle() << endl;
  cout << receiver->lightDetected() << endl;
  stepper->rotate(Stepper::CW, 180);
  sleep(3);
}
