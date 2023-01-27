//
// Created by sondahi on 23.01.23.
//

#ifndef GEMBEDDED_C_PIN_H
#define GEMBEDDED_C_PIN_H

#include "common.h"

typedef struct output_pin {
    uint8_t number;
    uint8_t level;
    uint32_t reference;
    volatile uint32_t status;
} output_pin_t;

typedef struct input_pin {
    uint8_t number;
    uint8_t pullUpDown;
    uint8_t level;
    volatile uint8_t status;
    uint32_t reference;
} input_pin_t;

typedef struct listener_pin {
    uint8_t number;
    uint8_t cevent;
    uint8_t revent;
    volatile uint8_t status;
    int reference;
    int timeoutInMilSec;
    uint64_t timeStamp;
} listener_pin_t;

#endif //GEMBEDDED_C_PIN_H
