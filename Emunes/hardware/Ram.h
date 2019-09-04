#pragma once

#include <array>
#include <cstdint>

class Ram{

public:
	void Write(uint16_t address, uint8_t byte);
	[[nodiscard]] uint8_t Read(uint16_t address) const;

private:
	std::array<uint8_t, 64 * 1024> memory;
};