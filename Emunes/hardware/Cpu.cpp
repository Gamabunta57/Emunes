#include <ios>
#include <iomanip>
#include <iostream>
#include "Cpu.h"

Cpu::Cpu()
:A(0),X(0),Y(0),PC{0},S{STACK_POINTER_INITIAL_VALUE}, status(0x20),bus(nullptr),_pcHasChanged(false), instructionSet{{
		{ "BRK", Implied,  1, 7, &Cpu::BRK },	{ "ORA", IndexedX, 2, 6, &Cpu::ORA },	{ "???", Absolute, 0, 0, &Cpu::XXX },	{ "???", Absolute, 0, 0, &Cpu::XXX },	{ "???", Absolute, 0, 0, &Cpu::XXX },	{ "ORA", ZeroPage, 2, 3, &Cpu::ORA },	{ "ASL", ZeroPage, 2, 5, &Cpu::ASL },	{ "???", Absolute, 0, 0, &Cpu::XXX },	{ "PHP", Implied, 1, 3, &Cpu::PHP },	{ "ORA", Immediate, 2, 2, &Cpu::ORA },	{ "ASL", Accumulator, 1, 2, &Cpu::ASL },	{ "???", Absolute, 0, 0, &Cpu::XXX },	{ "???", Absolute, 0, 0, &Cpu::XXX },	{ "ORA", Absolute, 3, 4, &Cpu::ORA },	{ "ASL", Absolute, 3, 6, &Cpu::ASL },	{ "???", Absolute, 0, 0, &Cpu::XXX },
		{ "BPL", Relative, 2, 2, &Cpu::BPL },	{ "ORA", IndexedY, 2, 5, &Cpu::ORA },	{ "???", Absolute, 0, 0, &Cpu::XXX },	{ "???", Absolute, 0, 0, &Cpu::XXX },	{ "???", Absolute, 0, 0, &Cpu::XXX },	{ "ORA", ZeroPageX, 2, 4, &Cpu::ORA },	{ "ASL", ZeroPageX, 2, 6, &Cpu::ASL },	{ "???", Absolute, 0, 0, &Cpu::XXX },	{ "CLC", Implied, 1, 2, &Cpu::CLC },	{ "ORA", AbsoluteY, 3, 4, &Cpu::ORA },	{ "???", Absolute, 0, 0, &Cpu::XXX },	{ "???", Absolute, 0, 0, &Cpu::XXX },	{ "???", Absolute, 0, 0, &Cpu::XXX },	{ "ORA", AbsoluteX, 3, 4, &Cpu::ORA },	{ "ASL", AbsoluteX, 3, 7, &Cpu::ASL },	{ "???", Absolute, 0, 0, &Cpu::XXX },
		{ "JSR", Absolute, 3, 6, &Cpu::JSR },	{ "AND", IndexedX, 2, 6, &Cpu::AND },	{ "???", Absolute, 0, 0, &Cpu::XXX },	{ "???", Absolute, 0, 0, &Cpu::XXX },	{ "BIT", ZeroPage, 2, 3, &Cpu::BIT },	{ "AND", ZeroPage, 2, 3, &Cpu::AND },	{ "ROL", ZeroPage, 2, 5, &Cpu::ROL },	{ "???", Absolute, 0, 0, &Cpu::XXX },	{ "PLP", Implied, 1, 4, &Cpu::PLP },	{ "AND", Immediate, 2, 2, &Cpu::AND },	{ "ROL", Accumulator, 1, 2, &Cpu::ROL },	{ "???", Absolute, 0, 0, &Cpu::XXX },	{ "BIT", Absolute, 3, 4, &Cpu::BIT },	{ "AND", Absolute, 3, 4, &Cpu::AND },	{ "ROL", Absolute, 3, 6, &Cpu::ROL },	{ "???", Absolute, 0, 0, &Cpu::XXX },
		{ "BMI", Relative, 2, 2, &Cpu::BMI },	{ "AND", IndexedY, 2, 5, &Cpu::AND },	{ "???", Absolute, 0, 0, &Cpu::XXX },	{ "???", Absolute, 0, 0, &Cpu::XXX },	{ "???", Absolute, 0, 0, &Cpu::XXX },	{ "AND", ZeroPageX, 2, 4, &Cpu::AND },	{ "ROL", ZeroPageX, 2, 6, &Cpu::ROL },	{ "???", Absolute, 0, 0, &Cpu::XXX },	{ "SEC", Implied, 1, 2, &Cpu::SEC },	{ "AND", AbsoluteY, 3, 4, &Cpu::AND },	{ "???", Absolute, 0, 0, &Cpu::XXX },	{ "???", Absolute, 0, 0, &Cpu::XXX },	{ "???", Absolute, 0, 0, &Cpu::XXX },	{ "AND", AbsoluteX, 3, 4, &Cpu::AND },	{ "ROL", AbsoluteX, 3, 7, &Cpu::ROL },	{ "???", Absolute, 0, 0, &Cpu::XXX },
		{ "RTI", Implied,  1, 6, &Cpu::RTI },	{ "EOR", IndexedX, 2, 6, &Cpu::EOR },	{ "???", Absolute, 0, 0, &Cpu::XXX },	{ "???", Absolute, 0, 0, &Cpu::XXX },	{ "???", Absolute, 0, 0, &Cpu::XXX },	{ "EOR", ZeroPage, 2, 3, &Cpu::EOR },	{ "LSR", ZeroPage, 2, 5, &Cpu::LSR },	{ "???", Absolute, 0, 0, &Cpu::XXX },	{ "PHA", Implied, 1, 3, &Cpu::PHA },	{ "EOR", Immediate, 2, 2, &Cpu::EOR },	{ "LSR", Accumulator, 1, 2, &Cpu::LSR },	{ "???", Absolute, 0, 0, &Cpu::XXX },	{ "JMP", Absolute, 3, 3, &Cpu::JMP },	{ "EOR", Absolute, 3, 4, &Cpu::EOR },	{ "LSR", Absolute, 3, 6, &Cpu::LSR },	{ "???", Absolute, 0, 0, &Cpu::XXX },
		{ "BVC", Relative, 2, 2, &Cpu::BVC },	{ "EOR", IndexedY, 2, 5, &Cpu::EOR },	{ "???", Absolute, 0, 0, &Cpu::XXX },	{ "???", Absolute, 0, 0, &Cpu::XXX },	{ "???", Absolute, 0, 0, &Cpu::XXX },	{ "EOR", ZeroPageX, 2, 4, &Cpu::EOR },	{ "LSR", ZeroPageX, 2, 6, &Cpu::LSR },	{ "???", Absolute, 0, 0, &Cpu::XXX },	{ "CLI", Implied, 1, 2, &Cpu::CLI },	{ "EOR", AbsoluteY, 3, 4, &Cpu::EOR },	{ "???", Absolute, 0, 0, &Cpu::XXX },	{ "???", Absolute, 0, 0, &Cpu::XXX },	{ "???", Absolute, 0, 0, &Cpu::XXX },	{ "EOR", AbsoluteX, 3, 4, &Cpu::EOR },	{ "LSR", AbsoluteX, 3, 7, &Cpu::LSR },	{ "???", Absolute, 0, 0, &Cpu::XXX },
		{ "RTS", Implied,  1, 6, &Cpu::RTS },	{ "ADC", IndexedX, 2, 6, &Cpu::ADC },	{ "???", Absolute, 0, 0, &Cpu::XXX },	{ "???", Absolute, 0, 0, &Cpu::XXX },	{ "???", Absolute, 0, 0, &Cpu::XXX },	{ "ADC", ZeroPage, 2, 3, &Cpu::ADC },	{ "ROR", ZeroPage, 2, 5, &Cpu::ROR },	{ "???", Absolute, 0, 0, &Cpu::XXX },	{ "PLA", Implied, 1, 4, &Cpu::PLA },	{ "ADC", Immediate, 2, 2, &Cpu::ADC },	{ "ROR", Accumulator, 1, 2, &Cpu::ROR },	{ "???", Absolute, 0, 0, &Cpu::XXX },	{ "JMP", Indirect, 3, 5, &Cpu::JMP },	{ "ADC", Absolute, 3, 4, &Cpu::ADC },	{ "ROR", Absolute, 3, 6, &Cpu::ROR },	{ "???", Absolute, 0, 0, &Cpu::XXX },
		{ "BVS", Relative, 2, 2, &Cpu::BVS },	{ "ADC", IndexedY, 2, 5, &Cpu::ADC },	{ "???", Absolute, 0, 0, &Cpu::XXX },	{ "???", Absolute, 0, 0, &Cpu::XXX },	{ "???", Absolute, 0, 0, &Cpu::XXX },	{ "ADC", ZeroPageX, 2, 4, &Cpu::ADC },	{ "ROR", ZeroPageX, 2, 6, &Cpu::ROR },	{ "???", Absolute, 0, 0, &Cpu::XXX },	{ "SEI", Implied, 1, 2, &Cpu::SEI },	{ "ADC", AbsoluteY, 3, 4, &Cpu::ADC },	{ "???", Absolute, 0, 0, &Cpu::XXX },	{ "???", Absolute, 0, 0, &Cpu::XXX },	{ "???", Absolute, 0, 0, &Cpu::XXX },	{ "ADC", AbsoluteX, 3, 4, &Cpu::ADC },	{ "ROR", AbsoluteX, 3, 7, &Cpu::ROR },	{ "???", Absolute, 0, 0, &Cpu::XXX },
		{ "???", Absolute, 0, 0, &Cpu::XXX },	{ "STA", IndexedX, 2, 6, &Cpu::STA },	{ "???", Absolute, 0, 0, &Cpu::XXX },	{ "???", Absolute, 0, 0, &Cpu::XXX },	{ "STY", ZeroPage, 2, 3, &Cpu::STY },	{ "STA", ZeroPage, 2, 3, &Cpu::STA },	{ "STX", ZeroPage, 2, 3, &Cpu::STX },	{ "???", Absolute, 0, 0, &Cpu::XXX },	{ "DEY", Implied, 1, 2, &Cpu::DEY },	{ "???", Absolute, 0, 0, &Cpu::XXX },	{ "TXA", Implied, 1, 2, &Cpu::TXA },	{ "???", Absolute, 0, 0, &Cpu::XXX },	{ "STY", Absolute, 3, 4, &Cpu::STY },	{ "STA", Absolute, 3, 4, &Cpu::STA },	{ "STX", Absolute, 3, 4, &Cpu::STX },	{ "???", Absolute, 0, 0, &Cpu::XXX },
		{ "BCC", Relative, 2, 2, &Cpu::BCC },	{ "STA", IndexedY, 2, 6, &Cpu::STA },	{ "???", Absolute, 0, 0, &Cpu::XXX },	{ "???", Absolute, 0, 0, &Cpu::XXX },	{ "STY", ZeroPageX, 2, 4, &Cpu::STY },	{ "STA", ZeroPageX, 2, 4, &Cpu::STA },	{ "STX", ZeroPageY, 2, 4, &Cpu::STX },	{ "???", Absolute, 0, 0, &Cpu::XXX },	{ "TYA", Implied, 1, 2, &Cpu::TYA },	{ "STA", AbsoluteY, 3, 5, &Cpu::STA },	{ "TXS", Implied, 1, 2, &Cpu::TXS },	{ "???", Absolute, 0, 0, &Cpu::XXX },	{ "???", Absolute, 0, 0, &Cpu::XXX },	{ "STA", AbsoluteX, 3, 5, &Cpu::STA },	{ "???", Absolute, 0, 0, &Cpu::XXX },	{ "???", Absolute, 0, 0, &Cpu::XXX },
		{ "LDY", Immediate,2, 2, &Cpu::LDY },	{ "LDA", IndexedX, 2, 6, &Cpu::LDA },	{ "LDX", Immediate,2, 2, &Cpu::LDX },	{ "???", Absolute, 0, 0, &Cpu::XXX },	{ "LDY", ZeroPage, 2, 3, &Cpu::LDY },	{ "LDA", ZeroPage, 2, 3, &Cpu::LDA },	{ "LDX", ZeroPage, 2, 3, &Cpu::LDX },	{ "???", Absolute, 0, 0, &Cpu::XXX },	{ "TAY", Implied, 1, 2, &Cpu::TAY },	{ "LDA", Immediate, 2, 2, &Cpu::LDA },	{ "TAX", Implied, 1, 2, &Cpu::TAX },	{ "???", Absolute, 0, 0, &Cpu::XXX },	{ "LDY", Absolute, 3, 4, &Cpu::LDY },	{ "LDA", Absolute, 3, 4, &Cpu::LDA },	{ "LDX", Absolute, 3, 4, &Cpu::LDX },	{ "???", Absolute, 0, 0, &Cpu::XXX },
		{ "BCS", Relative, 2, 2, &Cpu::BCS },	{ "LDA", IndexedY, 2, 5, &Cpu::LDA },	{ "???", Absolute, 0, 0, &Cpu::XXX },	{ "???", Absolute, 0, 0, &Cpu::XXX },	{ "LDY", ZeroPageX, 2, 4, &Cpu::LDY },	{ "LDA", ZeroPageX, 2, 4, &Cpu::LDA },	{ "LDX", ZeroPageY, 2, 4, &Cpu::LDX },	{ "???", Absolute, 0, 0, &Cpu::XXX },	{ "CLV", Implied, 1, 2, &Cpu::CLV },	{ "LDA", AbsoluteY, 3, 4, &Cpu::LDA },	{ "TSX", Implied, 1, 2, &Cpu::TSX },	{ "???", Absolute, 0, 0, &Cpu::XXX },	{ "LDY", AbsoluteX, 3, 4, &Cpu::LDY },	{ "LDA", AbsoluteX, 3, 4, &Cpu::LDA },	{ "LDX", AbsoluteY, 3, 4, &Cpu::LDX },	{ "???", Absolute, 0, 0, &Cpu::XXX },
		{ "CPY", Immediate,2, 2, &Cpu::CPY },	{ "CMP", IndexedX, 2, 6, &Cpu::CMP },	{ "???", Absolute, 0, 0, &Cpu::XXX },	{ "???", Absolute, 0, 0, &Cpu::XXX },	{ "CPY", ZeroPage, 2, 3, &Cpu::CPY },	{ "CMP", ZeroPage, 2, 3, &Cpu::CMP },	{ "DEC", ZeroPage, 2, 5, &Cpu::DEC },	{ "???", Absolute, 0, 0, &Cpu::XXX },	{ "INY", Implied, 1, 2, &Cpu::INY },	{ "CMP", Immediate, 2, 2, &Cpu::CMP },	{ "DEX", Implied, 1, 2, &Cpu::DEX },	{ "???", Absolute, 0, 0, &Cpu::XXX },	{ "CPY", Absolute, 3, 4, &Cpu::CPY },	{ "CMP", Absolute, 3, 4, &Cpu::CMP },	{ "DEC", Absolute, 3, 6, &Cpu::DEC },	{ "???", Absolute, 0, 0, &Cpu::XXX },
		{ "BNE", Relative, 2, 2, &Cpu::BNE },	{ "CMP", IndexedY, 2, 5, &Cpu::CMP },	{ "???", Absolute, 0, 0, &Cpu::XXX },	{ "???", Absolute, 0, 0, &Cpu::XXX },	{ "???", Absolute, 0, 0, &Cpu::XXX },	{ "CMP", ZeroPageX, 2, 4, &Cpu::CMP },	{ "DEC", ZeroPageX, 2, 6, &Cpu::DEC },	{ "???", Absolute, 0, 0, &Cpu::XXX },	{ "CLD", Implied, 1, 2, &Cpu::CLD },	{ "CMP", AbsoluteY, 3, 4, &Cpu::CMP },	{ "???", Absolute, 0, 0, &Cpu::XXX },	{ "???", Absolute, 0, 0, &Cpu::XXX },	{ "???", Absolute, 0, 0, &Cpu::XXX },	{ "CMP", AbsoluteX, 3, 4, &Cpu::CMP },	{ "DEC", AbsoluteX, 3, 7, &Cpu::DEC },	{ "???", Absolute, 0, 0, &Cpu::XXX },
		{ "CPX", Immediate,2, 2, &Cpu::CPX },	{ "SBC", IndexedX, 2, 6, &Cpu::SBC },	{ "???", Absolute, 0, 0, &Cpu::XXX },	{ "???", Absolute, 0, 0, &Cpu::XXX },	{ "CPX", ZeroPage, 2, 3, &Cpu::CPX },	{ "SBC", ZeroPage, 2, 3, &Cpu::SBC },	{ "INC", ZeroPage, 2, 5, &Cpu::INC },	{ "???", Absolute, 0, 0, &Cpu::XXX },	{ "INX", Implied, 1, 2, &Cpu::INX },	{ "SBC", Immediate, 2, 2, &Cpu::SBC },	{ "NOP", Implied, 1, 2, &Cpu::NOP },	{ "???", Absolute, 0, 0, &Cpu::XXX },	{ "CPX", Absolute, 3, 4, &Cpu::CPX },	{ "SBC", Absolute, 3, 4, &Cpu::SBC },	{ "INC", Absolute, 3, 6, &Cpu::INC },	{ "???", Absolute, 0, 0, &Cpu::XXX },
		{ "BEQ", Relative, 2, 2, &Cpu::BEQ },	{ "SBC", IndexedY, 2, 5, &Cpu::SBC },	{ "???", Absolute, 0, 0, &Cpu::XXX },	{ "???", Absolute, 0, 0, &Cpu::XXX },	{ "???", Absolute, 0, 0, &Cpu::XXX },	{ "SBC", ZeroPageX, 2, 4, &Cpu::SBC },	{ "INC", ZeroPageX, 2, 6, &Cpu::INC },	{ "???", Absolute, 0, 0, &Cpu::XXX },	{ "SED", Implied, 1, 2, &Cpu::SED },	{ "SBC", AbsoluteY, 3, 4, &Cpu::SBC },	{ "???", Absolute, 0, 0, &Cpu::XXX },	{ "???", Absolute, 0, 0, &Cpu::XXX },	{ "???", Absolute, 0, 0, &Cpu::XXX },	{ "SBC", AbsoluteX, 3, 4, &Cpu::SBC },	{ "INC", AbsoluteX, 3, 7, &Cpu::INC },	{ "???", Absolute, 0, 0, &Cpu::XXX }
      }}
{}

