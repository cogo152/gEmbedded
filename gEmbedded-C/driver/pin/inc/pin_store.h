//
// Created by sondahi on 28.01.23.
//

#ifndef GEMBEDDED_C_PIN_STORE_H
#define GEMBEDDED_C_PIN_STORE_H

#include "pin.h"

#define PIN_STORE_INCREMENT_SIZE            (2)

#define PIN_STORE_ERROR_NO                  (0)
#define PIN_STORE_ERROR_INIT                (-1)
#define PIN_STORE_ERROR_DESTROY             (-2)
#define PIN_STORE_ERROR_MALLOC              (-3)

#define PIN_STORE_PIN_ADDED                 (1U)
#define PIN_STORE_PIN_NOT_ADDED             (0U)

#define PIN_STORE_PIN_STATE_ELIGIBLE        (1)
#define PIN_STORE_PIN_STATE_INELIGIBLE      (0)

int initPinStore();

void destroyPinStore();

int isPinAdded(uint8_t pinNumber);

int addPin(pin_t pin, int *storeReference);

pin_t *getPin(int storeReference);

void removePin(int storeReference);

const int *getUsablePins(int *size);

void releaseUsablePins(const int *eligiblePins);

#endif //GEMBEDDED_C_PIN_STORE_H
