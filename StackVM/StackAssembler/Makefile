CXXFLAGS = -std=c++11 -Wall

StackAsm: StackAsm.o Lexer.o
	$(CXX) $(CXXFLAGS) StackAsm.o Lexer.o -o $@
	
Lexer.o : Lexer.h Lexer.cpp
	$(CXX) $(CXXFLAGS) -c Lexer.cpp
	
StackAsm.o : Lexer.h StackAsm.cpp 
	$(CXX) $(CXXFLAGS) -c StackAsm.cpp

clean:
	rm -f *.o StackAsm *.bin
