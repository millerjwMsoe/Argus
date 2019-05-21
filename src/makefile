# motor code makefile

all: motor calibrate

# dependencies generated with g++ -MM *.cpp
angleFinder.o: angleFinder.cpp angleFinder.h PeriodicTask.h \
 RunnableClass.h irreceiver.h stepper.h
binTriangulator.o: binTriangulator.cpp binTriangulator.h PeriodicTask.h \
 RunnableClass.h angleFinder.h irreceiver.h stepper.h
calibrate.o: calibrate.cpp GPIO.h uln2003.h PeriodicTask.h \
 RunnableClass.h stepper.h
coms.o: coms.cpp coms.h PeriodicTask.h RunnableClass.h rs232.h
GPIO.o: GPIO.cpp GPIO.h util.h
irreceiver.o: irreceiver.cpp irreceiver.h
main.o: main.cpp GPIO.h uln2003.h PeriodicTask.h RunnableClass.h \
 stepper.h tsop38238.h irreceiver.h angleFinder.h binTriangulator.h
PeriodicTask.o: PeriodicTask.cpp PeriodicTask.h RunnableClass.h
RunnableClass.o: RunnableClass.cpp RunnableClass.h
stepper.o: stepper.cpp stepper.h
tsop38238.o: tsop38238.cpp tsop38238.h GPIO.h irreceiver.h
uln2003.o: uln2003.cpp uln2003.h GPIO.h PeriodicTask.h RunnableClass.h \
 stepper.h
util.o: util.cpp util.h

# variables
CC = g++
COPTIONS = -g --save-temps -O0 -pthread
LOPTIONS = -g -pthread
OBJS = angleFinder.o binTriangulator.o coms.o GPIO.o irreceiver.o main.o \
 PeriodicTask.o RunnableClass.o rs232.o stepper.o tsop38238.o uln2003.o util.o
NAME = motor.out

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
