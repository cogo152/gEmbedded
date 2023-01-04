//
// Created by sondahi on 03.01.23.
//

#ifndef GEMBEDDED_C_PINVALIDATOR_H
#define GEMBEDDED_C_PINVALIDATOR_H

#include "common.h"
#include "pin.h"

typedef enum {
    PIN_VALIDATION_SUCCESS = 0,
    PIN_VALIDATION_ERROR = 1
} PIN_VALIDATION_STATUS;

PIN_VALIDATION_STATUS validatePin(PIN_TYPE pinType, PIN pinToValidate);
PIN_VALIDATION_STATUS registerPin(PIN pin);

#endif //GEMBEDDED_C_PINVALIDATOR_H
