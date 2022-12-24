#ifndef CLOCKMANAGER_H
#define CLOCKMANAGER_H

#include "common.h"

#define CLOCK_PASSWD                (0x5a<<24)
#define CLOCK_MASH_0                (0<<9)
#define CLOCK_MASH_1                (1<<9)
#define CLOCK_MASH_2                (2<<9)
#define CLOCK_MASH_3                (3<<9)
#define CLOCK_FLIP_INVERT           (1<<8)
#define CLOCK_FLIP_NOT_INVERT       (0<<8)
#define CLOCK_BUSY                  (1<<7)
#define CLOCK_KILL                  (1<<5)
#define CLOCK_ENABLE                (1<<4)
#define CLOCK_SRC_GND0              (0<<0)
#define CLOCK_SRC_OSCILLATOR        (1<<0)
#define CLOCK_SRC_TESTDEBUG0        (2<<0)
#define CLOCK_SRC_TESTDEBUG1        (3<<0)
#define CLOCK_SRC_PLLA              (4<<0)
#define CLOCK_SRC_PLLC              (5<<0)
#define CLOCK_SRC_PLLD              (6<<0)
#define CLOCK_SRC_HDMI              (7<<0)
#define CLOCK_SRC_GND1              (8<<0)
#define CLOCK_DIV(divi, divf)       (((divi)<<12) | ((divf)<<0))

#define CLOCK_MAX_FREQUENCY         (25000000U)
#define CLOCK_PLLD_FREQUENCY        (500000000U)
#define CLOCK_MIN_DIVI              (1U)
#define CLOCK_MAX_DIVI              (4095U)

typedef enum {
    CLOCK_SUCCESS = 0,
    CLOCK_ERROR = 1
} CLOCK_STATUS;

CLOCK_STATUS configureClock (uintptr_t volatile *ctlOffset, uintptr_t volatile *divOffset, uint32_t clockFrequency);

CLOCK_STATUS enableClock (uintptr_t volatile *ctlOffset);

CLOCK_STATUS disableClock (uintptr_t volatile *ctlOffset);

#endif //CLOCKMANAGER_H