Cpu::~Cpu() = default;


Cpu::Instruction Cpu::getInstruction(uint16_t const address) const {
	return instructionSet[address];
}

void Cpu::fetchInstructionBytes(const Instruction &instruction, uint16_t const address, uint8_t* byteFetched) const {
	byteFetched[0] = bus->Read(address);
	int memorySize = instruction.memoryRequirement;

	if (memorySize > 1)
        byteFetched[1] = bus->Read(address+1);

	if (memorySize > 2)
        byteFetched[2] = bus->Read(address+2);
}

void Cpu::attachBus(Bus* const busToAttach){
    this->bus = busToAttach;
}

void Cpu::reset() {
	_pcHasChanged = false;
    PC.LL = bus->Read(RESET_VECTOR_ADDR);
	PC.HH = bus->Read(RESET_VECTOR_ADDR + 1);
	status = INITIAL_PROCESSOR_STATUS;
	S = (uint8_t)STACK_POINTER_INITIAL_VALUE;
	A = 0;
	X = 0;
	Y = 0;
	std::cout << std::setfill('0') << std::setw(4) << std::hex << PC.address() << std::endl;
}

void Cpu::run1Instruction() {
	_pcHasChanged = false;

	Instruction instruction = getInstruction(bus->Read(PC.address()));

	uint8_t instructionBytes[3];
	fetchInstructionBytes(instruction, PC.address(), instructionBytes);

    MnemonicArgument argument = fetchArgument(instruction.addressingMode, instructionBytes);

    (this->*instruction.mnemonicCall)(argument);
	if(!_pcHasChanged)
		PC += instruction.memoryRequirement;
}

