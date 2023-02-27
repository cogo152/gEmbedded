//
// Created by sondahi on 28.01.23.
//

#ifndef GEMBEDDED_C_PIN_VALIDATOR_H
#define GEMBEDDED_C_PIN_VALIDATOR_H

#include "common.h"

typedef enum {
    PIN_VALIDATOR_ERROR_NO = 0,
    PIN_VALIDATOR_ERROR_PIN_NUMBER = 100,
    PIN_VALIDATOR_ERROR_PIN_PULLUPDOWN = 101,
    PIN_VALIDATOR_ERROR_PIN_EVENT = 102,
    PIN_VALIDATOR_ERROR_PIN_EVENT_TIMEOUT = 103
} PIN_VALIDATOR_ERROR;

PIN_VALIDATOR_ERROR validateOutputPin(uint8_t pinNumber);

PIN_VALIDATOR_ERROR validateInputPin(uint8_t pinNumber, uint8_t pinPullUpDown);

PIN_VALIDATOR_ERROR validateListenerPin(uint8_t pinNumber, uint8_t pinPullUpDown, uint8_t pinEvent, int timeoutInMilSec);

#endif //GEMBEDDED_C_PIN_VALIDATOR_H