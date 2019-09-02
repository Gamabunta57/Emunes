//
// Created by Stéphane Loegel on 31/08/2019.
//

#ifndef EMUNES_MNEMONICARGUMENT_H
#define EMUNES_MNEMONICARGUMENT_H

#include "byte.h"
#include "MemoryAddress.h"

struct MnemonicArgument{
    MemoryAddress targetAddress;
    byte readValue;
    bool isAcu;
};

#endif //EMUNES_MNEMONICARGUMENT_H
