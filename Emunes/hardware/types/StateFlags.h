#pragma once

#include <cstdint>

struct StateFlags
{
public:
	bool C;
	bool Z;
	bool I;
	bool D;
	bool B;
	bool _;
	bool V;
	bool N;

public:

	StateFlags(uint8_t const state) {
		C = state & 0x01u;
		Z = state & 0x02u;
		I = state & 0x04u;
		D = state & 0x08u;
		B = state & 0x10u;
		_ = state & 0x20u;
		V = state & 0x40u;
		N = state & 0x80u;
	}

	uint8_t state() {
		return (C << 0u)
			+ (Z << 1u)
			+ (I << 2u)
			+ (D << 3u)
			+ (B << 4u)
			+ (_ << 5u)
			+ (V << 6u)
			+ (N << 7u)
			;
	}

	StateFlags& operator=(uint8_t const state) {
		this->C = state & 0x01u;
		this->Z = state & 0x02u;
		this->I = state & 0x04u;
		this->D = state & 0x08u;
		this->B = state & 0x10u;
		this->_ = state & 0x20u;
		this->V = state & 0x40u;
		this->N = state & 0x80u;
		return *this;
	}
};
