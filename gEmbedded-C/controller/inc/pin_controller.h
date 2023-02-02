//
// Created by sondahi on 29.01.23.
//

#ifndef GEMBEDDED_C_PIN_CONTROLLER_H
#define GEMBEDDED_C_PIN_CONTROLLER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "common.h"

#define PIN_CONTROLLER_EXCEPTION_NO_ERROR           (0)
#define PIN_CONTROLLER_INITIALIZED_ERROR            (-1)
#define PIN_DRIVER_NOT_INITIALIZED_ERROR            (-2)

int setupPinController(void);

int shutdownPinController(void);

int openOutputPin(int pinNumber, int *reference);

int setOutputPinHigh(int reference);

int readOutputPinLevel(int reference, int *level);

int setOutputLow(int reference);

int closeOutputPin(int reference);

#ifdef __cplusplus
}
#endif
#endif //GEMBEDDED_C_PIN_CONTROLLER_H
