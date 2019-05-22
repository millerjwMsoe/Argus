/*
* File: Camera.cpp
* Author: Jonathan Enderle
* Created: 10/25/18
 */

#include "Camera.h"

#include <iostream>

using namespace std;
using namespace cv; 

std::mutex mxt;
/*
Construct a new instance of the camera class.
Parameters
threadName	This is the name of the thread that is to be used to run the image capture.
width	This is the width of the natively captured images. This is the resolution the camera generates.
height	This is the height of the natively captured images. This is the resolution the camera generates.
*/
Camera::Camera(std::string threadName, int width, int height) : RunnableClass(threadName) {
	// set up capture
	// cout << "Camera::Camera() | BEGIN" << endl;
	// cout << "Camera::Camera() | CREATING VIDEOCAPTURE" << endl;
	capture = new VideoCapture(0);
	// cout << "Camera::Camera() | CREATED CAMERA" << endl;
	// cout << "Camera::Camera() | INITIALIZING CAPTURE FIELDS" << endl;
	capture->set(CV_CAP_PROP_FRAME_WIDTH, width);
	capture->set(CV_CAP_PROP_FRAME_HEIGHT, height);
	capture->set(CV_CAP_PROP_FPS, 60);
	// cout << "Camera::Camera() | INITIALIZED CAPTURE FIELDS" << endl;
	// cout << "Camera::Camera() | CREATING LASTFRAME" << endl;
	lastFrame = new Mat();
	// cout << "Camera::Camera() | EXIT" << endl;
}

/*
This is the destructor for the camera. It will delete all dynamically allocated objects.
*/
Camera::~Camera() {
	delete capture;
	delete lastFrame;
}

/*
This is the main thread for the camera. It will do the following:

If we are unable to connect exit.
While the thread is to keep running: 
2a. grab the next image from the camera. 
2b. Retrieve the image into the last frame.
*/
void Camera::run() {
	cout << "Camera::run() | BEGIN" << endl;
	while (keepGoing) {
		if (!capture->isOpened()) {
			cout << "Camera::run() | COULD NOT CONNECT" << endl;
			exit(-1);
		} else {
			// cout << "Camera::run() | GRABBING FRAME" << endl;
			capture->grab();
			mxt.lock();
			capture->retrieve(*lastFrame);
			mxt.unlock();
		}
	}
	cout << "Camera::run() | EXIT" << endl;
}

/*
This method will shutdown the camera, preventing further pictures form being taken. It basically sets keepGoing to false.

*/
void Camera::shutdown() {
	keepGoing = false;
}

/*
If the last frame was empty, return NULL.
Instantiate a new matrix.
Copy the data from the last frame into the return frame.
Return the frame.
*/
Mat* Camera::takePicture() {
	// cout << "Camera::takePicture() | BEGIN" << endl;
	if (lastFrame->empty()) {
		// cout << "Camera::takePicture() | RETURN NULL" << endl;
		return NULL; 
	} else {
		// cout << "Camera::takePicture() | TAKE THE PICTURE" << endl;
		Mat *returnFrame = new Mat();
		mxt.lock();
		lastFrame->copyTo(*returnFrame);
		mxt.unlock();
		// cout << "Camera::takePicture() | EXIT" << endl;
		return returnFrame;
	}
}




