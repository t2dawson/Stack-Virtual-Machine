/*
 * StackAsm.cpp
 *
 *  Created on: Apr 16, 2017
 *      Author: tdawson
 */

#include <iostream>
#include <fstream>

#include "../Lexer/Lexer.h"

typedef uint32_t ui32;

std::vector<ui32> compileToInstructions(strings lexeme);
bool isInteger(std::string);
bool isPrimitive(std::string);
ui32 mapToHex(std::string);

int main(int argc, char* argv[]) {

	//check for command line argument errors
	if(argc!= 2) {

		std::cout <<"Usage: " << argv[0] << " <filename>" << std::endl;
		exit(1);
	}

	//read the input file
	std::ifstream inputFile;
	inputFile.open(argv[1]);
	if(!inputFile.is_open()) {

		std::cout << "Error: could not open file " << argv[1] << std::endl;
		exit(1);
	}

	std::string line;
	std::string contents;

	while(getline(inputFile,line))  contents+= line + '\n';

	inputFile.close();

	//parse file with Lexer
	Lexer lexer;
	strings lexemes = lexer.lex(contents);

	//compile lexemes to binary instructions
	std::vector<ui32> instructions = compileToInstructions(lexemes);

	//write the instructions to .bin file
	std::ofstream outputFile;
	outputFile.open("output.bin",std::ios::binary);

	for(ui32 i = 0; i < instructions.size(); i++)
		outputFile.write(reinterpret_cast<char*> (&instructions[i]),sizeof(ui32));


	outputFile.close();

	return 0;
}
