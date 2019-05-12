/*
 * File: binTriangulator.cpp
 * Description: Uses two IR angle finders to determine bin position
 */

#include <iostream>
#include "binTriangulator.h"

using namespace std;

BinTriangulator::BinTriangulator(AngleFinder* leftAngle, AngleFinder* rightAngle, std::string threadName) : PeriodicTask (threadName) {
    m_leftAngle = leftAngle;
    m_rightAngle = rightAngle;
}

void BinTriangulator::run() {
    // runs every 500 ms or so
}

