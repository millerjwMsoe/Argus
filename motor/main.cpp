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

void stepper(int xw) {
  switch (Steps) {
    case 0:
      IN1->setValue(GPIO::LOW);
      IN2->setValue(GPIO::LOW);
      IN3->setValue(GPIO::LOW);
      IN4->setValue(GPIO::HIGH);
      break;
    case 1:
      IN1->setValue(GPIO::LOW);
      IN2->setValue(GPIO::LOW);
      IN3->setValue(GPIO::HIGH);
      IN4->setValue(GPIO::HIGH);
      break;
    case 2:
      IN1->setValue(GPIO::LOW);
      IN2->setValue(GPIO::LOW);
      IN3->setValue(GPIO::HIGH);
      IN4->setValue(GPIO::LOW);
      break;
    case 3:
      IN1->setValue(GPIO::LOW);
      IN2->setValue(GPIO::HIGH);
      IN3->setValue(GPIO::HIGH);
      IN4->setValue(GPIO::LOW);
      break;
    case 4:
      IN1->setValue(GPIO::LOW);
      IN2->setValue(GPIO::HIGH);
      IN3->setValue(GPIO::LOW);
      IN4->setValue(GPIO::LOW);
      break;
    case 5:
      IN1->setValue(GPIO::HIGH);
      IN2->setValue(GPIO::HIGH);
      IN3->setValue(GPIO::LOW);
      IN4->setValue(GPIO::LOW);
      break;
    case 6:
      IN1->setValue(GPIO::HIGH);
      IN2->setValue(GPIO::LOW);
      IN3->setValue(GPIO::LOW);
      IN4->setValue(GPIO::LOW);
      break;
    case 7:
      IN1->setValue(GPIO::HIGH);
      IN2->setValue(GPIO::LOW);
      IN3->setValue(GPIO::LOW);
      IN4->setValue(GPIO::HIGH);
      break;
    default:
      IN1->setValue(GPIO::LOW);
      IN2->setValue(GPIO::LOW);
      IN3->setValue(GPIO::LOW);
      IN4->setValue(GPIO::LOW);
      break;
    }
  Steps = (Steps + 1) % 8;
}

int main(int argc, char* argv[]) {
  IN1 = new GPIO(6);
  IN1->setDirection(GPIO::OUTPUT);
  IN2 = new GPIO(16);
  IN2->setDirection(GPIO::OUTPUT);
  IN3 = new GPIO(20);
  IN3->setDirection(GPIO::OUTPUT);
  IN4 = new GPIO(21);
  IN4->setDirection(GPIO::OUTPUT);
while(true) {
  for(int i=0; i<4096; i++){
    stepper(1);
    usleep(800); // 800ms delay
  }
  Direction = !Direction;
}
}
