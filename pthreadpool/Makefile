
CC=g++
CFLAGS=-g -c -Wall

LDFLAGS=-lpthread  
INCLUDE=-I. -I./include
EXECUTABLE=test
SOURCES=src/FCThread.cpp src/FCThreadPool.cpp test.cpp

OBJECTS=$(SOURCES:.cpp=.o)

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) $(INCLUDE)  $< -o $@ 

clean:
	rm -f ./src/*.o
	rm -f *.o
	rm -f $(EXECUTABLE)
	rm -rf $(EXECUTABLE).dSYM
