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
		return offset + 0x100;
	}

	void operator= (uint8_t const& byte) {
		offset = byte;
	}

	void operator= (uint16_t const& word) {
		offset = (word & 0x00FF);
	}

	void operator-- () {
		offset--;
	}

	void operator++ () {
		offset++;
	}
};
#endif //EMUNES_STACKPOINTER_H
