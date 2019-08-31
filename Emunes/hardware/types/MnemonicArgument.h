//
// Created by Stéphane Loegel on 31/08/2019.
//

#ifndef EMUNES_MNEMONICARGUMENT_H
#define EMUNES_MNEMONICARGUMENT_H

#include "byte.h"

union Word{
    uint16_t word;
    byte LL;
    byte HH;
};

struct MnemonicArgument{
    Word value;
    bool isAcu;
	//TODO : add address for operands that need it
};

#endif //EMUNES_MNEMONICARGUMENT_H
