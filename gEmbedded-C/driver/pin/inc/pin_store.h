//
// Created by sondahi on 28.01.23.
//

#ifndef GEMBEDDED_C_PIN_STORE_H
#define GEMBEDDED_C_PIN_STORE_H

#include "pin.h"

#define PIN_STORE_ERROR_NO                  (0)
#define PIN_STORE_ERROR_MALLOC              (-1)
#define PIN_STORE_PIN_STATE_ELIGIBLE        (1)
#define PIN_STORE_PIN_STATE_INELIGIBLE      (0)
#define PIN_STORE_TRUE                      (1)
#define PIN_STORE_FALSE                     (0)

#define PIN_STORE_INCREMENT_SIZE            (2)
#define PIN_STORE_PIN_INITIAL_NUMBER        (32)

int initPinStore();

void isPinStoreInitialized(int *pinStoreInitialized);

void destroyPinStore();

void isPinAdded(uint8_t pinNumber, int *pinAdded);

int addPin(pin_t pin, int *storeReference);

pin_t *getPin(int storeReference);

void removePin(int storeReference);

const int *getClosablePinReferences(int *length);

void releaseClosablePinReferences(const int *closablePinReferences);

#endif //GEMBEDDED_C_PIN_STORE_H
