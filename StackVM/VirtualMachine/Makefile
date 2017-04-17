CXXFLAGS = -std=c++11 -Wall

all: StackVM

StackVM: VM.o Main.o
	
	$(CXX) $(CXXFLAGS) VM.o Main.o -o StackVM

Main.o : Main.cpp
	
	$(CXX) $(CXXFLAGS) -c Main.cpp
	

VM.o : VM.cpp VM.h

	$(CXX) $(CXXFLAGS) -c VM.cpp

clean:

	rm -f *.o StackVM
