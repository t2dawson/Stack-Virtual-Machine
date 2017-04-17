#include "VM.h"

int main() {

	VM stackMachine;
	std::vector<i32> program{3,4,0x40000001,5, 0x40000002, 3 ,0x40000000 };

	stackMachine.loadProgram(program);
	stackMachine.run();

	return 0;
}
