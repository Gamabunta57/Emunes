//
// Created by Stéphane Loegel on 31/08/2019.
//

#ifndef EMUNES_STACKPOINTER_H
#define EMUNES_STACKPOINTER_H

struct StackPointer
{
	uint8_t offset;
    bool overflow; // just 1 bit according to the 6502 doc (idk if overflow is the right naming here)

	uint16_t address() {
		return offset + 0x100u;
	}

	StackPointer& operator= (uint8_t const byte) {
		this->offset = byte;
		return *this;
	}

	StackPointer& operator= (uint16_t const word) {
		this->offset = word & 0x00FFu;
		return *this;
	}

	StackPointer operator-- (int) {
	    StackPointer result(*this);
		this->offset--;
		return result;
	}

	StackPointer operator++ (int) {
        StackPointer result(*this);
        this->offset++;
        return result;
	}
};
#endif //EMUNES_STACKPOINTER_H