MnemonicArgument Cpu::fetchArgument(AddressingMode const mode, const uint8_t* const instructionBytes) const{
    MemoryAddress addr{0};
    MnemonicArgument fetchedArgument{0x0000,0x00,0};
    switch (mode){
        case Accumulator:{
            fetchedArgument.isAcu = true;
            return fetchedArgument;
        }
        case Immediate:{
            fetchedArgument.readValue.value = instructionBytes[1];
            return fetchedArgument;
        }
        case Absolute:{
            addr.LL = instructionBytes[1];
            addr.HH = instructionBytes[2];
            break;
        }
        case ZeroPage:{
            addr.LL = instructionBytes[1];
            break;
        }
        case ZeroPageX:{
            addr.LL = instructionBytes[1] + X;
            addr.HH = 0;
            break;
        }
        case ZeroPageY:{
            addr.LL = instructionBytes[1] + Y;
            addr.HH = 0;
            break;
        }
        case AbsoluteX:{
            addr.HH = instructionBytes[2];
            addr.LL = instructionBytes[1];
            addr +=  X + status.C;
            break;
        }
        case AbsoluteY:{
            addr.HH = instructionBytes[2];
            addr.LL = instructionBytes[1];
            addr +=  Y + status.C;
            break;
        }
        case Relative:{
            byte byte{instructionBytes[1]};
            addr = (uint16_t)(PC.address() + byte.signedValue + 2);
            break;
        }
        case Indirect:{
            MemoryAddress indirect{instructionBytes[1], instructionBytes[2]};

			uint16_t address = indirect.address();

            addr.LL = bus->Read(address);
            addr.HH = bus->Read(address + 1);

            break;
        }
        case IndexedX:{
            MemoryAddress indirect{0};
            indirect.LL = instructionBytes[1] + X;
            indirect.HH = 0;

			uint16_t address = indirect.address();

            addr.LL = bus->Read(address);
            addr.HH = bus->Read(address + 1);

            break;
        }
        case IndexedY:{
            MemoryAddress indirect{0};
            indirect.LL = instructionBytes[1];
            indirect.HH = 0;

			uint16_t address = indirect.address();

			addr.LL = bus->Read(address);
			addr.HH = bus->Read(address + 1);

            addr += Y + status.C;
            break;
        }
        default:
            break;
    }
    fetchedArgument.targetAddress = addr;
    fetchedArgument.readValue.value = bus->Read(addr.address());
    return fetchedArgument;
}

