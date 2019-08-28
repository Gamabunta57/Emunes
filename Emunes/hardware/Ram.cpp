#include "Ram.h"

void Ram::Write(uint16_t address, uint8_t byte)
{
	this->memory[address] = byte;
}

uint8_t Ram::Read(uint16_t address)
{
	return this->memory[address];
}
