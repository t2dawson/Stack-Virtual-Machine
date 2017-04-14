CXXFLAGS = -std=c++11 -Wall

all: StackVM

StackVM: VM.o
	
	$(CXX) $(CXXFLAGS) VM.o -o StackVM

VM.o : VM.cpp VM.h

	$(CXX) $(CXXFLAGS) -c VM.cpp

clean:

	rm -f *.o StackVM
