#include <string>

#include "Cpu.h"
#include "Bus.h"

Cpu::Cpu()
:A(0),X(0),Y(0),PC{0},S{0}, status{0},bus(nullptr), instructionSet{{
		{ "BRK", Implied,  1, 7 }, { "ORA", IndexedX, 2, 6 }, { "???", Absolute, 0, 0 }, { "???", Absolute, 0, 0 }, { "???", Absolute, 0, 0 }, { "ORA", ZeroPage, 2, 3 }, { "ASL", ZeroPage, 2, 5 }, { "???", Absolute, 0, 0 }, { "PHP", Implied, 1, 3 }, { "ORA", Immediate, 2, 2 }, { "ASL", Accumulator,1, 2 }, { "???", Absolute, 0, 0 }, { "???", Absolute, 0, 0 }, { "ORA", Absolute, 3, 4 }, { "ASL", Absolute, 3, 6 }, { "???", Absolute, 0, 0 },
		{ "BPL", Relative, 2, 2 }, { "ORA", IndexedY, 2, 5 }, { "???", Absolute, 0, 0 }, { "???", Absolute, 0, 0 }, { "???", Absolute, 0, 0 }, { "ORA", ZeroPageX,2, 4 }, { "ASL", ZeroPageX,2, 6 }, { "???", Absolute, 0, 0 }, { "CLC", Implied, 1, 2 }, { "ORA", AbsoluteY, 3, 4 }, { "???", Absolute,   0, 0 }, { "???", Absolute, 0, 0 }, { "???", Absolute, 0, 0 }, { "ORA", AbsoluteX,3, 4 }, { "ASL", AbsoluteX,3, 7 }, { "???", Absolute, 0, 0 },
		{ "JSR", Absolute, 3, 6 }, { "AND", IndexedX, 2, 6 }, { "???", Absolute, 0, 0 }, { "???", Absolute, 0, 0 }, { "BIT", ZeroPage, 2, 3 }, { "AND", ZeroPage, 2, 3 }, { "ROL", ZeroPage, 2, 5 }, { "???", Absolute, 0, 0 }, { "PLP", Implied, 1, 4 }, { "AND", Immediate, 2, 2 }, { "ROL", Accumulator,1, 2 }, { "???", Absolute, 0, 0 }, { "BIT", Absolute, 3, 4 }, { "AND", Absolute, 3, 4 }, { "ROL", Absolute, 3, 6 }, { "???", Absolute, 0, 0 },
		{ "BMI", Relative, 2, 2 }, { "AND", IndexedY, 2, 5 }, { "???", Absolute, 0, 0 }, { "???", Absolute, 0, 0 }, { "???", Absolute, 0, 0 }, { "AND", ZeroPageX,2, 4 }, { "ROL", ZeroPageX,2, 6 }, { "???", Absolute, 0, 0 }, { "SEC", Implied, 1, 2 }, { "AND", AbsoluteY, 3, 4 }, { "???", Absolute,	  0, 0 }, { "???", Absolute, 0, 0 }, { "???", Absolute, 0, 0 }, { "AND", AbsoluteX,3, 4 }, { "ROL", AbsoluteX,3, 7 }, { "???", Absolute, 0, 0 },
		{ "RTI", Implied,  1, 6 }, { "EOR", IndexedX, 2, 6 }, { "???", Absolute, 0, 0 }, { "???", Absolute, 0, 0 }, { "???", Absolute, 0, 0 }, { "EOR", ZeroPage, 2, 3 }, { "LSR", ZeroPage ,2, 5 }, { "???", Absolute, 0, 0 }, { "PHA", Implied, 1, 3 }, { "EOR", Immediate, 2, 2 }, { "LSR", Accumulator,1, 2 }, { "???", Absolute, 0, 0 }, { "JMP", Absolute, 3, 3 }, { "EOR", Absolute, 3, 4 }, { "LSR", Absolute, 3, 6 }, { "???", Absolute, 0, 0 },
		{ "BVC", Relative, 2, 2 }, { "EOR", IndexedY, 2, 5 }, { "???", Absolute, 0, 0 }, { "???", Absolute, 0, 0 }, { "???", Absolute, 0, 0 }, { "EOR", ZeroPageX,2, 4 }, { "LSR", ZeroPageX,2, 6 }, { "???", Absolute, 0, 0 }, { "CLI", Implied, 1, 2 }, { "EOR", AbsoluteY, 3, 4 }, { "???", Absolute,   0, 0 }, { "???", Absolute, 0, 0 }, { "???", Absolute, 0, 0 }, { "EOR", AbsoluteX,3, 4 }, { "LSR", AbsoluteX,3, 7 }, { "???", Absolute, 0, 0 },
		{ "RTS", Implied,  1, 6 }, { "ADC", IndexedX, 2, 6 }, { "???", Absolute, 0, 0 }, { "???", Absolute, 0, 0 }, { "???", Absolute, 0, 0 }, { "ADC", ZeroPage, 2, 3 }, { "ROR", ZeroPage, 2, 5 }, { "???", Absolute, 0, 0 }, { "PLA", Implied, 1, 4 }, { "ADC", Immediate, 2, 2 }, { "ROR", Accumulator,1, 2 }, { "???", Absolute, 0, 0 }, { "JMP", Indirect, 3, 5 }, { "ADC", Absolute, 3, 4 }, { "ROR", Absolute, 3, 6 }, { "???", Absolute, 0, 0 },
		{ "BVS", Relative, 2, 2 }, { "ADC", IndexedY, 2, 5 }, { "???", Absolute, 0, 0 }, { "???", Absolute, 0, 0 }, { "???", Absolute, 0, 0 }, { "ADC", ZeroPageX,2, 4 }, { "ROR", ZeroPageX,2, 6 }, { "???", Absolute, 0, 0 }, { "SEI", Implied, 1, 2 }, { "ADC", AbsoluteY, 3, 4 }, { "???", Absolute,   0, 0 }, { "???", Absolute, 0, 0 }, { "???", Absolute, 0, 0 }, { "ADC", AbsoluteX,3, 4 }, { "ROR", AbsoluteX,3, 7 }, { "???", Absolute, 0, 0 },
		{ "???", Absolute, 0, 0 }, { "STA", IndexedX, 2, 6 }, { "???", Absolute, 0, 0 }, { "???", Absolute, 0, 0 }, { "STY", ZeroPage, 2, 3 }, { "STA", ZeroPage, 2, 3 }, { "STX", ZeroPage, 2, 3 }, { "???", Absolute, 0, 0 }, { "DEY", Implied, 1, 2 }, { "???", Absolute,  0, 0 }, { "TXA", Implied,	  1, 2 }, { "???", Absolute, 0, 0 }, { "STY", Absolute, 3, 4 }, { "STA", Absolute, 3, 4 }, { "STX", Absolute, 3, 4 }, { "???", Absolute, 0, 0 },
		{ "BCC", Relative, 2, 2 }, { "STA", IndexedY, 2, 6 }, { "???", Absolute, 0, 0 }, { "???", Absolute, 0, 0 }, { "STY", ZeroPageX,2, 4 }, { "STA", ZeroPageX,2, 4 }, { "STX", ZeroPageY,2, 4 }, { "???", Absolute, 0, 0 }, { "TYA", Implied, 1, 2 }, { "STA", AbsoluteY, 3, 5 }, { "TXS", Implied,	  1, 2 }, { "???", Absolute, 0, 0 }, { "???", Absolute, 0, 0 }, { "STA", AbsoluteX,3, 5 }, { "???", Absolute, 0, 0 }, { "???", Absolute, 0, 0 },
		{ "LDY", Immediate,2, 2 }, { "LDA", IndexedX, 2, 6 }, { "LDX", Immediate,2, 2 }, { "???", Absolute, 0, 0 }, { "LDY", ZeroPage, 2, 3 }, { "LDA", ZeroPage, 2, 3 }, { "LDX", ZeroPage, 2, 3 }, { "???", Absolute, 0, 0 }, { "TAY", Implied, 1, 2 }, { "LDA", Immediate, 2, 2 }, { "TAX", Implied,	  1, 2 }, { "???", Absolute, 0, 0 }, { "LDY", Absolute, 3, 4 }, { "LDA", Absolute, 3, 4 }, { "LDX", Absolute, 3, 4 }, { "???", Absolute, 0, 0 },
		{ "BCS", Relative, 2, 2 }, { "LDA", IndexedY, 2, 5 }, { "???", Absolute, 0, 0 }, { "???", Absolute, 0, 0 }, { "LDY", ZeroPageX,2, 4 }, { "LDA", ZeroPageX,2, 4 }, { "LDX", ZeroPageY,2, 4 }, { "???", Absolute, 0, 0 }, { "CLV", Implied, 1, 2 }, { "LDA", AbsoluteY, 3, 4 }, { "TSX", Implied,	  1, 2 }, { "???", Absolute, 0, 0 }, { "LDY", AbsoluteX,3, 4 }, { "LDA", AbsoluteX,3, 4 }, { "LDX", AbsoluteY,3, 4 }, { "???", Absolute, 0, 0 },
		{ "CPY", Immediate,2, 2 }, { "CMP", IndexedX, 2, 6 }, { "???", Absolute, 0, 0 }, { "???", Absolute, 0, 0 }, { "CPY", ZeroPage, 2, 3 }, { "CMP", ZeroPage, 2, 3 }, { "DEC", ZeroPage, 2, 5 }, { "???", Absolute, 0, 0 }, { "INY", Implied, 1, 2 }, { "CMP", Immediate, 2, 2 }, { "DEX", Implied,	  1, 2 }, { "???", Absolute, 0, 0 }, { "CPY", Absolute, 3, 4 }, { "CMP", Absolute, 3, 4 }, { "DEC", Absolute, 3, 6 }, { "???", Absolute, 0, 0 },
		{ "BNE", Relative, 2, 2 }, { "CMP", IndexedY, 2, 5 }, { "???", Absolute, 0, 0 }, { "???", Absolute, 0, 0 }, { "???", Absolute, 0, 0 }, { "CMP", ZeroPageX,2, 4 }, { "DEC", ZeroPageX,2, 6 }, { "???", Absolute, 0, 0 }, { "CLD", Implied, 1, 2 }, { "CMP", AbsoluteY, 3, 4 }, { "???", Absolute,   0, 0 }, { "???", Absolute, 0, 0 }, { "???", Absolute, 0, 0 }, { "CMP", AbsoluteX,3, 4 }, { "DEC", AbsoluteX,3, 7 }, { "???", Absolute, 0, 0 },
		{ "CPX", Immediate,2, 2 }, { "SBC", IndexedX, 2, 6 }, { "???", Absolute, 0, 0 }, { "???", Absolute, 0, 0 }, { "CPX", ZeroPage, 2, 3 }, { "SBC", ZeroPage, 2, 3 }, { "INC", ZeroPage, 2, 5 }, { "???", Absolute, 0, 0 }, { "INX", Implied, 1, 2 }, { "SBC", Immediate, 2, 2 }, { "NOP", Implied,	  1, 2 }, { "???", Absolute, 0, 0 }, { "CPX", Absolute, 3, 4 }, { "SBC", Absolute, 3, 4 }, { "INC", Absolute, 3, 6 }, { "???", Absolute, 0, 0 },
		{ "BEQ", Relative, 2, 2 }, { "SBC", IndexedY, 2, 5 }, { "???", Absolute, 0, 0 }, { "???", Absolute, 0, 0 }, { "???", Absolute, 0, 0 }, { "SBC", ZeroPageX,2, 4 }, { "INC", ZeroPageX,2, 6 }, { "???", Absolute, 0, 0 }, { "SED", Implied, 1, 2 }, { "SBC", AbsoluteY, 3, 4 }, { "???", Absolute,   0, 0 }, { "???", Absolute, 0, 0 }, { "???", Absolute, 0, 0 }, { "SBC", AbsoluteX,3, 4 }, { "INC", AbsoluteX,3, 7 }, { "???", Absolute, 0, 0 }
      }}
{}

