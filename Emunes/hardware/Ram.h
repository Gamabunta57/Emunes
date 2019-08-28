#pragma once

#include <array>
#include <cstdint>

class Ram{

public:
	void Write(uint16_t address, uint8_t byte);
	uint8_t Read(uint16_t address);

private:
	std::array<uint8_t, 64 * 1024> memory;
};