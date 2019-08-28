#include "Bus.h"

Bus::Bus(Cpu* cpu, Ram* ram)
	:cpu(cpu), ram(ram)
{};

Bus::~Bus() {}

uint8_t Bus::Read(uint16_t address)
{
	return (*ram).Read(address);
}

void Bus::Write(uint16_t address, uint8_t byte)
{
	(*ram).Write(address, byte);
}
