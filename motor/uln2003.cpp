/*
 * File: uln2003.cpp
 * Description: Interfaces with the ULN2003 driver
 *   to drive the Elegoo 28BYJ-48 stepper motor
 */

#include <unistd.h>
#include "stepper.h"

ULN2003(int pin1, int pin2, int pin3, int pin4) {
  IN1 = new GPIO(pin1);
  IN1->setDirection(OUTPUT);
  IN2 = new GPIO(pin2);
  IN2->setDirection(OUTPUT);
  IN3 = new GPIO(pin3);
  IN3->setDirection(OUTPUT);
  IN4 = new GPIO(pin4);
  IN4->setDirection(OUTPUT);

  direction = Stepper::CW;

  step = 0;
  stepCount = 0;
}

void ULN2003::startRotation(Stepper::DIRECTION direction) {
  // TODO - implement this as a multithreaded function
  this->direction = direction;
  while(true) {
    step();
    usleep(800); // 800 us delay
  }
}

void ULN2003::stopRotation() {
  // TODO
}

void ULN2003::rotate(Stepper::DIRECTION direction, double degrees) {
  // TODO
}

double ULN2003::getAngle() {
  // TODO
  return 0;
}

void ULN2003::step() {
  switch (step) {
  case 0:
    writePins(GPIO::LOW, GPIO::LOW, GPIO::LOW, GPIO::HIGH);
    break;
  case 1:
    writePins(GPIO::LOW, GPIO::LOW, GPIO::HIGH, GPIO::HIGH);
    break;
  case 2:
    writePins(GPIO::LOW, GPIO::LOW, GPIO::HIGH, GPIO::LOW);
    break;
  case 3:
    writePins(GPIO::LOW, GPIO::HIGH, GPIO::HIGH, GPIO::LOW);
    break;
  case 4:
    writePins(GPIO::LOW, GPIO::HIGH, GPIO::LOW, GPIO::LOW);
    break;
  case 5:
    writePins(GPIO::HIGH, GPIO::HIGH, GPIO::LOW, GPIO::LOW);
    break;
  case 6:
    writePins(GPIO::HIGH, GPIO::LOW, GPIO::LOW, GPIO::LOW);
    break;
  case 7:
    writePins(GPIO::HIGH, GPIO::LOW, GPIO::LOW, GPIO::HIGH);
    break;
  default:
    writePins(GPIO::LOW, GPIO::LOW, GPIO::LOW, GPIO::LOW);
    break;
  }
  incremementStep();
}

// TODO - refactor this function
void ULN2003::incremementStep() {
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

void writePins(GPIO::VALUE pin1, GPIO::VALUE pin2, GPIO::VALUE pin3, GPIO::VALUE pin4) {
  IN1->setValue(pin1);
  IN2->setValue(pin2);
  IN3->setValue(pin3);
  IN4->setValue(pin4);
}

ULN2003::~ULN2003() {
  delete IN1;
  delete IN2;
  delete IN3;
  delete IN4;
}

