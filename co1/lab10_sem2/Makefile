CC=g++
CFLAGS=-c --std=c++1y -Wall
LDFLAGS=--std=c++1y
SOURCES=./main.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=foo

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o
