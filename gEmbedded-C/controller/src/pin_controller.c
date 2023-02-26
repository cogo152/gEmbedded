//
// Created by sondahi on 26.02.23.
//

#include "pin_controller.h"
#include "pin_validator.h"
#include "pin_driver.h"
#include "peripheral.h"

PIN_CONTROLLER_ERROR pinControllerInit() {

    const PIN_DRIVER_ERROR error = initPinDriver();
    if (error != PIN_DRIVER_ERROR_NO) {
        return PIN_CONTROLLER_ERROR_INIT;
    }

    return PIN_CONTROLLER_ERROR_NO;

}

PIN_CONTROLLER_ERROR pinControllerDestroy() {

    const PIN_DRIVER_ERROR error = destroyPinDriver();
    if (error != PIN_DRIVER_ERROR_NO) {
        return PIN_CONTROLLER_ERROR_DESTROY;
    }

    return PIN_CONTROLLER_ERROR_NO;

}

PIN_CONTROLLER_ERROR outputPinOpen(const uint8_t pinNumber, uint32_t *const ioReference) {

    const PIN_VALIDATOR_ERROR validatorError = validateOutputPin(pinNumber);
    if (validatorError != PIN_VALIDATOR_ERROR_NO) {
        return PIN_CONTROLLER_ERROR_PIN_NUMBER;
    }

    setPinFunction(pinNumber, PIN_CONFIG_FUNCTION_OUTPUT);
    const uint8_t pinFunction = readPinFunction(pinNumber);
    if (pinFunction != PIN_CONFIG_FUNCTION_OUTPUT) {
        return PIN_CONTROLLER_ERROR_PIN_FUNCTION;
    }

    *ioReference = getPinBitField(pinNumber);

    return PIN_CONTROLLER_ERROR_NO;

}

PIN_CONTROLLER_ERROR outputPinClose(const uint8_t pinNumber) {

    setPinFunction(pinNumber, PIN_CONFIG_FUNCTION_INPUT);
    const uint8_t pinFunction = readPinFunction(pinNumber);
    if (pinFunction != PIN_CONFIG_FUNCTION_INPUT) {
        return PIN_CONTROLLER_ERROR_PIN_FUNCTION;
    }

    return PIN_CONTROLLER_ERROR_NO;

}

int readPinLevel(const uint32_t ioReference) {

    uint32_t pinLevel = readPin(ioReference);
    if (pinLevel > 0) {
        return PIN_CONTROLLER_PIN_LEVEL_HIGH;
    } else {
        return PIN_CONTROLLER_PIN_LEVEL_LOW;
    }

}

void outputPinWrite(const uint32_t ioReference) {

    setPin(ioReference);

}

void outputPinClear(const uint32_t ioReference) {

    clearPin(ioReference);

}

int outputPinRead(const uint32_t ioReference) {

    return readPinLevel(ioReference);

}