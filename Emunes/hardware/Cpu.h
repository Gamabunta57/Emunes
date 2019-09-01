#pragma once
#include <cstdint>
#include <array>
#include <string>

#include "types/ProgramCounter.h"
#include "types/StackPointer.h"
#include "types/AddressingMode.h"
#include "types/MnemonicArgument.h"

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
    struct Instruction {
        //uint8_t opcode; implied by the index in the instruction set
        std::string mnemonic;
        AddressingMode addressingMode;
        uint8_t memoryRequirement; // byte code size (1, 2 or 3)
        uint8_t executionTime; // in machine cycle
        void (Cpu::*mnemonicCall )(MnemonicArgument) = nullptr;
    };

public:
	static const uint16_t RESET_VECTOR_ADDR = 0xFFFC;
    static const uint8_t STACK_POINTER_INITIAL_VALUE = 0xFD;

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
    MnemonicArgument fetchArgument(const AddressingMode &mode, const uint8_t *instructionBytes);

    void pushOnStack(uint8_t value);
    uint8_t pullFromStack();

    void ADC(MnemonicArgument arg);
    void AND(MnemonicArgument arg);
    void ASL(MnemonicArgument arg);
    void BCC(MnemonicArgument arg);
    void BCS(MnemonicArgument arg);
    void BEQ(MnemonicArgument arg);
    void BIT(MnemonicArgument arg);
    void BMI(MnemonicArgument arg);
    void BNE(MnemonicArgument arg);
    void BPL(MnemonicArgument arg);
    void BRK(MnemonicArgument arg);
    void BVC(MnemonicArgument arg);
    void BVS(MnemonicArgument arg);
    void CLC(MnemonicArgument arg);
    void CLD(MnemonicArgument arg);
    void CLI(MnemonicArgument arg);
    void CLV(MnemonicArgument arg);
    void CMP(MnemonicArgument arg);
    void CPX(MnemonicArgument arg);
    void CPY(MnemonicArgument arg);
    void DEC(MnemonicArgument arg);
    void DEX(MnemonicArgument arg);
    void DEY(MnemonicArgument arg);
    void EOR(MnemonicArgument arg);
    void INC(MnemonicArgument arg);
    void INX(MnemonicArgument arg);
    void INY(MnemonicArgument arg);
    void JMP(MnemonicArgument arg);
    void JSR(MnemonicArgument arg);
    void LDA(MnemonicArgument arg);
    void LDX(MnemonicArgument arg);
    void LDY(MnemonicArgument arg);
    void LSR(MnemonicArgument arg);
    void NOP(MnemonicArgument arg);
    void ORA(MnemonicArgument arg);
    void PHA(MnemonicArgument arg);
    void PHP(MnemonicArgument arg);
    void PLA(MnemonicArgument arg);
    void PLP(MnemonicArgument arg);
    void ROL(MnemonicArgument arg);
    void ROR(MnemonicArgument arg);
    void RTI(MnemonicArgument arg);
    void RTS(MnemonicArgument arg);
    void SBC(MnemonicArgument arg);
    void SEC(MnemonicArgument arg);
    void SED(MnemonicArgument arg);
    void SEI(MnemonicArgument arg);
    void STA(MnemonicArgument arg);
    void STX(MnemonicArgument arg);
    void STY(MnemonicArgument arg);
    void TAX(MnemonicArgument arg);
    void TAY(MnemonicArgument arg);
    void TSX(MnemonicArgument arg);
    void TXA(MnemonicArgument arg);
    void TXS(MnemonicArgument arg);
    void TYA(MnemonicArgument arg);
    void XXX(MnemonicArgument arg);
};


