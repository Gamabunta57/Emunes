#include "Bus.h"

Bus::Bus(Ram* const ram)
	:ram(ram)
{
};

Bus::~Bus() = default;

uint8_t Bus::Read(uint16_t const address) const
{
	return ram->Read(address);
}

void Bus::Write(uint16_t const address, uint8_t const byte) const
{
	ram->Write(address, byte);
}
