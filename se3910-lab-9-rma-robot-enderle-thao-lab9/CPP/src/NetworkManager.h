/*
 * File: NetworkManager.h
 * Class: SE3910 - Dr. Schilling
 * Created: Sep 27 2018
 * Author: Jonathan Enderle
 */

#ifndef NETWORK_MANAGER_H
#define NETWORK_MANAGER_H

#include <string>
#include "RunnableClass.h"

class CommandQueue;

/**
 * Represents a 'packet' of information from the Java app.
 */
struct networkMessageStruct
{
	int32_t messageDestination; // index of command queue (1-indexed)
	int32_t message;
	int32_t xorChecksum;
};

/**
 * Listens for data on a port and adds it to a queue of commands
 */
class NetworkManager: public RunnableClass {
public:
	/**
	 * Constructor
	 * @param port port to listen on
	 * @param queue queue of commands to add to
	 * @param threadName name of the thread
	 */
	NetworkManager(int port, CommandQueue* queue[], std::string threadName);

	/**
	 * Destructor
	 */
	virtual ~NetworkManager();

	/**
	 * Start up this NetworkManager as a thread
	 */
	void run();

	/**
	 * Stop this thread
	 */
	void stop();

private:
	/**
	 * Helper method to receive a message from Java app
	 * @param destination where to write the message
	 * @param socket socket to read from
	 * @return number of bytes received
	 */
	int receiveNetworkMessageStruct(networkMessageStruct* destination, int socket);

	/**
	 * The port number we listen on
	 */
	int portNumber;

	/**
	 * Array of command queues
	 */
	CommandQueue** referenceQueue;

	/**
	 * Magic
	 */
	int server_fd;
};

#endif /* NETWORK_MANAGER_H */
