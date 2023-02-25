//
// Created by sondahi on 05.02.23.
//

#ifndef GEMBEDDED_C_PIN_CONTROLLER_H
#define GEMBEDDED_C_PIN_CONTROLLER_H

#include "common.h"

#ifdef __cplusplus
extern "C" {
#endif

#define PIN_CONTROLLER_ERROR_NO                     (0)
#define PIN_CONTROLLER_ERROR_LOCK                   (-1)
#define PIN_CONTROLLER_ERROR_UNLOCK                 (-2)
#define PIN_CONTROLLER_ERROR_STATE                  (-3)
#define PIN_CONTROLLER_ERROR_DRIVER                 (-4)
#define PIN_CONTROLLER_ERROR_STORE                  (-5)
#define PIN_CONTROLLER_ERROR_PIN_CLOSE              (-6)
#define PIN_CONTROLLER_ERROR_CONFIG_LOCK            (-7)
#define PIN_CONTROLLER_ERROR_CONFIG_UNLOCK          (-8)
#define PIN_CONTROLLER_ERROR_PIN_OPENED             (-9)
#define PIN_CONTROLLER_ERROR_PIN_CLOSED             (-10)
#define PIN_CONTROLLER_ERROR_PIN_VALIDATION         (-11)
#define PIN_CONTROLLER_ERROR_PIN_INIT               (-12)
#define PIN_CONTROLLER_ERROR_PIN_DESTROY            (-13)
#define PIN_CONTROLLER_ERROR_PIN_SESSION_INIT       (-14)
#define PIN_CONTROLLER_ERROR_PIN_SESSION_DESTROY    (-15)
#define PIN_CONTROLLER_ERROR_PIN_ADD                (-16)
#define PIN_CONTROLLER_ERROR_IO_LOCK                (-17)
#define PIN_CONTROLLER_ERROR_IO_UNLOCK              (-18)

#define PIN_CONTROLLER_PIN_LEVEL_HIGH               (1)
#define PIN_CONTROLLER_PIN_LEVEL_LOW                (0)


#define PIN_CONTROLLER_TRUE     (1)
#define PIN_CONTROLLER_FALSE    (0)

int pinControllerInit();

int pinControllerDestroy();

int outputPinOpen(uint8_t pinNumber, int *reference);

int outputPinClose(int reference);

int outputPinWrite(int reference);

int outputPinClear(int reference);

int outputPinRead(int reference, int *pinLevel);

#ifdef __cplusplus
}
#endif
#endif //GEMBEDDED_C_PIN_CONTROLLER_H
