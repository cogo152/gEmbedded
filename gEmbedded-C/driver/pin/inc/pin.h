//
// Created by sondahi on 23.01.23.
//

#ifndef GEMBEDDED_C_PIN_H
#define GEMBEDDED_C_PIN_H

#include "common.h"
#include "pthread.h"

#define PIN_TYPE_OUTPUT         (1)
#define PIN_TYPE_INPUT          (2)
#define PIN_TYPE_LISTENER       (3)

#define PIN_IO_STATE_ELIGIBLE      (1)
#define PIN_IO_STATE_INELIGIBLE    (0)

typedef struct {
    int type;
    pthread_mutex_t sLock;
    uint8_t cNumber;
    uint8_t cFunction;
    uint8_t cPullUpDown;
    uint8_t cEvent;
    int cEventTimeout;
    int ioState;
    uint32_t ioReference;
    uint32_t ioLevel;
    int ioEvent;
    uint64_t ioTimeStamp;
} pin_t;

#endif //GEMBEDDED_C_PIN_H
