/*
* File: ImageTransmitter.h
* Author: Jonathan Enderle
* Created: 10/25/18
* Description: This class will transmit an image to a remote device.  The image will be transmitted as a set of UDP datagra
 */

#ifndef IMAGETRANSMITTER_H_
#define IMAGETRANSMITTER_H_

#include<opencv2/opencv.hpp>

using namespace cv;

class ImageTransmitter {
private:
    int myPort=5000;
    int sockfd=0;
    char* destinationMachineName=NULL;
    int imageCount = 0;

public:
    ImageTransmitter(char* machineName, int port);
    virtual ~ImageTransmitter();

    int streamImage(Mat *image);
};

#endif /* IMAGETRANSMITTER_H_ */
