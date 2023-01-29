//
// Created by sondahi on 28.01.23.
//

#ifndef GEMBEDDED_C_PIN_VALIDATOR_H
#define GEMBEDDED_C_PIN_VALIDATOR_H

#include "pin.h"
#include "pin_exception.h"

#define MAX_VALID_PIN_SIZE  (12)

int validateOutputPin(output_pin_t *outputPin);

int validateInputPin(input_pin_t *inputPin);

int validateListenerPin(listener_pin_t *listenerPin);

#endif //GEMBEDDED_C_PIN_VALIDATOR_H