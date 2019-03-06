# motor code makefile

all: motor

# dependencies generated with g++ -MM *.cpp
GPIO.o: GPIO.cpp GPIO.h util.h
main.o: main.cpp GPIO.h uln2003.h PeriodicTask.h RunnableClass.h \
 stepper.h
PeriodicTask.o: PeriodicTask.cpp PeriodicTask.h RunnableClass.h
RunnableClass.o: RunnableClass.cpp RunnableClass.h
stepper.o: stepper.cpp stepper.h
uln2003.o: uln2003.cpp uln2003.h GPIO.h PeriodicTask.h RunnableClass.h \
 stepper.h
util.o: util.cpp util.h

# variables
CC = g++
COPTIONS = -g --save-temps -O0 -pthread
LOPTIONS = -g -pthread
OBJS = GPIO.o main.o PeriodicTask.o RunnableClass.o stepper.o uln2003.o util.o
NAME = motor.out

# explicit rules
motor: $(OBJS)
	$(CC) $(LOPTIONS) -o $(NAME) $^

# implicit rules
%.o : %.c
	$(CC) $(COPTIONS) -c $<

# clean
clean:
	rm -rf $(NAME) *.o *.ii *.s