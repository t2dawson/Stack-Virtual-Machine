/*
 * VM.h
 *
 *  Created on: Apr 14, 2017
 *      Author: tdawson
 */

#ifndef VM_H_
#define VM_H_

#include <vector>
#include <iostream>
#define endl "\n"

typedef int32_t i32;


class VM {

	i32 pc = 100; // random value change later
	i32 sp = 0;
	std::vector<i32> stack;
	i32 data = 0;
	i32 codeType = 0; // the type of byte code: Instruction/Number
	bool running = true;

	i32 getCodeType(i32 instruction);
	i32 getData(i32 instruction);
	void cpu();
	void fetch();
	void decode();
	void executeProgram();
	void executePrimitive();

public:
	VM();
	void run();
	void loadProgram(std::vector<i32> program);;
	virtual ~VM();
};

#endif /* VM_H_ */
