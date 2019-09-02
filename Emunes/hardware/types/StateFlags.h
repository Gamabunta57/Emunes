#pragma once

#include <cstdint>

union StateFlags
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

	StateFlags(const uint8_t &state) {
		operator=(state);
	}

	uint8_t state() {
		return (C << 0)
			+ (Z << 1)
			+ (I << 2)
			+ (D << 3)
			+ (B << 4)
			+ (_ << 5)
			+ (V << 6)
			+ (N << 7)
			;
	}

	void operator=(const uint8_t &state) {
		C = state & 0x01;
		Z = state & 0x02;
		I = state & 0x04;
		D = state & 0x08;
		B = state & 0x10;
		_ = state & 0x20;
		V = state & 0x40;
		N = state & 0x80;
	}
};
