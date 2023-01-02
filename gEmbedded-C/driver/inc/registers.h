//
// Created by sondahi on 29.12.22.
//

#ifndef GEMBEDDED_C_REGISTERS_H
#define GEMBEDDED_C_REGISTERS_H

struct PinConfigRegs {
    volatile uintptr_t FSEL[6];
    uintptr_t NotUsed1[13];
    volatile uintptr_t REN[2];
    uintptr_t NotUsed2;
    volatile uintptr_t FEN[2];
    uintptr_t NotUsed3;
    volatile uintptr_t HEN[2];
    uintptr_t NotUsed4;
    volatile uintptr_t LEN[2];
    uintptr_t NotUsed5;
    volatile uintptr_t AREN[2];
    uintptr_t NotUsed6;
    volatile uintptr_t AFEN[2];
    uintptr_t NotUsed7[21];
    volatile uintptr_t PUP_PDN[4];
};

struct PinIORegs {
    uintptr_t NotUsed1[7];
    volatile uintptr_t SET[2];
    uintptr_t NotUsed2;
    volatile uintptr_t CLR[2];
    uintptr_t NotUsed3;
    volatile uintptr_t LEV[2];
    uintptr_t NotUsed4;
    volatile uintptr_t EDS[2];
};

struct ClockRegs {
    volatile uintptr_t CTL;
    volatile uintptr_t DIV;
};

struct PWMRegs {
    volatile uintptr_t CTL;
    volatile uintptr_t STA;
    volatile uintptr_t DMAC;
    uintptr_t NotUsed1;
    volatile uintptr_t RNG0;
    volatile uintptr_t DAT0;
    volatile uintptr_t FIFO;
    uintptr_t NotUsed2;
    volatile uintptr_t RNG1;
    volatile uintptr_t DAT1;
};

struct I2CRegs {
    volatile uintptr_t C;
    volatile uintptr_t S;
    volatile uintptr_t DLEN;
    volatile uintptr_t A;
    volatile uintptr_t FIFO;
    volatile uintptr_t DIV;
    volatile uintptr_t DEL;
    volatile uintptr_t CLKT;
};

#endif //GEMBEDDED_C_REGISTERS_H