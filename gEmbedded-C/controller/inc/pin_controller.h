//
// Created by sondahi on 26.02.23.
//

#ifndef GEMBEDDED_C_PIN_CONTROLLER_H
#define GEMBEDDED_C_PIN_CONTROLLER_H

#include "common.h"
#include "peripheral.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    PIN_CONTROLLER_ERROR_NO = 0,
    PIN_CONTROLLER_ERROR_INIT_MAP = 130,
    PIN_CONTROLLER_ERROR_DESTROY_UNMAP = 131,
    PIN_CONTROLLER_ERROR_PIN_NUMBER = 132,
    PIN_CONTROLLER_ERROR_PIN_FUNCTION = 133,
    PIN_CONTROLLER_ERROR_PIN_PULLUPDOWN = 134,
    PIN_CONTROLLER_ERROR_PIN_EVENT = 135,
    PIN_CONTROLLER_ERROR_PIN_EVENT_TIMEOUT = 136,
    PIN_CONTROLLER_ERROR_FILE = 137,
    PIN_CONTROLLER_ERROR_IOCTL = 138,
    PIN_CONTROLLER_ERROR_POLL = 139
} PIN_CONTROLLER_ERROR;

#define PIN_CONTROLLER_CONFIG_FUNCTION_OUTPUT           (PIN_CONFIG_FUNCTION_OUTPUT)
#define PIN_CONTROLLER_CONFIG_FUNCTION_INPUT            (PIN_CONFIG_FUNCTION_INPUT)
#define PIN_CONTROLLER_CONFIG_FUNCTION_ALT0             (PIN_CONFIG_FUNCTION_ALT0)
#define PIN_CONTROLLER_CONFIG_FUNCTION_ALT1             (PIN_CONFIG_FUNCTION_ALT1)
#define PIN_CONTROLLER_CONFIG_FUNCTION_ALT2             (PIN_CONFIG_FUNCTION_ALT2)
#define PIN_CONTROLLER_CONFIG_FUNCTION_ALT3             (PIN_CONFIG_FUNCTION_ALT3)
#define PIN_CONTROLLER_CONFIG_FUNCTION_ALT4             (PIN_CONFIG_FUNCTION_ALT4)
#define PIN_CONTROLLER_CONFIG_FUNCTION_ALT5             (PIN_CONFIG_FUNCTION_ALT5)

#define PIN_CONTROLLER_CONFIG_PULLUPDOWN_NO_RESISTOR    (PIN_CONFIG_PULLUPDOWN_NO_RESISTOR)
#define PIN_CONTROLLER_CONFIG_PULLUPDOWN_PULL_UP        (PIN_CONFIG_PULLUPDOWN_PULL_UP)
#define PIN_CONTROLLER_CONFIG_PULLUPDOWN_PULL_DOWN      (PIN_CONFIG_PULLUPDOWN_PULL_DOWN)

#define PIN_CONTROLLER_CONFIG_EVENT_RISING              (PIN_CONFIG_EVENT_RISING)
#define PIN_CONTROLLER_CONFIG_EVENT_FALLING             (PIN_CONFIG_EVENT_FALLING)
#define PIN_CONTROLLER_CONFIG_EVENT_BOTH                (PIN_CONFIG_EVENT_BOTH)

typedef struct pin_event_t {
    int event;
    uint64_t timeStamp;
} pin_event_data;

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
listenerPinOpen(uint8_t pinNumber, uint8_t pinPullUpDown, uint8_t pinEvent, int timeoutInMilSec, int *ioReference);

PIN_CONTROLLER_ERROR listenerPinClose(int ioReference, uint8_t pinNumber);

PIN_CONTROLLER_ERROR listenerPinRead(int ioReference, int timeoutInMilSec, pin_event_data *pinEventData);

#define PIN_CONTROLLER_IO_PIN_LEVEL_HIGH               (1)
#define PIN_CONTROLLER_IO_PIN_LEVEL_LOW                (0)
#define PIN_CONTROLLER_IO_PIN_EVENT_RISING             (1)
#define PIN_CONTROLLER_IO_PIN_EVENT_FALLING            (0)

#ifdef __cplusplus
}
#endif
#endif //GEMBEDDED_C_PIN_CONTROLLER_H
