//
// Created by sondahi on 23.01.23.
//

#ifndef GEMBEDDED_C_PIN_H
#define GEMBEDDED_C_PIN_H

#include "common.h"
#include "pthread.h"

#define PIN_STATE_ELIGIBLE                          (1)
#define PIN_STATE_INELIGIBLE                        (0)

typedef struct {
    pthread_mutex_t sLock;
    int sState;
    uint8_t cNumber;
    uint8_t cFunction;
    uint8_t cPullUpDown;
    uint8_t cEvent;
    int cEventTimeout;
    uint32_t ioReference;
    uint32_t ioLevel;
    int ioEvent;
    uint64_t ioTimeStamp;
} pin_t;

#endif //GEMBEDDED_C_PIN_H
