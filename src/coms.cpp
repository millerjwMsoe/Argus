/*
 * File: coms.cpp
 * Description: Communicates w/ an Arduino via RS232
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include "coms.h"
#include "rs232.h"

#define BUF_SIZE 1024

using namespace std;

Coms::Coms(string threadName) : PeriodicTask (threadName) {
    m_comport = 16;
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
		printf("Received %i bytes: '%s'\n", n, (char *)str_recv);
	}
}
