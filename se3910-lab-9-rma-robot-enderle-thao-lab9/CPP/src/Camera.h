/*
* File: Camera.h
* Author: Jonathan Enderle
* Created: 10/25/18
 */

#ifndef CAMERA_H_
#define CAMERA_H_

#include "RunnableClass.h"
#include<opencv2/opencv.hpp>
#include <mutex>

using namespace std;
using namespace cv;

class Camera: public RunnableClass {
private:
    VideoCapture *capture;
    Mat * lastFrame;
    std::mutex mtx;
public:
    Camera(std::string threadName, int width, int height);
    virtual ~Camera();
    void run();
    void shutdown();
    Mat* takePicture();
};

#endif /* CAMERA_H_ */
