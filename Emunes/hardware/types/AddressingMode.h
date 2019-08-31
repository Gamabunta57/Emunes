//
// Created by Stéphane Loegel on 31/08/2019.
//

#ifndef EMUNES_ADDRESSINGMODE_H
#define EMUNES_ADDRESSINGMODE_H

enum AddressingMode {
    Immediate,
    Absolute,
    ZeroPage,
    Accumulator,
    Implied,
    IndexedX,
    IndexedY,
    ZeroPageX,
    AbsoluteX,
    AbsoluteY,
    Relative,
    Indirect,
    ZeroPageY
};

#endif //EMUNES_ADDRESSINGMODE_H
