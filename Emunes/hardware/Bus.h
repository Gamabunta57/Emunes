#pragma once

#include <cstdint>

#include "Ram.h"

class Bus
{
public:
	Ram* ram;

public:
	Bus(Ram* ram);
	~Bus();

	uint8_t Read(uint16_t address);
	void Write(uint16_t address, uint8_t byte);

};

