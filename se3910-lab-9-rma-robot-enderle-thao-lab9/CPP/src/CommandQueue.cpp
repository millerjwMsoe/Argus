/*
 * CommandQueue.cpp
 *
 *  Created on: Sep 27, 2018
 *      Author: se3910
 */

#include "CommandQueue.h"
#include <iostream>

using namespace std;

CommandQueue::CommandQueue() {

}

CommandQueue::~CommandQueue() {

}

int CommandQueue::dequeue() {
	// cout << "CommandQueue::dequeue() BEGIN" << endl;
	sem_wait(&queueCountSemaphore);
	queueMutex.lock();
	int val = commandQueueContents.front();
	commandQueueContents.pop();
	queueMutex.unlock();
	return val;
}

void CommandQueue::enqueue(int value) {
	queueMutex.lock();
	commandQueueContents.push(value);
	queueMutex.unlock();
	sem_post(&queueCountSemaphore);
}

bool CommandQueue::hasItem() {
	bool hasItem = !commandQueueContents.empty();
	//cout << "CommandQueue::hasItem() " << hasItem << endl;
	return hasItem;
}
