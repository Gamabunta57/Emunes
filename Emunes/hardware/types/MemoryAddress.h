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
	[[nodiscard]] uint16_t address() const{
		return LL + (HH << 8u);
	}
	
	MemoryAddress operator++ (int) {
        const MemoryAddress result(*this);
	    *this = address()+1;
		return result;
	}

	MemoryAddress& operator= (uint16_t const value) {
		this->LL = value & 0x00FFu;
		this->HH = (value & 0xFF00u) >> 8u;
		return *this;
	}

	MemoryAddress& operator+= (int const value) {
		*this = this->address() + value;
		return *this;
	}

	MemoryAddress operator+ (uint8_t const byte) {
		MemoryAddress newMA{ this->LL,this->HH};
		return newMA += byte;
	}
};
#endif //EMUNES_MEMORYADDRESS_H
