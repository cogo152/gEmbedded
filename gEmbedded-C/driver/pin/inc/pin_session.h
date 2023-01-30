//
// Created by sondahi on 29.01.23.
//

#ifndef GEMBEDDED_C_PIN_SESSION_H
#define GEMBEDDED_C_PIN_SESSION_H

#include "pin.h"
#include "pin_status.h"


int initSession(pin_t *pin);

int lockSession(pin_t *pin);

int unlockSession(pin_t *pin);

int destroySession(pin_t *pin);

#endif //GEMBEDDED_C_PIN_SESSION_H
