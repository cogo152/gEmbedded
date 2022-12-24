//
// Created by sondahi on 17.12.22.
//

#ifndef GEMBEDDED_C_PINDRIVER_H
#define GEMBEDDED_C_PINDRIVER_H

#include "common.h"

typedef enum {
    PIN_CONFIG_SUCCESS = 0,
    PIN_CONFIG_ERROR = 1
} PIN_CONFIG_STATUS;

typedef enum {
    PIN_IO_SUCCESS = 0,
    PIN_IO_ERROR = 1
} PIN_IO_STATUS;

typedef enum {
    PIN_LOW = 0,
    PIN_HIGH = 1
} PIN_LEVEL;

// Thread Safe
PIN_CONFIG_STATUS configureInputPin(PIN inputPin, PULL_UP_DOWN pullUpDown);
// Thread Safe
PIN_IO_STATUS readInputPin(PIN validatedPin, PIN_LEVEL *pinLevelToRead);

#endif //GEMBEDDED_C_PINDRIVER_H
