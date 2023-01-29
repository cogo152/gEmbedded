//
// Created by sondahi on 23.01.23.
//

#ifndef GEMBEDDED_C_PIN_H
#define GEMBEDDED_C_PIN_H

#include "common.h"
#include "pthread.h"

typedef struct {
    int number;
    int level;
    uint32_t reference;
    int status;
    pthread_mutex_t mutex;

} output_pin_t;

typedef struct {
    int number;
    uint8_t pullUpDown;
    int level;
    uint32_t reference;
    int status;
    pthread_mutex_t mutex;
} input_pin_t;

typedef struct {
    int number;
    int cevent;
    int revent;
    int timeoutInMilSec;
    uint64_t timeStamp;
    int reference;
    int status;
    pthread_mutex_t mutex;
} listener_pin_t;

#endif //GEMBEDDED_C_PIN_H