void Cpu::pushOnStack(uint8_t const value) {
    bus->Write(S.address(), value);
    S--;
}

uint8_t Cpu::pullFromStack() {
    S++;
    return bus->Read(S.address());
}

void Cpu::ADC(MnemonicArgument const arg) {
	uint8_t oldA = A;

	uint16_t newValue = arg.readValue.value + A + status.C;

	status.C = newValue > 0x00FF;
	status.V = (~(oldA ^ arg.readValue.value) & (oldA ^ (uint8_t)newValue)) & 0x0080u;

	A = newValue & 0x00FFu;

	status.Z = A == 0;
	status.N = A & 0x80u;
}

void Cpu::AND(MnemonicArgument const arg) {
    A &= arg.readValue.value;

	status.Z = A == 0;
	status.N = A & 0x80u;
}

void Cpu::ASL(MnemonicArgument const arg) {
	uint8_t value = arg.isAcu ? A : arg.readValue.value;
	status.C = value & 0x80u;
	value <<= 1u;
	status.Z = value == 0;
	status.N = value & 0x8u;

	if (arg.isAcu)
		A = value;
	else
		bus->Write(arg.targetAddress.address(), value);
}

void Cpu::BCC(MnemonicArgument const arg) {
	if (status.C)
		return;

    PC = arg.targetAddress.address();
	_pcHasChanged = true;
}

