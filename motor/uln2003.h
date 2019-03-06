/*
 * File: uln2003.h
 * Description: Interfaces with the ULN2003 driver
 *   to drive the Elegoo 28BYJ-48 stepper motor
 */

#ifndef ULN2003_H_
#define ULN2003_H_

#include "GPIO.h"
#include "PeriodicTask.h"
#include "stepper.h"

class ULN2003: public Stepper, public PeriodicTask {
public:

  ULN2003(int pin1, int pin2, int pin3, int pin4, std::string threadName);

  void startRotation(Stepper::DIRECTION);
  void stopRotation();
  void rotate(Stepper::DIRECTION, double degrees);

  // Return the current angle of the motor shaft, between 0 and 360°.
  // This value is relative to the orientation of the shaft at program start.
  double getAngle();

  void run(); // overrides PeriodicTask::run(); runs periodically on its own thread

  ~ULN2003();

private:
  exploringRPi::GPIO* IN1;
  exploringRPi::GPIO* IN2;
  exploringRPi::GPIO* IN3;
  exploringRPi::GPIO* IN4;

  Stepper::DIRECTION direction;

  // variables to keep track of steps and motor phases
  int step;
  int stepCount;
  const int STEPS_PER_REVOLUTION = 4096;

  // variables to determine whether the controller should drive the next phase
  bool continuousRotation;
  int stepsRemaining;

  // keep track of whether thread was started.
  // prefer to keep the fact that it's multithreaded invisible to user.
  bool threadStarted;

  void nextStep();
  void incrementStep();
  void writePins(exploringRPi::GPIO::VALUE pin1, exploringRPi::GPIO::VALUE pin2, exploringRPi::GPIO::VALUE pin3, exploringRPi::GPIO::VALUE pin4);
  void startThread();
};

#endif /* ULN2003_H_ */
