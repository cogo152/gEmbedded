//
// Created by sondahi on 17.12.22.
//

#include "pin.h"

PULL_UP_DOWN_STATUS
configurePullUpDown(PIN validatedPin, PULL_UP_DOWN pullUpDownToConfigure, struct PinConfigRegs *pinConfigRegs) {

    if (pinConfigRegs == NULL) {
        return PULL_UP_DOWN_ERROR;
    }

    switch (pullUpDownToConfigure) {
        case PULL_UP_DOWN_NO_RESISTOR:
        case PULL_UP_DOWN_PULL_UP:
        case PULL_UP_DOWN_PULL_DOWN:{
            const uint8_t registerSelector = validatedPin / 16;
            pinConfigRegs->PUP_PDN[registerSelector] &= ~(3 << ((validatedPin % 16) * 2));
            pinConfigRegs->PUP_PDN[registerSelector] |= (pullUpDownToConfigure << ((validatedPin % 16) * 2));
            break;
        }
        default: {
            return PULL_UP_DOWN_ERROR;
        }
    }

    return PULL_UP_DOWN_SUCCESS;

}

PULL_UP_DOWN_STATUS
readPullUpDown(PIN validatedPin, PULL_UP_DOWN *pullUpDownToRead, struct PinConfigRegs *pinConfigRegs) {

    if (pinConfigRegs == NULL) {
        return PULL_UP_DOWN_ERROR;
    }

    const uint8_t registerSelector = validatedPin / 16;
    uint32_t registerLine = pinConfigRegs->PUP_PDN[registerSelector];
    uint32_t mask = (3 << ((validatedPin % 16) * 2));
    uint32_t pullUpDown = registerLine & mask;
    pullUpDown >>= ((validatedPin % 16) * 2);
    *pullUpDownToRead = pullUpDown;

    return PULL_UP_DOWN_SUCCESS;

}