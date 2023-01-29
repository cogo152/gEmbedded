//
// Created by sondahi on 28.01.23.
//

#include "pin_store.h"

static pin_t registeredPins[12];

int addPin(const pin_t pin, int *const storeReference) {

    static volatile int index = 0;

    registeredPins[index] = pin;
    *storeReference = index;
    ++index;

    return PIN_STORE_EXCEPTION_NO_ERROR;

}

pin_t *getPin(int storeReference) {

    return &registeredPins[storeReference];

}

void removePin(int storeReference) {
    // TODO
}