void Cpu::BCS(MnemonicArgument const arg) {
	if (!status.C)
		return;
    PC = arg.targetAddress.address();
	_pcHasChanged = true;
}

void Cpu::BEQ(MnemonicArgument const arg) {
	if (!status.Z)
		return;

    PC = arg.targetAddress.address();
	_pcHasChanged = true;
}

void Cpu::BIT(MnemonicArgument const arg) {
    status.V = (arg.readValue.value & 0x40u);
    status.N = (arg.readValue.value & 0x80u);
    status.Z = (A & arg.readValue.value);
}

void Cpu::BMI(MnemonicArgument const arg) {
	if (!status.N)
		return;
    PC = arg.targetAddress.address();
	_pcHasChanged = true;
}

void Cpu::BNE(MnemonicArgument const arg) {
	if (status.Z)
		return;

    PC = arg.targetAddress.address();
	_pcHasChanged = true;
}

void Cpu::BPL(MnemonicArgument const arg) {
	if (status.N)
		return;

    PC = arg.targetAddress.address();
	_pcHasChanged = true;
}

void Cpu::BRK(MnemonicArgument const) { //TODO : check why there's a PC + 2
    //interrupt
    status.I = true;
	MemoryAddress nextAddress{0};
	nextAddress = (uint16_t)(PC.address() + 2); 
    pushOnStack(nextAddress.LL);
    pushOnStack(nextAddress.HH);
    pushOnStack(status.state());
}

