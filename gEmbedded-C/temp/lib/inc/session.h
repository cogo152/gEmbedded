//
// Created by sondahi on 29.12.22.
//

#ifndef GEMBEDDED_C_SESSION_H
#define GEMBEDDED_C_SESSION_H

#include <pthread.h>

#include "common.h"

struct session {
    volatile uint8_t id;
    volatile uint8_t status;
    pthread_mutex_t lock;
};

typedef enum {
    SESSION_SUCCESS = 0,
    SESSION_ERROR=1
} SESSION_STATUS;

SESSION_STATUS initSession(struct session *);
SESSION_STATUS destroySession(struct session *);

SESSION_STATUS lockSession(struct session *);
SESSION_STATUS unlockSession(struct session *);

#endif //GEMBEDDED_C_SESSION_H
