/*
 * ImageCapturer.cpp
 *
 *  Created on: Oct 25, 2018
 *      Author: se3910
 */

#include "ImageCapturer.h"
#include <time.h>
#include <unistd.h>
#include <iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;

ImageCapturer::ImageCapturer(string threadName, Camera* cam, ImageTransmitter* imgTrans, int num1, int num2 ) : PeriodicTask(threadName) {
	cout << "ImageCapturer::ImageCapturer() | BEGIN" << endl;
    myCamera = cam;
    myTrans = imgTrans;
    imageWidth = num1;
    imageHeight = num2;
    cout << "ImageCapturer::ImageCapturer() | EXIT" << endl;
}

ImageCapturer::~ImageCapturer(){
    delete size;
    delete myCamera;
    delete myTrans;
    delete size;
}

void ImageCapturer::run() {
	// cout << "ImageCapturer::run() | BEGIN" << endl;
    // Obtain the time since the epoch from the system clock in ms.
    long diff1, diff2, diff3;
    milliseconds start1 = duration_cast< milliseconds >(system_clock::now().time_since_epoch());

    // cout << "ImageCapturer::run() | TAKING PHOTO" << endl;

    // Take the picture from the camera.
    Mat *photo = myCamera->takePicture();

    // cout << "ImageCapturer::run() | TOOK PHOTO" << endl;

    // If the image is not null, 
    if (photo != NULL) {
    	// cout << "ImageCapturer::run() | PHOTO NOT EMPTY" << endl;
    	// cout << "ImageCapturer::run() | OBTAINING TIME" << endl;
        // Obtain the time since the epoch from the system clock in ms
        milliseconds time1 = duration_cast< milliseconds >(system_clock::now().time_since_epoch());
        diff1 = time1.count() - start1.count();
        // cout << "ImageCapturer::run() | OBTAINED TIME" << endl;


		// cout << "ImageCapturer::run() | CREATING SIZE" << endl;

		// Resize the image according to the desired size, if a resize needs to occur.
		// TODO: add a check for resize need
		Size size(imageWidth, imageHeight);

		// cout << "ImageCapturer::run() | CREATED SIZE" << endl;
		// cout << "ImageCapturer::run() | STARTING RESIZE" << endl;

		// Mat *resizedImage = new Mat();
		milliseconds start2 = duration_cast< milliseconds >(system_clock::now().time_since_epoch());
		resize(*photo, *photo, size);

		// cout << "ImageCapturer::run() | FINISHED RESIZE" << endl;
		// cout << "ImageCapturer::run() | GETTING TIME" << endl;

		// Obtain the time since the epoch from the system clock in ms.
		milliseconds time2 = duration_cast< milliseconds >(system_clock::now().time_since_epoch());
		diff2 = time2.count() - start2.count();

		// cout << "ImageCapturer::run() | GOT TIME DIFF" << endl;
		// cout << "ImageCapturer::run() | STREAMING IMAGE" << endl;

		// Stream the image to the remote device.
		milliseconds start3 = duration_cast< milliseconds >(system_clock::now().time_since_epoch());
		myTrans->streamImage(photo);

		// cout << "ImageCapturer::run() | STREAMED IMAGE" << endl;

		// Obtain the time since the epoch from the system clock in ms.
		milliseconds time3 = duration_cast< milliseconds >(system_clock::now().time_since_epoch());
		diff3 = time3.count() - start3.count();

		// cout << "ImageCapturer::run() | DELETING PHOTO" << endl;

		// delete photo
		delete photo;

		// cout << "ImageCapturer::run() | DELETED PHOTO" << endl;


		// Print out to the console in ms the amount of time it took to grab the picture, resize the picture, and transmit the picture in ms.
		// cout << "Time to Grab photo: " << diff1 << endl;
		// cout << "Time to Resize photo: " << diff2 << endl;
		// cout << "Time to Transmit photo: " << diff3 << endl;
    }

}
