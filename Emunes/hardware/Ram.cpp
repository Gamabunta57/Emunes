#include "Ram.h"

void Ram::Write(uint16_t const address, uint8_t const byte)
{
	this->memory[address] = byte;
}

uint8_t Ram::Read(uint16_t const address) const
{
	return this->memory[address];
}
