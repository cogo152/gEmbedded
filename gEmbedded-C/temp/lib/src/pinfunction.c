//
// Created by sondahi on 17.12.22.
//

#include <pthread.h>

#include "pin.h"

PIN_FUNCTION_STATUS
configurePinFunction(PIN validatedPin, PIN_FUNCTION pinFunctionToConfigure, struct PinConfigRegs *pinConfigRegs) {

    if (pinConfigRegs == NULL) {
        return PIN_FUNCTION_ERROR;
    }

    switch (pinFunctionToConfigure) {
        case PIN_FUNCTION_INPUT:
        case PIN_FUNCTION_OUTPUT:
        case PIN_FUNCTION_ALT_0:
        case PIN_FUNCTION_ALT_1:
        case PIN_FUNCTION_ALT_2:
        case PIN_FUNCTION_ALT_3:
        case PIN_FUNCTION_ALT_4:
        case PIN_FUNCTION_ALT_5: {
            const uint8_t registerSelector = validatedPin / 10;
            pinConfigRegs->FSEL[registerSelector] &= ~(7 << ((validatedPin % 10) * 3));
            pinConfigRegs->FSEL[registerSelector] |= (pinFunctionToConfigure << ((validatedPin % 10) * 3));
            break;
        }
        default: {
            return PIN_FUNCTION_ERROR;
        }
    }

    return PIN_FUNCTION_SUCCESS;

}

PIN_FUNCTION_STATUS
readPinFunction(PIN validatedPin, PIN_FUNCTION *pinFunctionToRead, struct PinConfigRegs *pinConfigRegs) {

    if (pinConfigRegs == NULL) {
        return PIN_FUNCTION_ERROR;
    }

    const uint8_t registerSelector = validatedPin / 10;
    uint32_t registerLine = pinConfigRegs->FSEL[registerSelector];
    uint32_t mask = (7 << ((validatedPin % 10) * 3));
    uint32_t pinFunction = registerLine & mask;
    pinFunction >>= ((validatedPin % 10) * 3);
    *pinFunctionToRead = pinFunction;

    return PIN_FUNCTION_SUCCESS;

}