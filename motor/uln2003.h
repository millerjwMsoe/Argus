/*
 * File: uln2003.h
 * Description: Interfaces with the ULN2003 driver
 *   to drive the Elegoo 28BYJ-48 stepper motor
 */

#ifndef ULN2003_H_
#define ULN2003_H_

#include "GPIO.h"
#include "stepper.h"

class ULN2003: public Stepper {
public:

  ULN2003(int pin1, int pin2, int pin3, int pin4);

  void startRotation(Stepper::DIRECTION);
  void stopRotation();
  void rotate(Stepper::DIRECTION, double degrees);

  // Return the current angle of the motor shaft, between 0 and 360°.
  // This value is relative to the orientation of the shaft at program start.
  double getAngle();

  ~ULN2003();

private:
  exploringRPi::GPIO* IN1;
  exploringRPi::GPIO* IN2;
  exploringRPi::GPIO* IN3;
  exploringRPi::GPIO* IN4;

  Stepper::DIRECTION direction;

  int step;
  int stepCount;

  void nextStep();
  void incrementStep();
  void writePins(exploringRPi::GPIO::VALUE pin1, exploringRPi::GPIO::VALUE pin2, exploringRPi::GPIO::VALUE pin3, exploringRPi::GPIO::VALUE pin4);
};

#endif /* ULN2003_H_ */
