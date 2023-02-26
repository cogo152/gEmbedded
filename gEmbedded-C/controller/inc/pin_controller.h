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
    PIN_CONTROLLER_ERROR_INIT = -1,
    PIN_CONTROLLER_ERROR_DESTROY = -2,
    PIN_CONTROLLER_ERROR_PIN_NUMBER = -3,
    PIN_CONTROLLER_ERROR_PIN_FUNCTION = -4,
    PIN_CONTROLLER_ERROR_PIN_PULLUPDOWN = -5,
} PIN_CONTROLLER_ERROR;

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

#define PIN_CONTROLLER_PIN_LEVEL_HIGH               (1)
#define PIN_CONTROLLER_PIN_LEVEL_LOW                (0)

#ifdef __cplusplus
}
#endif
#endif //GEMBEDDED_C_PIN_CONTROLLER_H
