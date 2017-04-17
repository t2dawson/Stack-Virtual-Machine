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
bool isInteger(std::string instructionString);
bool isPrimitive(std::string);
ui32 mapToHex(std::string);

int main(int argc, char* argv[]) {

	//check for command line argument errors
	if(argc!= 2) {

		std::cerr <<"Usage: " << argv[0] << " <filename>" << std::endl;
		exit(1);
	}

	//read the input file
	std::ifstream inputFile;
	inputFile.open(argv[1]);
	if(!inputFile.is_open()) {

		std::cerr << "Error: could not open file " << argv[1] << std::endl;
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

std::vector<ui32> compileToInstructions(strings lexeme) {

	std::vector<ui32> instructions;
	for(ui32 i = 0; i < lexeme.size(); i++) {

		if(isInteger(lexeme[i]))
			instructions.push_back(std::stoi(lexeme[i]));
		else {

			ui32 instruction = mapToHex(lexeme[i]);
			if(instruction != -1) instructions.push_back(instruction);
			else {

				std::cerr << "Error: Invalid Instruction " << lexeme[i] << std::endl;
				exit(1);
			}
		}
	}

	return instructions;
}

bool isInteger(std::string instructionString) {

	for(ui32 i = 0; i < instructionString.length(); i++) {

		if(!isdigit(instructionString[i]))
			return false;
	}
	return true;
}

ui32 mapToHex(std::string operand) {
	//TODO: Do comparison and mapping more efficiently
	//TODO: Define operand constants

	if(operand == "+") return 0x40000001;
	else if (operand == "-") return 0x40000002;
	else if (operand == "*") return 0x40000003;
	else if (operand == "/") return 0x40000004;

	return -1; // invalid instruction (until more are added)
}