void Cpu::BVC(MnemonicArgument const arg) {
	if (status.V)
		return;
    PC = arg.targetAddress.address();
	_pcHasChanged = true;
}

void Cpu::BVS(MnemonicArgument const arg) {
	if (!status.V)
		return;
    PC = arg.targetAddress.address();
	_pcHasChanged = true;
}

void Cpu::CLC(MnemonicArgument const) {
    status.C = false;
}

void Cpu::CLD(MnemonicArgument const) {
    status.D = false;
}

void Cpu::CLI(MnemonicArgument const) {
    status.I = false;
}

void Cpu::CLV(MnemonicArgument const) {
    status.V = false;
}

void Cpu::CMP(MnemonicArgument const arg) {
	status.Z = A == arg.readValue.value;
	status.N = A < arg.readValue.value;
	status.C = A > arg.readValue.value;
}

void Cpu::CPX(MnemonicArgument const arg) {
	status.Z = X == arg.readValue.value;
	status.N = X < arg.readValue.value;
	status.C = X > arg.readValue.value;
}

void Cpu::CPY(MnemonicArgument const arg) {
	status.Z = Y == arg.readValue.value;
	status.N = Y < arg.readValue.value;
	status.C = Y > arg.readValue.value;
}

void Cpu::DEC(MnemonicArgument const arg) {
    uint8_t value = arg.readValue.value;
    value--;
    bus->Write(arg.targetAddress.address(), value);

	status.N = value & 0x80u;
	status.Z = value == 0;
}

