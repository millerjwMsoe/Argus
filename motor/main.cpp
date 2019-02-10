/*
 * File: TODO.cpp
 * Description: contains driver code for the Elegoo 28BYJ-48 motor
 */

#include <iostream>
#include <unistd.h>
#include "GPIO.h"


using namespace std;
using namespace exploringRPi;

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

void writePins(GPIO::VALUE pin1, GPIO::VALUE pin2, GPIO::VALUE pin3, GPIO::VALUE pin4) {
  IN1->setValue(pin1);
  IN2->setValue(pin2);
  IN3->setValue(pin3);
  IN4->setValue(pin4);
}

void step() {
  switch (Steps) {
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
  incremementSteps();
}

void ctor(int pin1, int pin2, int pin3, int pin4) {
  IN1 = new GPIO(pin1);
  IN1->setDirection(GPIO::OUTPUT);
  IN2 = new GPIO(pin2);
  IN2->setDirection(GPIO::OUTPUT);
  IN3 = new GPIO(pin3);
  IN3->setDirection(GPIO::OUTPUT);
  IN4 = new GPIO(pin4);
  IN4->setDirection(GPIO::OUTPUT);
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
