//
// Created by sondahi on 04.01.23.
//

#ifndef GEMBEDDED_C_SESSION_H
#define GEMBEDDED_C_SESSION_H

#include <pthread.h>

#include "common.h"

struct session {
    pthread_mutex_t configLock;     // singleton
    pthread_mutex_t ioLock;         // prior to io
    volatile uint8_t configActive;  // if false can not reach driver
    volatile uint8_t ioActive;       // if false can not reach driver
};

#endif //GEMBEDDED_C_SESSION_H
