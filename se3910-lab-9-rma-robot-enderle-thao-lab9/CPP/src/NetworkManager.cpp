/*
 * File: NetworkManager.cpp
 * Class: SE3910 - Dr. Schilling
 * Created: Sep 27 2018
 * Author: Jonathan Enderle
 */

#include "NetworkManager.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "CommandQueue.h"

using namespace std;

// print an error message - author: Dr. Schilling
void error(string msg) {
	perror(msg.c_str());
	exit(-1);
}

NetworkManager::NetworkManager(int port, CommandQueue* queue[], std::string threadName) : RunnableClass(threadName) {
	portNumber = port;
	referenceQueue = queue;
	server_fd = 0;
}

NetworkManager::~NetworkManager() { }

// With code from Dr. Schilling
void NetworkManager::run() {
	cout << "NetworkManager::run() BEGIN" << endl;
	int sockfd, newsockfd;
	socklen_t clilen;
	struct sockaddr_in serv_addr, cli_addr;

	// Create a socket.
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	// If the return is less than 0, then the socket failed to create.
	if (sockfd < 0) {
		error("ERROR opening socket");
	}

	// Initialize the buffer to all zeros.
	memset((void*) &serv_addr, 0, sizeof(serv_addr));

	// Setup the server address structure.
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portNumber);

	// Bind socket
	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
		error("ERROR on binding");
	}

	// Listen for clients on this socket
	listen(sockfd, 5);
	clilen = sizeof(cli_addr);

	// block until we receive a client
	newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
	if (newsockfd < 0) {
		error("ERROR on accept");
	}


	int msg_length; // when msg_length == 0, the socket was closed.

	while(keepGoing && msg_length > 0) {
		// create a clean buffer
		struct networkMessageStruct buffer;
		memset(&buffer, 0, sizeof(struct networkMessageStruct));

		msg_length = receiveNetworkMessageStruct(&buffer, newsockfd);

		// process data
		if((buffer.messageDestination ^ buffer.message) == buffer.xorChecksum) {
			// convert to HEX
			// std::cout << "NetworkManager::run() " << std::hex << buffer.message << endl;
			referenceQueue[buffer.messageDestination-1]->enqueue(buffer.message);
		} else {
			printf("Checksums don't match!\n");
		}
	}

}

void NetworkManager::stop() {

	// TODO - close sockets

}

int NetworkManager::receiveNetworkMessageStruct(networkMessageStruct* destination, int socket) {
	// receive data
	int n = recv(socket, (void*)destination, sizeof(struct networkMessageStruct), MSG_WAITALL);
	if (n < 0) {
		error("ERROR reading from socket.");
	}

	// switch endianness
	destination->messageDestination=ntohl(destination->messageDestination);
	destination->message=ntohl(destination->message);
	destination->xorChecksum=ntohl(destination->xorChecksum);

	return n;
}


