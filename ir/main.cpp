// Read from an IR receiver and print the results

#include <iostream>
#include "GPIO.h"

using namespace std;
using namespace exploringRPi;

int main(int argc, char* argv[]) {
    GPIO* irPin = new GPIO(12);
    irPin->setDirection(GPIO::INPUT);

    while(true) {
        GPIO::VALUE pinStatus = irPin->getValue();
        if(pinStatus == GPIO::HIGH) {
            cout << "Pin: HIGH" << endl;
        } else {
            cout << "Pin: LOW" << endl;
        }
    }

}
