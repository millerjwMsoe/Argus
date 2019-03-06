/*
 * File: uln2003.cpp
 * Description: Interfaces with the ULN2003 driver
 *   to drive the Elegoo 28BYJ-48 stepper motor
 */

#include <unistd.h>
#include "uln2003.h"

using namespace std;
using namespace exploringRPi;

ULN2003::ULN2003(int pin1, int pin2, int pin3, int pin4, string threadName) : PeriodicTask(threadName)  {
  IN1 = new GPIO(pin1);
  IN1->setDirection(GPIO::OUTPUT);
  IN2 = new GPIO(pin2);
  IN2->setDirection(GPIO::OUTPUT);
  IN3 = new GPIO(pin3);
  IN3->setDirection(GPIO::OUTPUT);
  IN4 = new GPIO(pin4);
  IN4->setDirection(GPIO::OUTPUT);

  direction = Stepper::CW;

  step = 0;
  stepCount = 0;
  continuousRotation = false;
  stepsRemaining = 0;
  threadStarted = false;
}

void ULN2003::startRotation(Stepper::DIRECTION direction) {
  if(!threadStarted) {
    startThread();
  }
  this->direction = direction;
  continuousRotation = true;
}

void ULN2003::stopRotation() {
  continuousRotation = false;
  stepsRemaining = 0;
}

void ULN2003::rotate(Stepper::DIRECTION direction, double degrees) {
  if(!threadStarted) {
    startThread();
  }
  int stepsFromDegrees = degrees / 360.0 * STEPS_PER_REVOLUTION;
  this->direction = direction;
  stepsRemaining = stepsFromDegrees;
}

void ULN2003::run() {
  if(continuousRotation || stepsRemaining > 0) {
    nextStep();
    if(stepsRemaining > 0) {
      stepsRemaining--;
    }
  }
}

double ULN2003::getAngle() {
  return (double) stepCount / STEPS_PER_REVOLUTION * DEGREES_PER_REVOLUTION;
}

void ULN2003::nextStep() {
  switch (step) {
  case 0:
    writePins(GPIO::HIGH, GPIO::LOW, GPIO::LOW, GPIO::HIGH);
    break;
  case 1:
    writePins(GPIO::HIGH, GPIO::LOW, GPIO::LOW, GPIO::LOW);
    break;
  case 2:
    writePins(GPIO::HIGH, GPIO::HIGH, GPIO::LOW, GPIO::LOW);
    break;
  case 3:
    writePins(GPIO::LOW, GPIO::HIGH, GPIO::LOW, GPIO::LOW);
    break;
  case 4:
    writePins(GPIO::LOW, GPIO::HIGH, GPIO::HIGH, GPIO::LOW);
    break;
  case 5:
    writePins(GPIO::LOW, GPIO::LOW, GPIO::HIGH, GPIO::LOW);
    break;
  case 6:
    writePins(GPIO::LOW, GPIO::LOW, GPIO::HIGH, GPIO::HIGH);
    break;
  case 7:
    writePins(GPIO::LOW, GPIO::LOW, GPIO::LOW, GPIO::HIGH);
    break;
  default:
    writePins(GPIO::LOW, GPIO::LOW, GPIO::LOW, GPIO::LOW);
    break;
  }
  incrementStep();
}

// TODO - refactor this function
void ULN2003::incrementStep() {
  if (direction == Stepper::CW) {
    step++;
    stepCount++;
  }
  if (direction == Stepper::CCW) {
    step--;
    stepCount--;
  }
  if (step > 7) {
    step = 0;
  }
  if (step < 0) {
    step = 7;
  }
}

void ULN2003::writePins(GPIO::VALUE pin1, GPIO::VALUE pin2, GPIO::VALUE pin3, GPIO::VALUE pin4) {
  IN1->setValue(pin1);
  IN2->setValue(pin2);
  IN3->setValue(pin3);
  IN4->setValue(pin4);
}

void ULN2003::startThread() {
  threadStarted = true;
  this->setTaskPeriod(1);
  this->start();
}

ULN2003::~ULN2003() {
  delete IN1;
  delete IN2;
  delete IN3;
  delete IN4;
}

