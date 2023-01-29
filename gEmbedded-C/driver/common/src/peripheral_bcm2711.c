//
// Created by sondahi on 27.01.23.
//

#include "peripheral_bcm2711.h"

void setPinFunction(volatile uintptr_t *const GPFSEL,const uint8_t pinNumber, const uint8_t pinFunction) {

    const uint8_t registerSelector = pinNumber / PIN_CONFIG_FUNCTION_MOD_DIV;
    const uint32_t clearValue = ~(PIN_CONFIG_FUNCTION_MASK << ((pinNumber % PIN_CONFIG_FUNCTION_MOD_DIV) * PIN_CONFIG_FUNCTION_MUL));
    const uint32_t setValue = pinFunction << ((pinNumber % PIN_CONFIG_FUNCTION_MOD_DIV) * PIN_CONFIG_FUNCTION_MUL);
    GPFSEL[registerSelector] &= clearValue;
    GPFSEL[registerSelector] |= setValue;

}

uint8_t readPinFunction(volatile uintptr_t *const GPFSEL, const uint8_t pinNumber) {

    const uint8_t registerSelector = pinNumber / PIN_CONFIG_FUNCTION_MOD_DIV;
    const uint32_t registerLine = GPFSEL[registerSelector];
    const uint32_t maskValue =
            PIN_CONFIG_FUNCTION_MASK << ((pinNumber % PIN_CONFIG_FUNCTION_MOD_DIV) * PIN_CONFIG_FUNCTION_MUL);
    uint32_t pinFunction = registerLine & maskValue;
    pinFunction >>= ((pinNumber % PIN_CONFIG_FUNCTION_MOD_DIV) * PIN_CONFIG_FUNCTION_MUL);
    return pinFunction;

}