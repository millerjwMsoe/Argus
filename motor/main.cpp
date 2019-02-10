/*
 * File: TODO.cpp
 * Description: contains driver code for the Elegoo 28BYJ-48 motor
 */

#include <iostream>
#include <unistd.h>
#include "GPIO.h"


using namespace std;
using namespace exploringRPi;
using GPIO::VALUE;
using GPIO::HIGH;
using GPIO::LOW;

int Steps = 0;
bool Direction = true;

GPIO* IN1;
GPIO* IN2;
GPIO* IN3;
GPIO* IN4;

void incremementSteps() {
  if (Direction == 1) {
    Steps++;
  }
  if (Direction == 0) {
    Steps--;
  }
  if (Steps > 7) {
    Steps = 0;
  }
  if (Steps < 0) {
    Steps = 7;
  }
}

void writePins(VALUE pin1, VALUE pin2, VALUE pin3, VALUE pin4) {
  IN1->setValue(pin1);
  IN2->setValue(pin2);
  IN3->setValue(pin3);
  IN4->setValue(pin4);
}

void step() {
  switch (Steps) {
  case 0:
    writePins(LOW, LOW, LOW, HIGH);
    break;
  case 1:
    writePins(LOW, LOW, HIGH, HIGH);
    break;
  case 2:
    writePins(LOW, LOW, HIGH, LOW);
    break;
  case 3:
    writePins(LOW, HIGH, HIGH, LOW);
    break;
  case 4:
    writePins(LOW, HIGH, LOW, LOW);
    break;
  case 5:
    writePins(HIGH, HIGH, LOW, LOW);
    break;
  case 6:
    writePins(HIGH, LOW, LOW, LOW);
    break;
  case 7:
    writePins(HIGH, LOW, LOW, HIGH);
    break;
  default:
    writePins(LOW, LOW, LOW, LOW);
    break;
  }
  incremementSteps();
}

void ctor(int pin1, int pin2, int pin3, int pin4) {
  IN1 = new GPIO(pin1);
  IN1->setDirection(OUTPUT);
  IN2 = new GPIO(pin2);
  IN2->setDirection(OUTPUT);
  IN3 = new GPIO(pin3);
  IN3->setDirection(OUTPUT);
  IN4 = new GPIO(pin4);
  IN4->setDirection(OUTPUT);
}

int main(int argc, char* argv[]) {
  ctor(6,16,20,21);
  while(true) {
    for(int i=0; i<4096; i++){
      step();
      usleep(800); // 800ms delay
    }
    Direction = !Direction;
  }
}
