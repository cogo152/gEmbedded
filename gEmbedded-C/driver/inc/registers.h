//
// Created by sondahi on 29.12.22.
//

#ifndef GEMBEDDED_C_REGISTERS_H
#define GEMBEDDED_C_REGISTERS_H

#include "common.h"

#define DEVICE_NAME             ("RaspberryPi-4B")
#define CORE_CLOCK_SPEED        (1500000000U)

#define MEMORY_FILE_NAME        ("/dev/mem")
#define PERIPHERAL_BASE_ADDRESS (0xFE000000)
#define BLOCK_SIZE              (0X1000)

#define GPIO_BASE_ADDRESS       (PERIPHERAL_BASE_ADDRESS+0x00200000)
#define CLOCK_BASE_ADDRESS      (PERIPHERAL_BASE_ADDRESS+0x00101000)
#define CLOCK_GP0_OFFSET        (0X70/4)
#define CLOCK_PWM_OFFSET        (0xa0/4)
#define PWM_BASE_ADDRESS        (PERIPHERAL_BASE_ADDRESS+0x0020c000)
#define I2C_BASE_ADDRESS        (PERIPHERAL_BASE_ADDRESS+0x00804000)

#define FSEL_OFFSET     (0x00/4)
#define REN_OFFSET      (0x4c/4)
#define FEN_OFFSET      (0x58/4)
#define HEN_OFFSET      (0x64/4)
#define LEN_OFFSET      (0x70/4)
#define AREN_OFFSET     (0x7c/4)
#define AFEN_OFFSET     (0x88/4)
#define PUP_PDN_OFFSET  (0xe4/4)

struct PinConfigRegs {
    volatile uintptr_t FSEL;
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

#define SET_OFFSET  (0x1c/4)
#define CLR_OFFSET  (0x28/4)
#define LEV_OFFSET  (0x34/4)
#define EDS_OFFSET  (0x40/4)

struct PinIORegs {
    volatile uintptr_t *SET;
    volatile uintptr_t *CLR;
    volatile uintptr_t *LEV;
    volatile uintptr_t *EDS;
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