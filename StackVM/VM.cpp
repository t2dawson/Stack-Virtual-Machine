/*
 * VM.cpp
 *
 *  Created on: Apr 14, 2017
 *      Author: tdawson
 *
 */

/*
 *
 * Instruction format:
 *
 * Header: 2 bits
 * Data : 30 bits
 *
 * Header Format:
 *
 * 0b00 => positive integer
 * 0b01 => primitve instruction
 * 0b10 => negative integer
 * 0b11 =? Undefined: no implentation for this yet
 *
 */

#include "VM.h"


VM::VM() {
	stack.reserve(1000000); // change in future
}

i32 VM::getCodeType(i32 instruction) {

	i32 type = 0xc0000000;
	type = (type & instruction) >> 30;
	return type;
}

i32 VM::getData(i32 instruction) {

	i32 data = 0x3fffffff;
	data = data & instruction;
	return data;
}

void VM::fetch(){
	pc++;
}

void VM::decode() {

	codeType = getCodeType(stack[pc]);
	data = getData(stack[pc]);
}

void VM::executeProgram() {
	if(codeType == 0 || codeType == 2) {
		sp++;
		stack[sp] = data;
	}

	else
		executePrimitive();
}

void VM::executePrimitive() {

	switch(data) {

	case 0: { // the halt instruction

		std::cout << "Halting Program" << endl;
		running = false;
		break;
	}

	case 1: { //  add instruction

		std::cout << "add " << stack[sp-1] << " and" << stack[sp] << endl;

		stack[sp - 1] += stack[sp];
		sp--;
		break;
	 }
  }

}

void VM::run() {

	pc -= 1;
	while(running) {
		fetch();
		decode();
		executeProgram();
	}
}

void VM::loadProgram(std::vector<i32> program) {

	for (i32 i = 0; i < program.size(); i++) {

		// start at program counter
		stack[pc+i] = program[i];
	}
}
