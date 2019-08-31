//
// Created by Stéphane Loegel on 31/08/2019.
//

#ifndef EMUNES_STACKPOINTER_H
#define EMUNES_STACKPOINTER_H

union StackPointer
{
    uint16_t full;
    uint8_t stack : 8;
    uint8_t overflow : 1; // idk if it's the right term here
};
#endif //EMUNES_STACKPOINTER_H
