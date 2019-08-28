#pragma once

#include <cstdint>

#include "Cpu.h"
#include "Ram.h"

class Bus
{
public:
	Cpu* cpu;
	Ram* ram;

public:
	Bus(Cpu* cpu, Ram* ram);
	~Bus();

	uint8_t Read(uint16_t address);
	void Write(uint16_t address, uint8_t byte);

};

