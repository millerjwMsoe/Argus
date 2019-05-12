/*
 * File: angleFinder.h
 * Description: Uses IR Receiver and Stepper to find angle of incident light
 */

#ifndef ANGLE_FINDER_H_
#define ANGLE_FINDER_H_

#include "PeriodicTask.h"
#include "irreceiver.h"
#include "stepper.h"

class AngleFinder : public PeriodicTask {
public:
    AngleFinder(Stepper* stepper, IRReceiver* receiver, std::string threadName);

    // overrides PeriodicTask::run(). Runs periodically on its own thread.
    void run();

    // returns the angle at which the bin was last seen
    double getAngle();

private:
    Stepper::DIRECTION opposite(Stepper::DIRECTION dir);
    Stepper* m_stepper;
    IRReceiver* m_receiver;
    bool m_seeking;
    double m_start; // the last angle at which light was detected
    double m_target; // the limit of how far to look for light in one direction
    Stepper::DIRECTION m_direction; // which direction to look for light in
    const int m_searchAngle = 45; // how many degrees to sweep before turning around
    double m_searchCount; // how many search sweeps since light was detected
    double m_lastFound; // angle at which the light was last found

};

#endif /* ANGLE_FINDER_H_ */
