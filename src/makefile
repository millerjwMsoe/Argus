# motor code makefile

all: motor calibrate

# dependencies generated with g++ -MM *.cpp
angleFinder.o: angleFinder.cpp angleFinder.h PeriodicTask.h \
 RunnableClass.h irreceiver.h stepper.h
binTriangulator.o: binTriangulator.cpp binTriangulator.h PeriodicTask.h \
 RunnableClass.h angleFinder.h irreceiver.h stepper.h
calibrate.o: calibrate.cpp GPIO.h uln2003.h PeriodicTask.h \
 RunnableClass.h stepper.h
coms.o: coms.cpp coms.h PeriodicTask.h RunnableClass.h rs232.h json.hpp
Camera.o: Camera.cpp Camera.h RunnableClass.h
GPIO.o: GPIO.cpp GPIO.h util.h
irreceiver.o: irreceiver.cpp irreceiver.h
main.o: main.cpp GPIO.h uln2003.h PeriodicTask.h RunnableClass.h \
 stepper.h tsop38238.h irreceiver.h angleFinder.h binTriangulator.h \
 Camera.h ImageTransmitter.h ImageCapturer.h
ImageCapturer.o: ImageCapturer.cpp ImageCapturer.h Camera.h \
 PeriodicTask.h RunnableClass.h ImageTransmitter.h
ImageTransmitter.o: ImageTransmitter.cpp ImageTransmitter.h
PeriodicTask.o: PeriodicTask.cpp PeriodicTask.h RunnableClass.h
RunnableClass.o: RunnableClass.cpp RunnableClass.h
stepper.o: stepper.cpp stepper.h
time_util.o: time_util.cpp time_util.h
tsop38238.o: tsop38238.cpp tsop38238.h GPIO.h irreceiver.h
uln2003.o: uln2003.cpp uln2003.h GPIO.h PeriodicTask.h RunnableClass.h \
 stepper.h
util.o: util.cpp util.h

# variables
CC = g++
COPTIONS = -g --save-temps -O0 -pthread -Wno-psabi
LOPTIONS = -g -pthread $(OPENCV)
OBJS = angleFinder.o binTriangulator.o coms.o GPIO.o irreceiver.o main.o \
 PeriodicTask.o RunnableClass.o rs232.o stepper.o tsop38238.o uln2003.o util.o \
 Camera.o ImageTransmitter.o ImageCapturer.o time_util.o
NAME = motor.out
OPENCV = -I/usr/include/opencv /usr/lib/arm-linux-gnueabihf/libopencv_calib3d.so -lopencv_calib3d /usr/lib/arm-linux-gnueabihf/libopencv_contrib.so -lopencv_contrib /usr/lib/arm-linux-gnueabihf/libopencv_core.so -lopencv_core /usr/lib/arm-linux-gnueabihf/libopencv_features2d.so -lopencv_features2d /usr/lib/arm-linux-gnueabihf/libopencv_flann.so -lopencv_flann /usr/lib/arm-linux-gnueabihf/libopencv_gpu.so -lopencv_gpu /usr/lib/arm-linux-gnueabihf/libopencv_highgui.so -lopencv_highgui /usr/lib/arm-linux-gnueabihf/libopencv_imgproc.so -lopencv_imgproc /usr/lib/arm-linux-gnueabihf/libopencv_legacy.so -lopencv_legacy /usr/lib/arm-linux-gnueabihf/libopencv_ml.so -lopencv_ml /usr/lib/arm-linux-gnueabihf/libopencv_objdetect.so -lopencv_objdetect /usr/lib/arm-linux-gnueabihf/libopencv_ocl.so -lopencv_ocl /usr/lib/arm-linux-gnueabihf/libopencv_photo.so -lopencv_photo /usr/lib/arm-linux-gnueabihf/libopencv_stitching.so -lopencv_stitching /usr/lib/arm-linux-gnueabihf/libopencv_superres.so -lopencv_superres /usr/lib/arm-linux-gnueabihf/libopencv_ts.so -lopencv_ts /usr/lib/arm-linux-gnueabihf/libopencv_video.so -lopencv_video /usr/lib/arm-linux-gnueabihf/libopencv_videostab.so -lopencv_videostab

# explicit rules
motor: $(OBJS)
	$(CC) $(LOPTIONS) -o $(NAME) $^

coms.o : coms.cpp
	$(CC) $(COPTIONS) -c coms.cpp rs232.c RunnableClass.cpp PeriodicTask.cpp

calibrate: calibrate.o GPIO.o RunnableClass.o PeriodicTask.o stepper.o uln2003.o util.o
	$(CC) $(LOPTIONS) -o calibrate.out $^

# implicit rules
%.o : %.cpp
	$(CC) $(COPTIONS) -c $<

# get Arduino port nr.
port:
	ls -lA /dev/serial/by-id

# clean
clean:
	rm -rf $(NAME) *.o *.ii *.s
