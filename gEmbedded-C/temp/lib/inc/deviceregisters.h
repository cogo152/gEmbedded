//
// Created by sondahi on 07.12.22.
//

#ifndef GEMBEDDED_C_DEVICEREGISTERS_H
#define GEMBEDDED_C_DEVICEREGISTERS_H

#include "common.h"
#include "devicecontextstatus.h"

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

typedef enum {
    CLOCK_GP_0 = 0,
    CLOCK_PWM = 1
} CLOCK_ID;

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

// Thread safe
DEVICE_CONTEXT_STATUS requestPinConfigRegs(struct PinConfigRegs **);

// Thread safe
DEVICE_CONTEXT_STATUS requestPinIORegs(struct PinIORegs **);

// Thread safe
DEVICE_CONTEXT_STATUS requestClockRegs(CLOCK_ID, struct ClockRegs **);

// Thread safe
DEVICE_CONTEXT_STATUS requestPWMRegs(struct PWMRegs **);

// Thread safe
DEVICE_CONTEXT_STATUS requestI2CRegs(struct I2CRegs **);

#endif //GEMBEDDED_C_DEVICEREGISTERS_H
