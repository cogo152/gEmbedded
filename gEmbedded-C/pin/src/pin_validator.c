//
// Created by sondahi on 28.01.23.
//

#include "pin_validator.h"
#include "peripheral.h"

int validateOutputPin(pin_t *const pin) {

    if(pin->type !=PIN_TYPE_OUTPUT){
        return PIN_VALIDATOR_EXCEPTION_TYPE_ERROR;
    }

    const int result = isElementInArray(gpioPins, MAX_GPIO_PIN_SIZE, pin->cNumber);
    if (result != 0) {
        return PIN_VALIDATOR_EXCEPTION_NUMBER_ERROR;
    }

    if (pin->cFunction != PIN_CONFIG_FUNCTION_OUTPUT) {
        return PIN_VALIDATOR_EXCEPTION_FUNCTION_ERROR;
    }

    return PIN_VALIDATOR_EXCEPTION_NO_ERROR;
}

int validateInputPin(pin_t *const pin) {

    if(pin->type !=PIN_TYPE_INPUT){
        return PIN_VALIDATOR_EXCEPTION_TYPE_ERROR;
    }

    const int result = isElementInArray(gpioPins, MAX_GPIO_PIN_SIZE, pin->cNumber);
    if (result != 0) {
        return PIN_VALIDATOR_EXCEPTION_NUMBER_ERROR;
    }

    if (pin->cFunction != PIN_CONFIG_FUNCTION_INPUT) {
        return PIN_VALIDATOR_EXCEPTION_FUNCTION_ERROR;
    }

    switch (pin->cPullUpDown) {
        case PIN_CONFIG_PUD_NO_RESISTOR:
        case PIN_CONFIG_PUD_PULL_UP:
        case PIN_CONFIG_PUD_PULL_DOWN:
            break;
        default:
            return PIN_VALIDATOR_EXCEPTION_PUD_ERROR;
    }

    return PIN_VALIDATOR_EXCEPTION_NO_ERROR;
}

int validateListenerPin(pin_t *const pin) {

    if(pin->type !=PIN_TYPE_LISTENER){
        return PIN_VALIDATOR_EXCEPTION_TYPE_ERROR;
    }

    const int result = isElementInArray(gpioPins, MAX_GPIO_PIN_SIZE, pin->cNumber);
    if (result != 0) {
        return PIN_VALIDATOR_EXCEPTION_NUMBER_ERROR;
    }

    if (pin->cFunction != PIN_CONFIG_FUNCTION_INPUT) {
        return PIN_VALIDATOR_EXCEPTION_FUNCTION_ERROR;
    }

    switch (pin->cEvent) {
        case PIN_CONFIG_EVENT_RISING:
        case PIN_CONFIG_EVENT_FALLING:
        case PIN_CONFIG_EVENT_BOTH:
            break;
        default:
            return PIN_VALIDATOR_EXCEPTION_EVENT_ERROR;
    }

    if (pin->cEventTimeout <= 0) {
        return PIN_VALIDATOR_EXCEPTION_EVENT_TIMEOUT_ERROR;
    }

    return PIN_VALIDATOR_EXCEPTION_NO_ERROR;

}