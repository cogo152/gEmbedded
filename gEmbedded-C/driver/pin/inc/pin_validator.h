//
// Created by sondahi on 28.01.23.
//

#ifndef GEMBEDDED_C_PIN_VALIDATOR_H
#define GEMBEDDED_C_PIN_VALIDATOR_H

#include "common.h"

typedef enum {
    PIN_VALIDATOR_ERROR_NO = 0,
    PIN_VALIDATOR_ERROR_PIN_NUMBER = -1,
    PIN_VALIDATOR_ERROR_PIN_PULLUPDOWN = -2,
    PIN_VALIDATOR_ERROR_PIN_EVENT = -3,
    PIN_VALIDATOR_ERROR_PIN_EVENT_TIMEOUT = -4
} PIN_VALIDATOR_ERROR;

PIN_VALIDATOR_ERROR validateOutputPin(uint8_t pinNumber);

PIN_VALIDATOR_ERROR validateInputPin(uint8_t pinNumber, uint8_t pinPullUpDown);

PIN_VALIDATOR_ERROR validateListenerPin(uint8_t pinNumber, uint8_t pinEvent, int pinEventTimeOutInMilSec);

#endif //GEMBEDDED_C_PIN_VALIDATOR_H