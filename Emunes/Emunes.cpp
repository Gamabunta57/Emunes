#include <iostream>
#include <array>
#include <sstream>
#include <string>
#include <iomanip>

#include "Bus.h"
#include "Cpu.h"
#include "Ram.h"

std::string disassemble(Ram* ram, Cpu* cpu, uint16_t startAdress, uint16_t endAddress);
std::string getHexString(int value, int size = 2);
std::string getAdressingModePrefix(AddressingMode mode);
std::string getAdressingModeSuffix(AddressingMode mode);
std::string operator+ (std::string string, AddressingMode addressingMode);

int main()
{

	Cpu* cpu = new Cpu();
	Ram* ram = new Ram();
	Bus bus(ram);
	cpu->attachBus(&bus);
	
	
	/* meaningless program to test all the different addressing mode available 
	0000 START  INX             E8
	0001        ASL A           0A
	0002        LDA #$0A        A9 0A
	0004        ROL *$02        26 02
	0006        ROL *$02,X      36 02
	0008        STX *$02,Y      96 02
	000A        STA $0200,X     9D 00 02
	000D        STA $0300,Y     99 00 03
	0010        STA ($20),Y     91 20
	0012        STA ($40,X)     81 40
	0014        CMP $0010       CD 10 00
	0017        BNE DO          D0 00

	0019 DO     JMP ($0000)     6C 00 00
	*/
	std::string asmString = "E8 0A A9 0A 26 02 36 02 96 02 9D 00 02 99 00 03 91 20 81 40 CD 10 00 D0 03 6C 00 00";
	std::stringstream asmStream(asmString);

	std::string byteCode;
	uint16_t startAddress = 0;
	uint16_t address = startAddress;

	while (asmStream >> byteCode)
		bus.Write(address++, std::stoi(byteCode,NULL,16));
	
	std::cout << "ADDR   MNEMONIC        BYTE CODE   MODE\n";
	std::cout << "---------------------------------------\n";
	std::cout << disassemble(ram, cpu, startAddress, address);

	delete cpu;
	delete ram;

	return 0;
}


std::string disassemble(Ram* ram, Cpu* cpu,  uint16_t startAdress, uint16_t endAddress)
{
	std::string result;
	uint16_t currentAddress = startAdress;
	while (currentAddress < endAddress) {
		uint8_t opcode = ram->Read(currentAddress);
		std::string byteString = getHexString(opcode);
		Instruction instruction = cpu->getInstruction(opcode);

		std::string args = "";
		if (instruction.memoryRequirement > 1) {
			uint8_t byte = ram->Read(currentAddress + 1);
			args = getHexString(byte);
			byteString += " "+ args;

			if (instruction.memoryRequirement > 2){
				byte = ram->Read(currentAddress + 2);
				args = getHexString(byte, 1) + args;
				byteString += " " + getHexString(byte, 2);
			}

			args = '$' + args;
		}

		args = getAdressingModePrefix(instruction.addressingMode) + args + getAdressingModeSuffix(instruction.addressingMode);
		args.resize(12, ' ');

		std::string hexAddress = getHexString(currentAddress, 4);
		hexAddress.resize(7, ' ');
		byteString.resize(12, ' ');
		result +=  hexAddress + instruction.mnemonic + ' ' + args + byteString+ '<'+instruction.addressingMode+">\n";
		currentAddress += instruction.memoryRequirement;
	}
	return result;
}

std::string getHexString(int value, int size) {
	std::stringstream ss("");
	ss << std::setfill('0') << std::setw(size) << std::hex << value;
	return ss.str();
}


std::string getAdressingModePrefix(AddressingMode mode) {
	switch (mode)
	{
	case Indirect:
	case IndexedX:
	case IndexedY:		return "(";

	case Accumulator:	return "A";

	case Immediate:		return "#";

	case ZeroPage:
	case ZeroPageX:
	case ZeroPageY:		return "*";

	};
	return "";
}
std::string getAdressingModeSuffix(AddressingMode mode) {
	switch (mode)
	{
	case Indirect:		return ")";

	case IndexedX:		return ",X)";

	case IndexedY:		return "),Y";

	case ZeroPageX:
	case AbsoluteX:		return ",X";

	case ZeroPageY:
	case AbsoluteY:		return ",Y";

	};
	return "";
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