//
// Created by sondahi on 28.01.23.
//

#ifndef GEMBEDDED_C_PIN_STORE_H
#define GEMBEDDED_C_PIN_STORE_H

#include "pin.h"

#define PIN_STORE_INCREMENT_SIZE            (2)
#define PIN_STORE_INITIAL_PIN_NUMBER        (32)
#define PIN_STORE_REUSABLE_PIN_NUMBER       (33)

#define PIN_STORE_EXCEPTION_NO_ERROR        (0)
#define PIN_STORE_EXCEPTION_INIT_ERROR      (-1)
#define PIN_STORE_EXCEPTION_DESTROY_ERROR   (-2)
#define PIN_STORE_EXCEPTION_ADD_ERROR       (-3)

#define PIN_STORE_PIN_ADDED                 (1U)
#define PIN_STORE_PIN_NOT_ADDED             (0U)

#define PIN_STORE_STATE_STORED              (1)
#define PIN_STORE_STATE_NOT_STORED          (0)

int initPinStore();

void destroyPinStore();

int isPinAdded(pin_t *pin);

int addPin(pin_t pin, int *storeReference);

pin_t *getPin(int storeReference);

void removePin(int storeReference);

const int *getUsablePins(int *size);

void releaseUsablePins(const int *eligiblePins);

#endif //GEMBEDDED_C_PIN_STORE_H
