//
// Created by Stéphane Loegel on 31/08/2019.
//

#ifndef EMUNES_PROGRAMCOUNTER_H
#define EMUNES_PROGRAMCOUNTER_H

union ProgramCounter
{
    uint16_t address;
    uint8_t PCL :8;
    uint8_t PCH :8;
};

#endif //EMUNES_PROGRAMCOUNTER_H
