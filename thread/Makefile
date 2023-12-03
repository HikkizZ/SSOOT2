CXX=g++
CXXFLAGS += $(shell pkg-config --cflags opencv4)
LDFLAGS += $(shell pkg-config --libs opencv4)
CFLAGS=-std=c++11 -pthread
all: main
main: main.cpp
	$(CXX) $(CFLAGS) -o main main.cpp $(CXXFLAGS) $(LDFLAGS)
clean:
	rm -f main

