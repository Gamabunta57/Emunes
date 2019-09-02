//
// Created by Stéphane Loegel on 31/08/2019.
//

#ifndef EMUNES_MEMORYADDRESS_H
#define EMUNES_MEMORYADDRESS_H

#include <cstdint>

struct MemoryAddress{

public:
	uint8_t LL;
	uint8_t HH;

public:
	const inline uint16_t address() {
		return LL + (HH << 8);
	}
	
	MemoryAddress& operator++ () {
		operator+(1);
	}

	void operator= (uint16_t const& value) {
		LL = value & 0x00FF;
		HH = (value & 0xFF00) >> 8;
	}

	void operator+= (int const& value) {
		operator+(value);
	}

	void operator+ (uint8_t const& byte) {
		uint16_t currentAddress = address();
		currentAddress += byte;
		LL = currentAddress & 0x00FF;
		HH = (currentAddress & 0xFF00) >> 8;
	}
};
#endif //EMUNES_MEMORYADDRESS_H
