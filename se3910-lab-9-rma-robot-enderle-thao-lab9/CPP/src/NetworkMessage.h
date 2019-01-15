/**
 * @file
 * @author  Walter Schilling (schilling@msoe.edu)
 * @version 1.0
 *
 * @section LICENSE This is a piece of a template solution to the lab.
 *
 *
 * @section DESCRIPTION
 *
 * This file defines a network message.  A network message is sent over the socket to control the robot.  Within this network message there are three parts.
 * The first 32 bit integer defines the destination for the message.  The second 32 bits defines the specific message.  The third 32 bits is a checksum which verifies that the message
 * is correct.
 */

#ifndef NETWORKMESSAGE_H
#define NETWORKMESSAGE_H
#include  <cstdint>

/**
 * This structure represents a network message.
 */
struct networkMessageStruct
{
	/**
	 * This is the destination.  This is a numerical destination on the given device for the message.
	 */
	int32_t messageDestination;
	/**
	 * This is the message that is to be sent.
	 */
	int32_t message;
	/**
	 * This is the checksum which will verify that the message has been properly received.  It is a simple XOR of the words in the message.
	 */
	int32_t xorChecksum;
};

#endif

