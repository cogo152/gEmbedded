//
// Created by sondahi on 29.01.23.
//

#ifndef GEMBEDDED_C_PIN_SESSION_H
#define GEMBEDDED_C_PIN_SESSION_H

#include "pin.h"

#define PIN_SESSION_ERROR_NO        (0)
#define PIN_SESSION_ERROR_INIT      (-1)
#define PIN_SESSION_ERROR_DESTROY   (-2)
#define PIN_SESSION_ERROR_LOCK      (-3)
#define PIN_SESSION_ERROR_UNLOCK    (-4)

int lockPinConfigSession(void );

int unlockPinConfigSession(void );

int initPinIOSession(pin_t *pin);

int destroyPinIOSession(pin_t *pin);

int lockPinIOSession(pin_t *pin);

int unlockPinIOSession(pin_t *pin);

#endif //GEMBEDDED_C_PIN_SESSION_H