void Cpu::DEX(MnemonicArgument const) {
    X--;

	status.N = X & 0x80u;
	status.Z = X == 0;
}

void Cpu::DEY(MnemonicArgument const) {
    Y--;

	status.N = Y & 0x80u;
	status.Z = Y == 0;
}

void Cpu::EOR(MnemonicArgument const arg) {
    A ^= arg.readValue.value;

	status.N = A & 0x80u;
	status.Z = A == 0;
}

void Cpu::INC(MnemonicArgument const arg) {
    uint8_t value = arg.readValue.value;
    value++;
    bus->Write(arg.targetAddress.address(), value);

	status.N = value & 0x80u;
	status.Z = value == 0;
}

void Cpu::INX(MnemonicArgument const) {
    X++;

	status.N = X & 0x80u;
	status.Z = X == 0;
}

void Cpu::INY(MnemonicArgument const) {
    Y++;

	status.N = Y & 0x80u;
	status.Z = Y == 0;
}

void Cpu::JMP(MnemonicArgument const arg) {
    PC = arg.targetAddress.address();
	_pcHasChanged = true;
}

void Cpu::JSR(MnemonicArgument const arg) {
   
	MemoryAddress nextAddress{0};
	nextAddress = PC.address() + 2;
	pushOnStack(nextAddress.LL);
	pushOnStack(nextAddress.HH);

	PC = arg.targetAddress.address();
	_pcHasChanged = true;
}

void Cpu::LDA(MnemonicArgument const arg) {
    A = arg.readValue.value;

	status.N = A & 0x80u;
	status.Z = A == 0;
}

void Cpu::LDX(MnemonicArgument const arg) {
    X = arg.readValue.value;

	status.N = X & 0x80u;
	status.Z = X == 0;
}

void Cpu::LDY(MnemonicArgument const arg) {
    Y = arg.readValue.value;

	status.N = Y & 0x80u;
	status.Z = Y == 0;
}

