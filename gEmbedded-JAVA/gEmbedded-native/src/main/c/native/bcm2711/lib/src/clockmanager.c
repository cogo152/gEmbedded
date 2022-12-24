#include "clockmanager.h"

CLOCK_STATUS configureClock (uintptr_t volatile *ctlOffset, uintptr_t volatile *divOffset, uint32_t clockFrequency) {

    if (clockFrequency > CLOCK_MAX_FREQUENCY) {
        return CLOCK_ERROR;
    }

    uint32_t divi = CLOCK_PLLD_FREQUENCY / clockFrequency;
    if ((divi < CLOCK_MIN_DIVI) || (divi > CLOCK_MAX_DIVI)) {
        return CLOCK_ERROR;
    }

    if (*ctlOffset & CLOCK_BUSY) {
        *ctlOffset = CLOCK_PASSWD | CLOCK_KILL;
        while (*ctlOffset & CLOCK_BUSY);
    }

    *ctlOffset = CLOCK_PASSWD | CLOCK_MASH_0 | CLOCK_FLIP_NOT_INVERT | CLOCK_SRC_PLLD;
    *divOffset = CLOCK_PASSWD | CLOCK_DIV(divi, 0);

    return CLOCK_SUCCESS;
}

CLOCK_STATUS enableClock (uintptr_t volatile *ctlOffset) {

    if (*ctlOffset & CLOCK_ENABLE) {
        return CLOCK_ERROR;
    }

    uint32_t registerLine = *ctlOffset;
    registerLine &= 0x00FFFFFF;
    registerLine |= CLOCK_PASSWD | CLOCK_ENABLE;
    *ctlOffset = registerLine;

    return CLOCK_SUCCESS;
}

CLOCK_STATUS disableClock (uintptr_t volatile *ctlOffset) {

    if (!(*ctlOffset & CLOCK_ENABLE)) {
        return CLOCK_ERROR;
    }

    uint32_t registerLine = *ctlOffset;
    registerLine &= 0x00FFFFEF;
    registerLine |= CLOCK_PASSWD;
    *ctlOffset = registerLine;

    while (*ctlOffset & CLOCK_BUSY);

    return CLOCK_SUCCESS;
}
