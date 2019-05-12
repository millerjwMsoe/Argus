/*
 * File: binTriangulator.cpp
 * Description: Uses two IR angle finders to determine bin position
 */

#include <iostream>
#include <cmath>
#include <iostream>
#include "binTriangulator.h"

using namespace std;

BinTriangulator::BinTriangulator(AngleFinder* leftSensor, AngleFinder* rightSensor, std::string threadName) : PeriodicTask (threadName) {
    m_leftSensor = leftSensor;
    m_rightSensor = rightSensor;
}

double BinTriangulator::radFromDeg(double deg) {
    double pi = 3.1415926535897;
    return deg * pi / 180.0;
}


void BinTriangulator::run() {
    /*                  c: bin angle
    c  x`\              r: right sensor angle
        \ ``\           l: left sensor angle
      R  \   ``\  L     C: distance between sensors (known)
          \     ``\     R: distance to right sensor
        l  x-------x r  L: distance to left sensor
               C
    */

    double C = 11; // TODO: hardcoded to 11"

    double l = m_leftSensor->getAngle();
    double r = m_rightSensor->getAngle();

    // get angles in range 0 - 360
    int degrees = 360;
    l = fmod(((fmod(l, degrees)) + degrees), degrees);
    r = fmod(((fmod(r, degrees)) + degrees), degrees);

    // convert from motor angle to the angle it creates in triangle
    if(l > 90 && l < 270) {
        l = l - 90;
    } else {
        l = 90 - l;
    }
    if(r > 90 && r < 270) {
        r = r - 90;
    } else {
        r = 90 - r;
    }

    double c = 180 - l - r;
    // Law of Sines
    double R = cos(radFromDeg(r)) * C / sin(radFromDeg(c));

    // SOH CAH TOA
    double x = R * cos(radFromDeg(l));
    double y = R * sin(radFromDeg(l));

    cout << "Perp. dist. to bin: " << y << endl;
    cout << "Horiz. dist. from bin: " << x << endl;
}
