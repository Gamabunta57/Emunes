//
// Created by Stéphane Loegel on 31/08/2019.
//

#ifndef EMUNES_REGISTERADDRESS_H
#define EMUNES_REGISTERADDRESS_H

#include "byte.h"

union Address{
    uint16_t full;
    byte LL;
    byte HH;
};
#endif //EMUNES_REGISTERADDRESS_H
