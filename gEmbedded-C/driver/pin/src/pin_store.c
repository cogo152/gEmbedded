//
// Created by sondahi on 28.01.23.
//

#include <stdlib.h>

#include "pin_store.h"

static pin_t *pinStore;
static volatile int storeSize = 0;
static volatile int storeIndex = -1;

int initPinStore() {

    storeSize = PIN_STORE_INCREMENT_SIZE;

    pinStore = (pin_t *) malloc(storeSize * sizeof(pin_t));
    if (pinStore == NULL) {
        return PIN_STORE_EXCEPTION_INIT_ERROR;
    }

    for (int i = 0; i < storeSize; ++i) {
        pin_t *pin = &pinStore[i];
        pin->cNumber = PIN_STORE_INITIAL_PIN_NUMBER;
    }

    storeIndex = 0;

    return PIN_STORE_EXCEPTION_NO_ERROR;
}

void destroyPinStore() {

    free(pinStore);
    storeSize = 0;
    storeIndex = -1;

}

int isPinAdded(pin_t *const pin) {

    for (int i = 0; i < storeSize; ++i) {
        pin_t *_pin = &pinStore[i];
        if (_pin->cNumber == pin->cNumber) {
            return PIN_STORE_PIN_ADDED;
        }
    }

    return PIN_STORE_PIN_NOT_ADDED;

}

int addPin(const pin_t pin, int *const storeReference) {

    for (int i = 0; i < storeSize; ++i) {
        pin_t *const _pin = &pinStore[i];
        if (_pin->cNumber == PIN_STORE_REUSABLE_PIN_NUMBER) {
            pinStore[i] = pin;
            *storeReference = i;
            return PIN_STORE_EXCEPTION_NO_ERROR;
        }
    }

    if (storeIndex == storeSize) {
        storeSize += PIN_STORE_INCREMENT_SIZE;
        pinStore = (pin_t *) realloc(pinStore, storeSize * sizeof(pin_t));
        if (pinStore == NULL) {
            return PIN_STORE_EXCEPTION_ADD_ERROR;
        }
    }

    pinStore[storeIndex] = pin;
    *storeReference = storeIndex;
    ++storeIndex;

    return PIN_STORE_EXCEPTION_NO_ERROR;

}

pin_t *getPin(const int storeReference) {

    return &pinStore[storeReference];

}

void removePin(int storeReference) {

    pin_t *const pin = &pinStore[storeReference];
    pin->cNumber = PIN_STORE_REUSABLE_PIN_NUMBER;

}