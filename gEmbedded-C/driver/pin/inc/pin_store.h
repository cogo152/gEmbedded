//
// Created by sondahi on 28.01.23.
//

#ifndef GEMBEDDED_C_PIN_STORE_H
#define GEMBEDDED_C_PIN_STORE_H

#include "pin.h"
#include "pin_exception.h"

typedef union {
    output_pin_t outputPin;
    input_pin_t inputPin;
    listener_pin_t listenerPin;
} pin_t;

int addPin(pin_t pin,int *storeReference);

pin_t *getPin(int storeReference);

void removePin(int storeReference);

#endif //GEMBEDDED_C_PIN_STORE_H
