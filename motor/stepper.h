/*
 * File: stepper.h
 * Description: Common interface for stepper motors
 */

#ifndef STEPPER_H_
#define STEPPER_H_

class Stepper {
public:
  // Rotating clockwise or counter-clockwise
  enum DIRECTION{ CW, CCW };

  virtual void startRotation(Stepper::DIRECTION) = 0;
  virtual void stopRotation() = 0;
  virtual void rotate(Stepper::DIRECTION, double degrees) = 0;

  // Return the current angle of the motor shaft, between 0 and 360°.
  // This value is relative to the orientation of the shaft at program start.
  virtual double getAngle() = 0;

  virtual ~Stepper();

};

#endif /* STEPPER_H_ */
