//
// Created by sondahi on 26.02.23.
//

#ifndef GEMBEDDED_C_PIN_CONTROLLER_H
#define GEMBEDDED_C_PIN_CONTROLLER_H

#include "common.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    PIN_CONTROLLER_ERROR_NO = 0,
    PIN_CONTROLLER_ERROR_INIT_MAP = 101,
    PIN_CONTROLLER_ERROR_DESTROY_UNMAP = 102,
    PIN_CONTROLLER_ERROR_PIN_NUMBER = 103,
    PIN_CONTROLLER_ERROR_PIN_FUNCTION = 104,
    PIN_CONTROLLER_ERROR_PIN_PULLUPDOWN = 105,
    PIN_CONTROLLER_ERROR_PIN_EVENT = 106,
    PIN_CONTROLLER_ERROR_PIN_EVENT_TIMEOUT = 107,
    PIN_CONTROLLER_ERROR_FILE = 108,
    PIN_CONTROLLER_ERROR_IOCTL = 109,
    PIN_CONTROLLER_ERROR_POLL = 110
} PIN_CONTROLLER_ERROR;

typedef struct {
    int event;
    uint64_t timeStamp;
} pin_event_t;

PIN_CONTROLLER_ERROR pinControllerInit();

PIN_CONTROLLER_ERROR pinControllerDestroy();

PIN_CONTROLLER_ERROR outputPinOpen(uint8_t pinNumber, uint32_t *ioReference);

PIN_CONTROLLER_ERROR outputPinClose(uint8_t pinNumber);

void outputPinWrite(uint32_t ioReference);

void outputPinClear(uint32_t ioReference);

int outputPinRead(uint32_t ioReference);

PIN_CONTROLLER_ERROR inputPinOpen(uint8_t pinNumber, uint8_t pinPullUpDown, uint32_t *ioReference);

PIN_CONTROLLER_ERROR inputPinClose(uint8_t pinNumber);

int inputPinRead(uint32_t ioReference);

PIN_CONTROLLER_ERROR
listenerPinOpen(uint8_t pinNumber, uint8_t pinEvent, int timeoutInMilSec, int *ioReference);

PIN_CONTROLLER_ERROR listenerPinClose(int ioReference, uint8_t pinNumber);

PIN_CONTROLLER_ERROR listenerPinRead(int ioReference, int timeoutInMilSec, pin_event_t *pinEvent);

#define PIN_CONTROLLER_PIN_LEVEL_HIGH               (1)
#define PIN_CONTROLLER_PIN_LEVEL_LOW                (0)
#define PIN_CONTROLLER_PIN_EVENT_RISING             (1)
#define PIN_CONTROLLER_PIN_EVENT_FALLING            (0)

#ifdef __cplusplus
}
#endif
#endif //GEMBEDDED_C_PIN_CONTROLLER_H
