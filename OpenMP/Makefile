CXX = g++
CXXFLAGS = -std=c++11 -Wall -fopenmp `pkg-config --cflags opencv4`
LIBS = `pkg-config --libs opencv4`

all: openmp

openmp: openmp_main.cpp
	$(CXX) $(CXXFLAGS) -o $@ $< $(LIBS)

clean:
	rm -f openmp
