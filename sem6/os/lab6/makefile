CC=g++
CFLAGS=-Wall -Wpedantic

LIBS=-lpthread -lrt
LAB=lab6

all: clean both

first:
	$(CC) $(CFLAGS) $(LIBS) -o $@ $(LAB)_1.cpp

second:
	$(CC) $(CFLAGS) $(LIBS) -o $@ $(LAB)_2.cpp

both: first second

clean:
	rm -f first second fifo
