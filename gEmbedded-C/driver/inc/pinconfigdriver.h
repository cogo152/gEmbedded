//
// Created by sondahi on 29.12.22.
//

#ifndef GEMBEDDED_C_PINCONFIGDRIVER_H
#define GEMBEDDED_C_PINCONFIGDRIVER_H

#include "common.h"
#include "pin.h"

#define FSEL_OFFSET     (0x00/4)
#define REN_OFFSET      (0x4c/4)
#define FEN_OFFSET      (0x58/4)
#define HEN_OFFSET      (0x64/4)
#define LEN_OFFSET      (0x70/4)
#define AREN_OFFSET     (0x7c/4)
#define AFEN_OFFSET     (0x88/4)
#define PUP_PDN_OFFSET  (0xe4/4)

typedef enum {
    PIN_CONFIG_SUCCESS = 0,
    PIN_CONFIG_ERROR = 1,
} PIN_CONFIG_STATUS;

PIN_CONFIG_STATUS setupPinConfigDriver(void);

PIN_CONFIG_STATUS shutdownPinConfigDriver(void);

PIN_CONFIG_STATUS configurePinFunction(PIN validatedPin, PIN_FUNCTION validatedPinFunction);

PIN_CONFIG_STATUS readPinFunction(PIN validatedPin, PIN_FUNCTION *pinFunctionToRead);

PIN_CONFIG_STATUS configurePinPullUpDown(PIN validatedPin, PULL_UP_DOWN validatedPinPullUpDown);

PIN_CONFIG_STATUS readPinPullUpDown(PIN validatedPin, PULL_UP_DOWN *pinPullUpDownToRead);

PIN_CONFIG_STATUS configurePinEvent(PIN validatedPin, PIN_EVENT validatedPinEvent);

PIN_CONFIG_STATUS configurePinEventLFS(PIN validatedPin, PIN_EVENT validatedPinEvent, int *fileDescriptor);

PIN_CONFIG_STATUS readPinEvent(PIN validatedPin, PIN_EVENT *pinEventToRead);

PIN_CONFIG_STATUS releasePinEvent(int fileDescriptor);

#endif //GEMBEDDED_C_PINCONFIGDRIVER_H
