/*
* File: ImageTransmitter.cpp
* Author: Jonathan Enderle
* Created: 10/25/18
 */


#include "ImageTransmitter.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>
#include "time_util.h"

#include <iostream>
using namespace std;

ImageTransmitter::ImageTransmitter(char* machineName, int port) {
	destinationMachineName = machineName;
	myPort = port;
}

ImageTransmitter::~ImageTransmitter() { }

int ImageTransmitter::streamImage(Mat *image) {
	// cout << "ImageTransmitter::streamImage() | BEGIN" << endl;
	int retval = -1;

	// If the image and destination machine are not null,
	if(image != NULL && destinationMachineName != NULL) {

		// cout << "ImageTransmitter::streamImage() | ENTER IF STATEMENT" << endl;


		// 1a. Increment the image count.
		imageCount++;

		// 1b. Initialize the socket sockfd to be a DGRAM.
		struct sockaddr_in serv_addr;
		struct hostent *server;
		int serverlen;
		sockfd = socket(AF_INET, SOCK_DGRAM, 0);

		// 1c. If there is an error with 1b, abort with an error message.
		if(sockfd < 0) {
			perror("ERROR opening socket");
			exit(-1);
		}

		// 1d. Get the host by name and set up a server instance.
		server = gethostbyname(destinationMachineName);

		// 1e. If the server is NULL, exit.
		if(server == NULL) {
			fprintf(stderr, "ERROR, no such host\n");
			exit(-1);
		}

		// 1f. Set up the rest of the UDP parameters.
		bzero((char *)&serv_addr, sizeof(serv_addr));
		serv_addr.sin_family = AF_INET;
		memcpy((char *) &serv_addr.sin_addr.s_addr, (char *) server->h_addr, server->h_length);
		serv_addr.sin_port = htons(myPort);

		// 1g. Obtain the image rows, columns, and message size (which is 3 * columns + 24).
		int rows = image->rows;
		int cols = image->cols;
		int messageSize = 3 * cols + 24;


		// 1h. Allocate a buffer of message size length on the heap.
		char* buffer = (char*) malloc(messageSize);
		serverlen = sizeof(serv_addr);


		// 1i. Obtain the current timestamp in ms using the time_util library.
		int timestamp = current_timestamp();

		// cout << "ImageTransmitter::streamImage() | BEGIN MESSAGE 1" << endl;


		// 1j. Iterate (using `index' over the even rows of the image, creating a message to send which consists of the following general structure:
		for(int index=0; index<rows; index+=2) {

			// Integer 0: The start time for the transmission
			// Integer 1: The current timestamp for the current portion of the image
			// Integer 2: The count of the image.
			// Integer 3: The number of rows in the image.
			// Integer 4: The number of columns in the image
			// Integer 5: The index being sent
			// An array of columns * 3 bytes, representing the pixels in the current row.
			int32_t* header = (int32_t*) buffer;

			header[0] = htonl(timestamp);
			header[1] = htonl(timestamp);
			header[2] = htonl(imageCount);
			header[3] = htonl(rows);
			header[4] = htonl(cols);
			header[5] = htonl(index);

			memcpy(&header[6], &image->data[3*cols*index], cols*3);

			/*
			for(int p=0; p<cols; p++) {

				// Offset by 6 to start at buffer[6]
				// and multiply by 3 to have 3 ints per pixel.
				buffer[p*3+6] = image->data[3*cols*index + p];
				buffer[p*3+6+1] = image->data[3*cols*index + p + 1];
				buffer[p*3+6+2] = image->data[3*cols*index + p + 2];

			}
			*/

			// 1j.a Send to message to the destination.
			int lres = sendto(sockfd, buffer, messageSize, 0, (struct sockaddr *) &serv_addr, serverlen);
			if(lres < 0) {
				printf("%d c %d", lres, errno);
				perror("Transmit:");
				exit(-1);
			}
			// cout << "ImageTransmitter::streamImage() | LRES 1: " << lres << endl;

		}




		// cout << "ImageTransmitter::streamImage() | BEGIN MESSAGE 2" << endl;


		// 1k. Iterate (using `index' over the odd rows of the image, creating a message to send which consists of the following general structure:
		for(int index=1; index<rows; index+=2) {

			// Integer 0: The start time for the transmission
			// Integer 1: The current timestamp for the current portion of the image
			// Integer 2: The count of the image.
			// Integer 3: The number of rows in the image.
			// Integer 4: The number of columns in the image
			// Integer 5: The index being sent
			// An array of columns * 3 bytes, representing the pixels in the current row.
			int32_t* header = (int32_t*) buffer;

			header[0] = htonl(timestamp);
			header[1] = htonl(timestamp);
			header[2] = htonl(imageCount);
			header[3] = htonl(rows);
			header[4] = htonl(cols);
			header[5] = htonl(index);

			memcpy(&header[6], &image->data[3*cols*index], cols*3);

			/*
			for(int p=0; p<cols; p++) {

				// Offset by 6 to start at buffer[6]
				// and multiply by 3 to have 3 ints per pixel.
				buffer[p*3+6] = image->data[3*cols*index + p];
				buffer[p*3+6+1] = image->data[3*cols*index + p + 1];
				buffer[p*3+6+2] = image->data[3*cols*index + p + 2];

			}
			*/

			// 1k.a Send to message to the destination.
			int lres = sendto(sockfd, buffer, messageSize, 0, (struct sockaddr *) &serv_addr, serverlen);
			if(lres < 0) {
				printf("%d c %d", lres, errno);
				perror("Transmit:");
				exit(-1);
			}
			// cout << "ImageTransmitter::streamImage() | LRES 2: " << lres << endl;
		}

		// Free the message that was allocated on the heap.
		free(buffer);

		// Close the socket.
		close(sockfd);
	}


	// cout << "ImageTransmitter::streamImage() | EXIT" << endl;
	return retval;
}


