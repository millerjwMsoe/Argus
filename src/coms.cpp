/*
 * File: coms.cpp
 * Description: Communicates w/ an Arduino via RS232
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <sstream>
#include "json.hpp"
#include "coms.h"
#include "rs232.h"

#define BUF_SIZE 1024

using namespace std;
using json = nlohmann::json;

Coms::Coms(string threadName) : PeriodicTask (threadName) {
    m_comport = RS232_GetPortnr("ttyACM0"); // TODO: determine this programatically?
    m_baudrate = 9600;
}

void Coms::setup() {
	char mode[] = {'8', 'N', '1', 0};
	if(RS232_OpenComport(m_comport, m_baudrate, mode)){
		printf("Cant open comport\n");
	}

	usleep(2000000);
}

// This runs every `task_period` ms. Set `task_period` to 1000000ms for good behavior
void Coms::run() {
	unsigned char str_recv[BUF_SIZE];
	int n = RS232_PollComport(m_comport, str_recv, (int)BUF_SIZE);
	if(n > 0){
		str_recv[n] = 0;
		//printf("Received %i bytes: '%s'\n", n, (char *)str_recv);
	}
        ostringstream oss;
        for(int i=0; i<n; i++) {
            oss << str_recv[i];
        }
        auto str = oss.str();
        try {
        	auto j = json::parse(str);
		cout << "Distance 1 [mm]: " << j["DIST1"] << endl;
		cout << "Distance 2 [mm]: " << j["DIST2"] << endl;
		cout << "Left Front [RPM]: " << j["LF_RPM"] << endl;
		cout << "Right Front [RPM]: " << j["RF_RPM"] << endl;
		cout << "Left Rear [RPM]: " << j["LR_RPM"] << endl;
		cout << "Right Rear [RPM]: " << j["RR_RPM"] << endl;
		cout << "Bucket Volume [%]: " << j["VOLUME"] << endl;
		cout << "Bucket Mass [kg]: " << j["MASS"] << endl;
	} catch (nlohmann::detail::parse_error e) {
		cout << "bad packet" << endl;
	}
}
