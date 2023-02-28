//
// Created by sondahi on 28.02.23.
//

#include <malloc.h>
#include "pin_store.h"

static pin_t **store = NULL;
static volatile size_t storeSize;
static volatile size_t storeIndex;

PIN_STORE_ERROR initPinStore(void) {

    store = (pin_t **) malloc(sizeof(pin_t *) * PIN_STORE_MIN_SIZE);
    if (store == NULL) {
        return PIN_STORE_ERROR_MALLOC;
    }

    storeSize = PIN_STORE_MIN_SIZE;
    storeIndex = 0;

    for (size_t i = 0; i < storeSize; ++i) {
        store[i] = NULL;
    }

    return PIN_STORE_ERROR_NO;

}


void destroyPinStore(void) {

    for (size_t i = 0; i < storeSize; ++i) {
        free(store[i]);
    }

    free(store);

}

int isPinStored(uint8_t pinNumber) {

    for (size_t i = 0; i < storeSize; ++i) {
        pin_t *pPin = store[i];
        if (pPin != NULL) {
            if (pPin->number == pinNumber) {
                return 1;
            }
        }
    }

    return 0;
}

void storePin(pin_t *pPin, size_t *storeReference) {

    for (size_t i = 0; i < storeSize; ++i) {
        if (store[i] == NULL) {
            store[i] = (pin_t *) malloc(sizeof(pin_t));
            *store[i] = *pPin;
            *storeReference = i;
            return;
        }
    }

}

pin_t *getPin(size_t storeReference) {

    return store[storeReference];

}

void removePin(int storeReference) {

    free(store[storeReference]);
    store[storeReference] = NULL;

}