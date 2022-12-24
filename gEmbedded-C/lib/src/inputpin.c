//
// Created by sondahi on 17.12.22.
//

#include "pindriver.h"
#include "pin.h"
#include "deviceregisters.h"

PIN_CONFIG_STATUS configureInputPin(PIN inputPin, PULL_UP_DOWN pullUpDown) {

    const PIN_STATUS pinValidationStatus = validatePin(PIN_TYPE_GPIO, inputPin);
    if (pinValidationStatus == PIN_ERROR) {
        return PIN_CONFIG_ERROR;
    }

    struct PinConfigRegs *pinConfigRegs;

    DEVICE_CONTEXT_STATUS  deviceRegisterStatus = requestPinConfigRegs(&pinConfigRegs);
    if (deviceRegisterStatus == DEVICE_CONTEXT_REGISTER_ERROR) {
        return PIN_CONFIG_ERROR;
    }

    const PIN_FUNCTION_STATUS pinFunctionStatus = configurePinFunction(inputPin, PIN_FUNCTION_INPUT, pinConfigRegs);
    if (pinFunctionStatus == PIN_FUNCTION_ERROR) {
        return PIN_CONFIG_ERROR;
    }

    const PULL_UP_DOWN_STATUS pullUpDownStatus = configurePullUpDown(inputPin, pullUpDown, pinConfigRegs);
    if (pullUpDownStatus == PULL_UP_DOWN_ERROR) {
        return PIN_CONFIG_ERROR;
    }

    PIN_STATUS pinRegistrationStatus = registerPin(inputPin);
    if (pinRegistrationStatus == PIN_ERROR) {
        return PIN_CONFIG_ERROR;
    }

    return PIN_CONFIG_SUCCESS;

}

PIN_IO_STATUS readInputPin(PIN validatedPin, PIN_LEVEL *pinLevelToRead) {

}