//
// Created by sondahi on 28.02.23.
//

#ifndef GEMBEDDED_C_PIN_STORE_H
#define GEMBEDDED_C_PIN_STORE_H

#include "common.h"
#include "peripheral.h"

typedef enum {
    PIN_STORE_ERROR_NO = 0,
    PIN_STORE_ERROR_MALLOC = 1200
} PIN_STORE_ERROR;


typedef struct {
    uint32_t ioReference;
    uint8_t type;
    uint8_t number;
} pin_t;

PIN_STORE_ERROR initPinStore(void);

void destroyPinStore(void);

int isPinStored(uint8_t pinNumber);

void storePin(pin_t * pin, size_t* storeReference);

pin_t* getPin(size_t storeReference);

void removePin(int storeReference);

#define PIN_STORE_MIN_SIZE                  (2)
#define PIN_STORE_INC_SIZE                  (2)
#define PIN_STORE_MAX_SIZE                  (MAX_GPIO_PIN_SIZE)

#endif //GEMBEDDED_C_PIN_STORE_H
