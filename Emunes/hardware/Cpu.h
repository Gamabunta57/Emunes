#pragma once
#include <cstdint>
#include <array>
#include <string>

#include "types/ProgramCounter.h";
#include "types/StackPointer.h";
#include "types/Instruction.h";
#include "types/AddressingMode.h";

#include "Bus.h"

union StateFlags
{
	uint8_t state;
	uint8_t C : 1; // Carry : 1 = true
	uint8_t Z : 2; // Zero : 1 = Result is Zero
	uint8_t I : 3; // IRQ Disable : 1 = Disable
	uint8_t D : 4; // Decimal mode : 1 = true
	uint8_t B : 5; // Break
	uint8_t _ : 6; // ???
	uint8_t V : 7; // Overflow : 1 = true
	uint8_t N : 8; // Negative : 1 = negative
};

class Cpu{

public:
	const uint16_t RESET_VECTOR_ADDR = 0xFFFC;

public:
	uint8_t A;
	uint8_t Y;
	uint8_t X;
	ProgramCounter PC;
	StackPointer S;
	StateFlags status;

	std::array<Instruction, 256> instructionSet;
	Bus* bus;

public:
	Cpu();
	~Cpu();

	void attachBus(Bus* bus);
	Instruction getInstruction(const uint16_t &address);
	void fetchInstructionBytes(const Instruction &instruction, const uint16_t &address, uint8_t* byteFetched);
	void reset();
	void run1Instruction();
    uint16_t fetchArgument(const AddressingMode &mode, const uint8_t *instructionBytes);
};