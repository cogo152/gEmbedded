//
// Created by sondahi on 29.12.22.
//

#ifndef GEMBEDDED_C_PINIODRIVER_H
#define GEMBEDDED_C_PINIODRIVER_H

#include "common.h"
#include "pin.h"

#define SET_OFFSET  (0x1c/4)
#define CLR_OFFSET  (0x28/4)
#define LEV_OFFSET  (0x34/4)
#define EDS_OFFSET  (0x40/4)

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

uint32_t getPinIOBitField(PIN validatedPin);

void setPin(uint32_t bitField);

void clearPin(uint32_t bitField);

uint8_t readPinLevel(uint32_t bitField);

void invokePinEvent(uint32_t bitField);

PIN_IO_STATUS pollPinEvent(struct pinevent *pinEvent);

#endif //GEMBEDDED_C_PINIODRIVER_H
