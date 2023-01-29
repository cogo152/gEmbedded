//
// Created by sondahi on 29.01.23.
//

#ifndef GEMBEDDED_C_PIN_CONTROLLER_H
#define GEMBEDDED_C_PIN_CONTROLLER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "common.h"
#include "pin_exception.h"

int pinControllerSetup(void);

int pintControllerShutdown(void);

int outputPinOpen(int pinNumber, int *reference);

int outputPinSet(int reference);

int outputPinRead(int reference, int *level);

int outputPinClear(int reference);

int outputPinClose(int reference);

#ifdef __cplusplus
}
#endif
#endif //GEMBEDDED_C_PIN_CONTROLLER_H
