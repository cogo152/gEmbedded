//
// Created by sondahi on 28.01.23.
//

#include <stdlib.h>

#include "pin_store.h"

static volatile int initialized = PIN_STORE_FALSE;
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
        pin_t *const pin = &pinStore[i];
        pin->cNumber = PIN_STORE_PIN_INITIAL_NUMBER;
        pin->sState = PIN_STORE_PIN_STATE_ELIGIBLE;
    }

    storeIndex = 0;

    initialized = PIN_STORE_TRUE;

    return PIN_STORE_ERROR_NO;
}

void isPinStoreInitialized(int *pinStoreInitialized){

    *pinStoreInitialized = initialized;

}

void destroyPinStore() {

    free((void *) pinStore);
    storeSize = 0;
    storeIndex = -1;

    pinStore = NULL;

    initialized = PIN_STORE_FALSE;

}

void isPinAdded(const uint8_t pinNumber, int *const pinAdded) {

    for (int i = 0; i < storeSize; ++i) {
        pin_t *const pin = &pinStore[i];
        if (pin->cNumber == pinNumber) {
            if (pin->sState == PIN_STORE_PIN_STATE_INELIGIBLE) {
                *pinAdded = PIN_STORE_TRUE;
                return;
            } else {
                *pinAdded = PIN_STORE_FALSE;
                return;
            }
        }
    }

    *pinAdded = PIN_STORE_FALSE;

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
            _pin->cNumber = PIN_STORE_PIN_INITIAL_NUMBER;
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

const int *getClosablePinReferences(int *const length) {

    int closablePinReferencesLength = 0;

    for (int i = 0; i < storeSize; ++i) {
        pin_t *const pin = &pinStore[i];
        if (pin->sState == PIN_STORE_PIN_STATE_INELIGIBLE) {
            ++closablePinReferencesLength;
        }
    }

    if (closablePinReferencesLength == 0) {
        *length = 0;
        return NULL;
    }

    int *closablePinReferences = (int *) malloc(closablePinReferencesLength * sizeof(int));

    int index = 0;

    for (int i = 0; i < storeSize; ++i) {
        pin_t *pin = &pinStore[i];
        if (pin->sState == PIN_STORE_PIN_STATE_INELIGIBLE) {
            closablePinReferences[index] = i;
            ++index;
        }
    }

    *length = closablePinReferencesLength;

    return closablePinReferences;

}

void releaseClosablePinReferences(const int *const closablePinReferences) {

    free((void *) closablePinReferences);

}