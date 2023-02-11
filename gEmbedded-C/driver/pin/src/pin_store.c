//
// Created by sondahi on 28.01.23.
//

#include <stdlib.h>

#include "pin_store.h"

static pin_t *pinStore = NULL;
static volatile int storeSize = 0;
static volatile int storeIndex = -1;

int initPinStore() {

    storeSize = PIN_STORE_INCREMENT_SIZE;

    pinStore = (pin_t *) malloc(storeSize * sizeof(pin_t));
    if (pinStore == NULL) {
        return PIN_STORE_ERROR_MALLOC;
    }

    for (int i = 0; i < storeSize; ++i) {
        pin_t *pin = &pinStore[i];
        pin->cNumber = 99;
        pin->sState = PIN_STORE_PIN_STATE_ELIGIBLE;
    }

    storeIndex = 0;

    return PIN_STORE_ERROR_NO;
}

void destroyPinStore() {

    free((void *) pinStore);
    storeSize = 0;
    storeIndex = -1;

    pinStore = NULL;

}

int isPinAdded(const uint8_t pinNumber) {

    for (int i = 0; i < storeSize; ++i) {
        pin_t *const _pin = &pinStore[i];
        if (_pin->cNumber == pinNumber) {
            if (_pin->sState == PIN_STORE_PIN_STATE_INELIGIBLE) {
                return PIN_STORE_PIN_ADDED;
            } else {
                return PIN_STORE_PIN_NOT_ADDED;
            }
        }
    }

    return PIN_STORE_PIN_NOT_ADDED;

}

int addPin(pin_t pin, int *const storeReference) {

    for (int i = 0; i < storeSize; ++i) {
        pin_t *const _pin = &pinStore[i];
        if (_pin->cNumber == pin.cNumber) {
            pin.sState = PIN_STORE_PIN_STATE_INELIGIBLE;
            pinStore[i] = pin;
            *storeReference = i;
            return PIN_STORE_ERROR_NO;
        }
    }

    if (storeIndex == storeSize) {
        storeSize += PIN_STORE_INCREMENT_SIZE;
        pinStore = (pin_t *) realloc(pinStore, storeSize * sizeof(pin_t));
        if (pinStore == NULL) {
            return PIN_STORE_ERROR_MALLOC;
        }
        for (int i = storeIndex; i < storeSize; ++i) {
            pin_t *_pin = &pinStore[i];
            _pin->cNumber = 99;
            _pin->sState = PIN_STORE_PIN_STATE_ELIGIBLE;
        }
    }

    pin.sState = PIN_STORE_PIN_STATE_INELIGIBLE;
    pinStore[storeIndex] = pin;
    *storeReference = storeIndex;
    ++storeIndex;

    return PIN_STORE_ERROR_NO;

}

pin_t *getPin(const int storeReference) {

    return &pinStore[storeReference];

}

void removePin(const int storeReference) {

    pin_t *const pin = &pinStore[storeReference];
    pin->sState = PIN_STORE_PIN_STATE_ELIGIBLE;

}

const int *getUsablePins(int *const size) {

    int eligiblePinSize = 0;

    for (int i = 0; i < storeSize; ++i) {
        pin_t *const pin = &pinStore[i];
        if (pin->sState == PIN_STORE_PIN_STATE_INELIGIBLE) {
            ++eligiblePinSize;
        }
    }

    if (eligiblePinSize == 0) {
        return NULL;
    }

    int *eligiblePins = (int *) malloc(eligiblePinSize * sizeof(int));

    int eligibleIndex = 0;

    for (int i = 0; i < storeSize; ++i) {
        pin_t *pin = &pinStore[i];
        if (pin->sState == PIN_STORE_PIN_STATE_INELIGIBLE) {
            eligiblePins[eligibleIndex] = i;
            ++eligibleIndex;
        }
    }

    *size = eligiblePinSize;

    return eligiblePins;

}

void releaseUsablePins(const int *const eligiblePins) {

    free((void *) eligiblePins);

}