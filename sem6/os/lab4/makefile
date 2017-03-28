CC=g++
CFLAGS=-Wall -Wpedantic

LIBS=-lpthread

all: clean both

first:
	$(CC) $(CFLAGS) $(LIBS) -o $@ lab4_1.cpp

second:
	$(CC) $(CFLAGS) $(LIBS) -o $@ lab4_2.cpp

both: first second

clean:
	rm -f first second out
