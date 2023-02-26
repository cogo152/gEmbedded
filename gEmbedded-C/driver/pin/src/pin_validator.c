//
// Created by sondahi on 28.01.23.
//

#include "pin_validator.h"
#include "peripheral.h"

PIN_VALIDATOR_ERROR validateOutputPin(const uint8_t pinNumber) {

    const int result = isElementInArray(gpioPins, MAX_GPIO_PIN_SIZE, pinNumber);
    if (result != 0) {
        return PIN_VALIDATOR_ERROR_PIN_NUMBER;
    }

    return PIN_VALIDATOR_ERROR_NO;
}

PIN_VALIDATOR_ERROR validateInputPin(const uint8_t pinNumber, const uint8_t pinPullUpDown) {

    const int result = isElementInArray(gpioPins, MAX_GPIO_PIN_SIZE, pinNumber);
    if (result != 0) {
        return PIN_VALIDATOR_ERROR_PIN_NUMBER;
    }

    switch (pinPullUpDown) {
        case PIN_CONFIG_PUD_NO_RESISTOR:
        case PIN_CONFIG_PUD_PULL_UP:
        case PIN_CONFIG_PUD_PULL_DOWN:
            break;
        default:
            return PIN_VALIDATOR_ERROR_PIN_PULLUPDOWN;
    }

    return PIN_VALIDATOR_ERROR_NO;
}

PIN_VALIDATOR_ERROR
validateListenerPin(const uint8_t pinNumber, const uint8_t pinEvent, const int pinEventTimeOutInMilSec) {

    const int result = isElementInArray(gpioPins, MAX_GPIO_PIN_SIZE, pinNumber);
    if (result != 0) {
        return PIN_VALIDATOR_ERROR_PIN_NUMBER;
    }

    switch (pinEvent) {
        case PIN_CONFIG_EVENT_RISING:
        case PIN_CONFIG_EVENT_FALLING:
        case PIN_CONFIG_EVENT_BOTH:
            break;
        default:
            return PIN_VALIDATOR_ERROR_PIN_EVENT;
    }

    if (pinEventTimeOutInMilSec <= 0) {
        return PIN_VALIDATOR_ERROR_PIN_EVENT_TIMEOUT;
    }

    return PIN_VALIDATOR_ERROR_NO;

}