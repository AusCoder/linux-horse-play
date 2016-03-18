CC = gcc
CFLAGS = -Wall -g
LDFAGS = -g

launchx: 

launchx.o:

.PHONY: clean all valgrind
clean:
	rm -f *.o launchx

all: clean launchx

valgrind: launchx
	valgrind --leak-check=full ./launchx
