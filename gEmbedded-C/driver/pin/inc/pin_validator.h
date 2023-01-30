//
// Created by sondahi on 28.01.23.
//

#ifndef GEMBEDDED_C_PIN_VALIDATOR_H
#define GEMBEDDED_C_PIN_VALIDATOR_H

#include "pin.h"
#include "pin_status.h"

#define MAX_VALID_PIN_SIZE  (12)

int validateOutputPin(pin_t *pin);

int validateInputPin(pin_t *pin);

int validateListenerPin(pin_t *pin);

#endif //GEMBEDDED_C_PIN_VALIDATOR_H