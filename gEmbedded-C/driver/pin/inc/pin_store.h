//
// Created by sondahi on 28.01.23.
//

#ifndef GEMBEDDED_C_PIN_STORE_H
#define GEMBEDDED_C_PIN_STORE_H

#include "pin.h"
#include "pin_status.h"

int addPin(pin_t pin, int *storeReference);

pin_t *getPin(int storeReference);

void removePin(int storeReference);

#endif //GEMBEDDED_C_PIN_STORE_H
