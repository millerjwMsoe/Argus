/*
 * File: main.cpp
 * Description: main
 */

#include <iostream>
#include <unistd.h>
#include "GPIO.h"
#include "uln2003.h"
#include "tsop38238.h"
#include "angleFinder.h"
#include "binTriangulator.h"
#include "coms.h"
#include "Camera.h"
#include "ImageTransmitter.h"

using namespace std;
using namespace exploringRPi;

int main(int argc, char* argv[]) {
  Stepper* r_stepper = new ULN2003(6, 16, 20, 21, "RightStepper");
  Stepper* l_stepper = new ULN2003(22, 27, 17, 4, "LeftStepper");
  IRReceiver* r_receiver = new TSOP38238(12);
  IRReceiver* l_receiver = new TSOP38238(25);

  Coms* arduino = new Coms("RS232");
  arduino->setup();
  arduino->setTaskPeriod(1000);
  arduino->start();

  AngleFinder* r_angleFinder = new AngleFinder(r_stepper, r_receiver, "RightAngleFinder");
  AngleFinder* l_angleFinder = new AngleFinder(l_stepper, l_receiver, "LeftAngleFinder");
  r_angleFinder->setTaskPeriod(500);
  l_angleFinder->setTaskPeriod(500);
  r_angleFinder->start();
  l_angleFinder->start();

  BinTriangulator* tri = new BinTriangulator(l_angleFinder, r_angleFinder, "Triangulator");
  tri->setTaskPeriod(500);
  tri->start();

  Camera* myCamera = new Camera("Camera", 640, 360);
  myCamera->start();

  cout << "Usage: ./motor.out ip port" << endl << "e.g. ./motor.out 192.168.1.1 5555" << endl;
  ImageTransmitter* it = new ImageTransmitter(argv[1], atoi(argv[2]));
	ImageCapturer *is = new ImageCapturer("Image Streamer", myCamera, it, 320, 180);
	is->setTaskPeriod(100);
	is->start();

  tri->waitForShutdown(); // blocks

}
