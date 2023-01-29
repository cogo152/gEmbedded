//
// Created by sondahi on 28.01.23.
//

#include "pin_validator.h"

static const int validPins[MAX_VALID_PIN_SIZE] = {
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11
};

static int isPinValid(const int pinNumber) {

    for (int i = 0; i < MAX_VALID_PIN_SIZE; ++i) {
        if (validPins[i] == pinNumber) {
            return 1;
        }
    }

    return 0;

}

int validateOutputPin(output_pin_t *const outputPin) {

    const int result = isPinValid(outputPin->number);
    if (result == 0) {
        return PIN_VALIDATOR_EXCEPTION_NUMBER_ERROR;
    }

    return PIN_VALIDATOR_EXCEPTION_NO_ERROR;
}

int validateInputPin(input_pin_t *const inputPin) {

    return PIN_VALIDATOR_EXCEPTION_NO_ERROR;
}

int validateListenerPin(listener_pin_t *const listenerPin) {

    return PIN_VALIDATOR_EXCEPTION_NO_ERROR;
}