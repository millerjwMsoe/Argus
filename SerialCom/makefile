all: test

test: coms.c RS-232/rs232.c
	gcc -o test coms.c RS-232/rs232.c

port:
	ls -lA /dev/serial/by-id

clean:
	rm -rf test
