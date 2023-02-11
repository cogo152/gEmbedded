//
// Created by sondahi on 28.01.23.
//

#include "pin_validator.h"
#include "peripheral.h"

int validateOutputPin(pin_t *const pin) {

    if(pin->type !=PIN_TYPE_OUTPUT){
        return PIN_VALIDATOR_ERROR_PIN_TYPE;
    }

    const int result = isElementInArray(gpioPins, MAX_GPIO_PIN_SIZE, pin->cNumber);
    if (result != 0) {
        return PIN_VALIDATOR_ERROR_PIN_NUMBER;
    }

    if (pin->cFunction != PIN_CONFIG_FUNCTION_OUTPUT) {
        return PIN_VALIDATOR_ERROR_PIN_FUNCTION;
    }

    return PIN_VALIDATOR_ERROR_NO;
}

int validateInputPin(pin_t *const pin) {

    if(pin->type !=PIN_TYPE_INPUT){
        return PIN_VALIDATOR_ERROR_PIN_TYPE;
    }

    const int result = isElementInArray(gpioPins, MAX_GPIO_PIN_SIZE, pin->cNumber);
    if (result != 0) {
        return PIN_VALIDATOR_ERROR_PIN_NUMBER;
    }

    if (pin->cFunction != PIN_CONFIG_FUNCTION_INPUT) {
        return PIN_VALIDATOR_ERROR_PIN_FUNCTION;
    }

    switch (pin->cPullUpDown) {
        case PIN_CONFIG_PUD_NO_RESISTOR:
        case PIN_CONFIG_PUD_PULL_UP:
        case PIN_CONFIG_PUD_PULL_DOWN:
            break;
        default:
            return PIN_VALIDATOR_ERROR_PIN_PULLUPDOWN;
    }

    return PIN_VALIDATOR_ERROR_NO;
}

int validateListenerPin(pin_t *const pin) {

    if(pin->type !=PIN_TYPE_LISTENER){
        return PIN_VALIDATOR_ERROR_PIN_TYPE;
    }

    const int result = isElementInArray(gpioPins, MAX_GPIO_PIN_SIZE, pin->cNumber);
    if (result != 0) {
        return PIN_VALIDATOR_ERROR_PIN_NUMBER;
    }

    if (pin->cFunction != PIN_CONFIG_FUNCTION_INPUT) {
        return PIN_VALIDATOR_ERROR_PIN_FUNCTION;
    }

    switch (pin->cEvent) {
        case PIN_CONFIG_EVENT_RISING:
        case PIN_CONFIG_EVENT_FALLING:
        case PIN_CONFIG_EVENT_BOTH:
            break;
        default:
            return PIN_VALIDATOR_ERROR_PIN_EVENT;
    }

    if (pin->cEventTimeout <= 0) {
        return PIN_VALIDATOR_ERROR_PIN_EVENT_TIMEOUT;
    }

    return PIN_VALIDATOR_ERROR_NO;

}