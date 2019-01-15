/*
 * ImageCapturer.h
 *
 *  Created on: Oct 25, 2018
 *      Author: se3910
 */

#ifndef IMAGECAPTURER_H_
#define IMAGECAPTURER_H_

#include "PeriodicTask.h"
#include "Camera.h"
#include "ImageTransmitter.h"
#include <opencv2/opencv.hpp>

class ImageCapturer : public PeriodicTask {
private:
    Camera* myCamera;
    ImageTransmitter *myTrans;
    int imageWidth;
    int imageHeight;
    Size *size;
public:
    ImageCapturer(std::string threadName, Camera *referencedCamera, ImageTransmitter *trans, int width, int height);

    virtual ~ImageCapturer();
    virtual void run();
};
#endif /* IMAGECAPTURER_H_ */
