#pragma once

#include <cstdint>

#include "Ram.h"

class Bus
{
public:
	Ram* ram;

public:
	explicit Bus(Ram* ram);
	~Bus();

	uint8_t Read(uint16_t address) const;
	void Write(uint16_t address, uint8_t byte) const;

};