Cpu::~Cpu() = default;


Instruction Cpu::getInstruction(const uint16_t address) {
	return this->instructionSet[address];
}

void Cpu::fetchInstructionBytes(const Instruction &instruction, const uint16_t &address, uint8_t* byteFetched) {
	byteFetched[0] = this->bus->Read(address);
	int memorySize = instruction.memoryRequirement;

	if (memorySize > 1)
        byteFetched[1] = this->bus->Read(address+1);

	if (memorySize > 2)
        byteFetched[2] = this->bus->Read(address+2);
}

void Cpu::attachBus(Bus* bus){
    this->bus = bus;
}

void Cpu::reset() {
	PC.PCL = this->bus->Read(RESET_VECTOR_ADDR);
	PC.PCH = this->bus->Read(RESET_VECTOR_ADDR + 1);
}

void Cpu::run1Instruction() {
	Instruction instruction = this->getInstruction(PC.address);
	uint8_t instructionBytes[3];
	this->fetchInstructionBytes(instruction, PC.address, instructionBytes);
	uint16_t argument = this->fetchArgument(instruction.addressingMode, instructionBytes);
}

uint16_t Cpu::fetchArgument(const AddressingMode mode, const uint8_t* instructionBytes){
    Address addr{0};
    switch (mode){
        case Implied:
        case Accumulator:
        case Immediate:
            return 0;
        case Absolute:{
            addr.LL.value = instructionBytes[1];
            addr.HH.value = instructionBytes[2];
            return addr.full;
        }
        case ZeroPage:{
            addr.LL.value = instructionBytes[1];
            return this->bus->Read(addr.full);
        }
        case ZeroPageX:{
            addr.LL.value = instructionBytes[1] + this->X;
            addr.HH.value = 0;
            return this->bus->Read(addr.full);
        }
        case ZeroPageY:{
            addr.LL.value = instructionBytes[1] + this->Y;
            addr.HH.value = 0;
            return this->bus->Read(addr.full);
        }
        case AbsoluteX:{
            addr.HH.value = instructionBytes[2];
            addr.LL.value = instructionBytes[1];
            addr.full +=  this->X + this->status.C;
            return this->bus->Read(addr.full);
        }
        case AbsoluteY:{
            addr.HH.value = instructionBytes[2];
            addr.LL.value = instructionBytes[1];
            addr.full +=  this->Y + this->status.C;
            return this->bus->Read(addr.full);
        }
        case Relative:{
            addr.LL.value = instructionBytes[1];
            return this->PC.address + addr.LL.signedValue;
        }
        case Indirect:{
            Address indirect{0};
            indirect.LL.value = instructionBytes[1];
            indirect.HH.value = instructionBytes[2];

            addr.LL.value = this->bus->Read(indirect.full);
            addr.HH.value = this->bus->Read(indirect.full + 1);

            return this->bus->Read(addr.full);
        }
        case IndexedX:{
            Address indirect{0};
            indirect.LL.value = instructionBytes[1] + this->X;
            indirect.HH.value = 0;

            addr.LL.value = this->bus->Read(indirect.full);
            addr.HH.value = this->bus->Read(indirect.full + 1);

            return this->bus->Read(addr.full);
        }
        case IndexedY:{
            Address indirect{0};
            indirect.LL.value = instructionBytes[1];
            indirect.HH.value = 0;

            addr.LL.value = this->bus->Read(indirect.full);
            addr.HH.value = this->bus->Read(indirect.full + 1);

            return this->bus->Read(addr.full + this->Y + this->status.C);
        }
    }
}