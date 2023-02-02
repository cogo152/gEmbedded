//
// Created by sondahi on 29.01.23.
//

#ifndef GEMBEDDED_C_PIN_SESSION_H
#define GEMBEDDED_C_PIN_SESSION_H

#include "pin.h"


#define PIN_SESSION_EXCEPTION_NO_ERROR          (0)
#define PIN_SESSION_EXCEPTION_INIT_ERROR        (-1)
#define PIN_SESSION_EXCEPTION_LOCK_ERROR        (-2)
#define PIN_SESSION_EXCEPTION_UNLOCK_ERROR      (-3)
#define PIN_SESSION_EXCEPTION_DESTROY_ERROR     (-4)

int initSession(pin_t *pin);

int lockSession(pin_t *pin);

int unlockSession(pin_t *pin);

int destroySession(pin_t *pin);

#endif //GEMBEDDED_C_PIN_SESSION_H
