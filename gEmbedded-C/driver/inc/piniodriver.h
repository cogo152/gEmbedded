//
// Created by sondahi on 29.12.22.
//

#ifndef GEMBEDDED_C_PINIODRIVER_H
#define GEMBEDDED_C_PINIODRIVER_H

#include "common.h"
#include "pin.h"

typedef enum {
    PIN_IO_SUCCESS = 0,
    PIN_IO_ERROR = 1,
} PIN_IO_STATUS;

typedef enum {
    PIN_EVENT_RESULT_RISING = 0,
    PIN_EVENT_RESULT_FALLING = 1,
    PIN_EVENT_RESULT_TIMEOUT = 2
} PIN_EVENT_RESULT;

struct pinevent {
    int fileDescriptor;
    int timeoutInMilSec;
    PIN_EVENT_RESULT result;
    uint64_t timestamp;
};

PIN_IO_STATUS setupPinIODriver(void);

PIN_IO_STATUS shutdownPinIODriver(void);

PIN_IO_STATUS setPin(PIN validatedPin);

PIN_IO_STATUS clearPin(PIN validatedPin);

PIN_IO_STATUS readPinLevel(PIN validatedPin, uint8_t *pinLevelToRead);

PIN_IO_STATUS invokePinEvent(PIN validatedPin);

PIN_IO_STATUS pollPinEvent(struct pinevent *pinEvent);

#endif //GEMBEDDED_C_PINIODRIVER_H
