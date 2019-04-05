/*
 * File: coms.h
 * Description: Communicates w/ an Arduino via RS232
 */

#ifndef COMS_H_
#define COMS_H_

#include "PeriodicTask.h"

class Coms : public PeriodicTask {
public:
    Coms(std::string threadName);

    // overrides PeriodicTask::run(). Runs periodically on its own thread.
    void run();

    void setup(); // sets up serial port; needs to be run before communicating

private:
    int m_baudrate;
    int m_comport;

};

#endif /* COMS_H_ */
