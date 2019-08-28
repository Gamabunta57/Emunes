#include "Cpu.h"

void Cpu::setInstructionSet(std::array<Instruction, 256> &instructionSet)
{
	this->instructionSet = instructionSet;
}
