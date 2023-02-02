//
// Created by sondahi on 28.01.23.
//

#ifndef GEMBEDDED_C_PIN_VALIDATOR_H
#define GEMBEDDED_C_PIN_VALIDATOR_H

#include "pin.h"

#define PIN_VALIDATOR_EXCEPTION_NO_ERROR            (0)
#define PIN_VALIDATOR_EXCEPTION_NUMBER_ERROR        (-1)
#define PIN_VALIDATOR_EXCEPTION_FUNCTION_ERROR      (-2)
#define PIN_VALIDATOR_EXCEPTION_PUD_ERROR           (-3)
#define PIN_VALIDATOR_EXCEPTION_EVENT_ERROR         (-4)
#define PIN_VALIDATOR_EXCEPTION_EVENT_TIMEOUT_ERROR (-5)

int validateOutputPin(pin_t *pin);

int validateInputPin(pin_t *pin);

int validateListenerPin(pin_t *pin);

#endif //GEMBEDDED_C_PIN_VALIDATOR_H