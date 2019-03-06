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
    AngleFinder(Stepper stepper, IRReceiver receiver, std::string threadName);

    // overrides PeriodicTask::run(). Runs periodically on its own thread.
    void run();

private:
    Stepper m_stepper;
    IRReceiver m_receiver;
};

#endif /* ANGLE_FINDER_H_ */
