#include <iostream>
#include <array>
#include <sstream>
#include <string>
#include <iomanip>

#include "Bus.h"
#include "Cpu.h"
#include "Ram.h"

std::string disassemble(Ram* ram, Cpu* cpu, uint16_t startAdress, uint16_t endAddress);

std::string operator+ (std::string string, AddressingMode addressingMode);


int main()
{

	Cpu* cpu = new Cpu();
	Ram* ram = new Ram();
	Bus bus(ram);
	cpu->attachBus(&bus);
	
	std::string asmString = "a9 01 8d 00 02 a9 05 8d 01 02 a9 08 8d 02 02";
	/*
	LDA #$01
	STA $0200
	LDA #$05
	STA $0201
	LDA #$08
	STA $0202
	*/
	std::stringstream asmStream(asmString);

	std::string byteCode;
	uint16_t address = 0;

	while (asmStream >> byteCode)
		bus.Write(address++, std::stoi(byteCode,NULL,16));
	
	std::cout << disassemble(ram, cpu, 0, address);

	delete cpu;
	delete ram;

	return 0;
}


std::string disassemble(Ram* ram, Cpu* cpu,  uint16_t startAdress, uint16_t endAddress)
{
	std::string result;
	uint16_t currentAddress = startAdress;
	while (currentAddress < endAddress) {
		Instruction instruction = cpu->getInstruction(ram->Read(currentAddress));
		currentAddress += instruction.memoryRequirement;

		result += instruction.mnemonic + " " + "<" + instruction.addressingMode +">";
	}
	return result;
}


std::string operator+ (std::string string, AddressingMode addressingMode)
{
	switch (addressingMode)
	{
	case Immediate: return string + "IMM";
	case Absolute: return string + "ABS";
	case ZeroPage: return string + " ZP";
	case Accumulator: return string + "ACU";
	case Implied: return string + "IMP";
	case IndexedX: return string + "IDX";
	case IndexedY: return string + "IDY";
	case ZeroPageX: return string + "ZPX";
	case AbsoluteX: return string + "ABX";
	case AbsoluteY: return string + "ABY";
	case Relative: return string + "REL";
	case Indirect: return string + "IND";
	case ZeroPageY: return  string + "ZPY";
	};
	return string;
}