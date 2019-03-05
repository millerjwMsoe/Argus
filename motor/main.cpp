/*
 * File: TODO.cpp
 * Description: contains driver code for the Elegoo 28BYJ-48 motor
 */

#include <iostream>
#include <unistd.h>
#include "GPIO.h"
#include "uln2003.h"


using namespace std;
using namespace exploringRPi;

int main(int argc, char* argv[]) {
  Stepper* stepper = new ULN2003(6,16,20,21, "Stepper");
  stepper->setTaskPeriod(1);
  stepper->start();
  stepper->rotate(Stepper::CW, 360);
}
