/*
 * File: binTriangulator.h
 * Description: Uses two IR angle finders to determine bin position
 */

#ifndef BIN_TRIANGULATOR_H_
#define BIN_TRIANGULATOR_H_

#include "PeriodicTask.h"
#include "angleFinder.h"

class BinTriangulator : public PeriodicTask {
public:
    BinTriangulator(AngleFinder* leftSensor, AngleFinder* rightSensor, std::string threadName);

    // overrides PeriodicTask::run(). Runs periodically on its own thread.
    void run();

private:
    AngleFinder* m_leftSensor;
    AngleFinder* m_rightSensor;

    double radFromDeg(double deg);
};

#endif /* BIN_TRIANGULATOR_H_ */