void Cpu::LSR(MnemonicArgument const arg) {
	uint8_t value = arg.isAcu ? A : arg.readValue.value;
	status.C = value & 0x01u;
	value >>= 1u;
	status.Z = value == 0;
	status.N = false;

	if (arg.isAcu)
		A = value;
	else
		bus->Write(arg.targetAddress.address(), value);
}

void Cpu::NOP(MnemonicArgument const) {

}

void Cpu::ORA(MnemonicArgument const arg) {
    A |= arg.readValue.value;

	status.Z = A == 0;
	status.N = A & 0x80u;
}

void Cpu::PHA(MnemonicArgument const) {
    pushOnStack(A);
}

void Cpu::PHP(MnemonicArgument const) {
    pushOnStack(status.state());
}

void Cpu::PLA(MnemonicArgument const) {
    A = pullFromStack();

	status.Z = A == 0;
	status.N = A & 0x80u;
}

void Cpu::PLP(MnemonicArgument const) {
    status = pullFromStack();
}

void Cpu::ROL(MnemonicArgument const arg) {
	uint8_t value = arg.isAcu ? A : arg.readValue.value;
	uint8_t isCurrentCarrySet = status.C;
	status.C = value & 0x80u;
	value <<= 1u;
	value += isCurrentCarrySet;
	status.Z = value == 0;
	status.N = value & 0x80u;

	if (arg.isAcu)
		A = value;
	else
		bus->Write(arg.targetAddress.address(), value);
}

void Cpu::ROR(MnemonicArgument const arg) {
	uint8_t value = arg.isAcu ? A : arg.readValue.value;
	uint8_t isCurrentCarrySet = status.C << 7u;
	status.C = value & 0x01u;
	value >>= 1u;
	value += isCurrentCarrySet;
	status.Z = value == 0;
	status.N = value & 0x80u;

	if (arg.isAcu)
		A = value;
	else
		bus->Write(arg.targetAddress.address(), value);
}

void Cpu::RTI(MnemonicArgument const) {
    status = pullFromStack();
    PC.HH = pullFromStack();
    PC.LL = pullFromStack();
	_pcHasChanged = true;
}

void Cpu::RTS(MnemonicArgument const) {
    PC.HH = pullFromStack();
    PC.LL = pullFromStack();
    PC++;
	_pcHasChanged = true;
}

void Cpu::SBC(MnemonicArgument const arg) {
    uint8_t oldA = A;

	uint16_t newValue = arg.readValue.value;
    newValue ^= 0x00FFu;
	newValue += A + status.C;

    status.C = newValue > 0x00FFu;
    status.V = (~(oldA ^ arg.readValue.value) & (oldA ^ newValue)) & 0x0080u;

    A = newValue & 0x00FFu;

    status.Z = A == 0;
    status.N = A & 0x80u;
}

void Cpu::SEC(MnemonicArgument const) {
    status.C = true;
}

void Cpu::SED(MnemonicArgument const) {
    status.D = true;
}

void Cpu::SEI(MnemonicArgument const) {
    status.I = true;
}

void Cpu::STA(MnemonicArgument const arg) {
    bus->Write(arg.targetAddress.address(), A);
}

void Cpu::STX(MnemonicArgument const arg) {
    bus->Write(arg.targetAddress.address(), X);
}

void Cpu::STY(MnemonicArgument const arg) {
    bus->Write(arg.targetAddress.address(), Y);
}

void Cpu::TAX(MnemonicArgument const) {
    X = A;

	status.Z = X == 0;
	status.N = X & 0x80u;
}

void Cpu::TAY(MnemonicArgument const) {
    Y = A;

	status.Z = Y == 0;
	status.N = Y & 0x80u;
}

void Cpu::TSX(MnemonicArgument const) {
    X = S.offset;

	status.Z = X == 0;
	status.N = X & 0x80u;
}

void Cpu::TXA(MnemonicArgument const) {
    A = X;

	status.Z = A == 0;
	status.N = A & 0x80u;
}

void Cpu::TXS(MnemonicArgument const) {
    S.offset = X;
}

void Cpu::TYA(MnemonicArgument const) {
    A = Y;

	status.Z = A == 0;
	status.N = A & 0x80u;
}

void Cpu::XXX(MnemonicArgument const arg) {
    NOP(arg);
}
