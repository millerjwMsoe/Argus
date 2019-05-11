/*
 * File: calibrate.cpp
 * Description: helper used to adjust the motors' starting positions
 */

#include <iostream>
#include <unistd.h>
#include "GPIO.h"
#include "uln2003.h"

using namespace std;
using namespace exploringRPi;

int main(int argc, char* argv[]) {
  Stepper* r_stepper = new ULN2003(6, 16, 20, 21, "RightStepper");
  Stepper* l_stepper = new ULN2003(22, 27, 17, 4, "LeftStepper");

  cout << "Usage: motor degrees" << endl;
  cout << "e.g. 'l 15' to rotate left motor 15 deg. clockwise" << endl;

  string motor;
  string deg;

  while(cin >> motor && cin >> deg) {

    int degrees = stoi(deg);

    Stepper::DIRECTION dir = Stepper::CW;
    if(degrees < 0) {
      dir = Stepper::CCW;
      degrees = abs(degrees);
    }

    if(motor == "l") {
      l_stepper->rotate(dir, degrees);
    } else if(motor == "r") {
      r_stepper->rotate(dir, degrees);
    } else {
      cout << "ignored." << endl;
    }

  }


}
