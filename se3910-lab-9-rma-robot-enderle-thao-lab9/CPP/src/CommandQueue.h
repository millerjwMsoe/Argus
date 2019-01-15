/*
 * CommandQueue.h
 *
 *  Created on: Sep 27, 2018
 *      Author: se3910
 */

#ifndef COMMAND_QUEUE_H
#define COMMAND_QUEUE_H

#include <queue>
#include <mutex>
#include <semaphore.h>

class CommandQueue {
public:
	CommandQueue();
	virtual ~CommandQueue();
	int dequeue();
	void enqueue(int value);
	bool hasItem();

private:
	std::queue<int> commandQueueContents;
	sem_t queueCountSemaphore;
	std::mutex queueMutex;

};

#endif /* COMMAND_QUEUE_H */
