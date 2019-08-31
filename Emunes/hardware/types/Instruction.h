//
// Created by Stéphane Loegel on 31/08/2019.
//

#ifndef EMUNES_INSTRUCTION_H
#define EMUNES_INSTRUCTION_H

struct Instruction {
    //uint8_t opcode; implied by the index in the instruction set
    std::string mnemonic;
    AddressingMode addressingMode;
    uint8_t memoryRequirement; // byte code size (1, 2 or 3)
    uint8_t executionTime; // in machine cycle
};

#endif //EMUNES_INSTRUCTION_H
