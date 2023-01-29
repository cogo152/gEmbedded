//
// Created by sondahi on 29.01.23.
//

#ifndef GEMBEDDED_C_PIN_SESSION_H
#define GEMBEDDED_C_PIN_SESSION_H

#include <pthread.h>

#include "pin_exception.h"

int initSession(pthread_mutex_t *mutex);

int lockSession(pthread_mutex_t *mutex);

int unlockSession(pthread_mutex_t *mutex);

int destroySession(pthread_mutex_t *mutex);

#endif //GEMBEDDED_C_PIN_SESSION_H
