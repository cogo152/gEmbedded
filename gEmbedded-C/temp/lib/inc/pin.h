//
// Created by sondahi on 17.12.22.
//

#ifndef GEMBEDDED_C_PIN_H
#define GEMBEDDED_C_PIN_H

#include "common.h"
#include "deviceregisters.h"

#define MAX_PIN_LENGTH  (32)

typedef enum {
    PIN_SUCCESS = 0,
    PIN_ERROR = 1,
} PIN_STATUS;

typedef enum {
    PIN_FUNCTION_SUCCESS = 2,
    PIN_FUNCTION_ERROR = 3
} PIN_FUNCTION_STATUS;

typedef enum {
    PULL_UP_DOWN_SUCCESS = 4,
    PULL_UP_DOWN_ERROR = 5,
} PULL_UP_DOWN_STATUS;

// InDeviceContextLock
PIN_STATUS validatePin(PIN_TYPE pinType, PIN pinToValidate);

// InDeviceContextLock
PIN_STATUS registerPin(PIN validatedPin);

// InDeviceContextLock
PIN_FUNCTION_STATUS
configurePinFunction(PIN validatedPin, PIN_FUNCTION pinFunctionToConfigure, struct PinConfigRegs *pinConfigRegs);

// InDeviceContextLock
PIN_FUNCTION_STATUS
readPinFunction(PIN validatedPin, PIN_FUNCTION *pinFunctionToRead, struct PinConfigRegs *pinConfigRegs);

// InDeviceContextLock
PULL_UP_DOWN_STATUS
configurePullUpDown(PIN validatedPin, PULL_UP_DOWN pullUpDownToConfigure, struct PinConfigRegs *pinConfigRegs);

// InDeviceContextLock
PULL_UP_DOWN_STATUS
readPullUpDown(PIN validatedPin, PULL_UP_DOWN *pullUpDownToRead, struct PinConfigRegs *pinConfigRegs);

#endif //GEMBEDDED_C_PIN_H
