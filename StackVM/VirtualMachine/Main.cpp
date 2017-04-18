#include "VM.h"
#include <fstream>

int main(int argc, char** argv) {

	//check for command line errors
	if(argc != 2) {

		std::cerr << "Usage: " << argv[0] << " <binary-file-path>" << std::endl;
		exit(1);
	}

	std::ifstream instructionReader(argv[1], 	 		std::ios::binary);

	std::vector<i32> program;
	i32 instruction;

	while(instructionReader.read((char*) &instruction, 			sizeof(instruction))) 
	program.push_back(instruction);


	VM stackMachine;
	stackMachine.loadProgram(program);
	stackMachine.run();

	return 0;
}
