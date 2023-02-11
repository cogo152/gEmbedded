//
// Created by sondahi on 29.01.23.
//

#include <pthread.h>

#include "pin_session.h"

static pthread_mutex_t cLock = PTHREAD_MUTEX_INITIALIZER;

int lockPinConfigSession(void) {

    const int status = pthread_mutex_lock(&cLock);
    if (status != 0) {
        return PIN_SESSION_ERROR_LOCK;
    }

    return PIN_SESSION_ERROR_NO;

}

int unlockPinConfigSession(void) {

    const int status = pthread_mutex_unlock(&cLock);
    if (status != 0) {
        return PIN_SESSION_ERROR_UNLOCK;
    }

    return PIN_SESSION_ERROR_NO;

}

int initPinIOSession(pin_t *const pin) {

    const int status = pthread_mutex_init(&pin->ioLock, NULL);
    if (status != 0) {
        return PIN_SESSION_ERROR_INIT;
    }

    return PIN_SESSION_ERROR_NO;

}

int destroyPinIOSession(pin_t *const pin) {

    const int status = pthread_mutex_destroy(&pin->ioLock);
    if (status != 0) {
        return PIN_SESSION_ERROR_DESTROY;
    }

    return PIN_SESSION_ERROR_NO;

}

int lockPinIOSession(pin_t *const pin) {

    const int status = pthread_mutex_lock(&pin->ioLock);
    if (status != 0) {
        return PIN_SESSION_ERROR_LOCK;
    }

    return PIN_SESSION_ERROR_NO;

}

int unlockPinIOSession(pin_t *const pin) {

    const int status = pthread_mutex_unlock(&pin->ioLock);
    if (status != 0) {
        return PIN_SESSION_ERROR_UNLOCK;
    }

    return PIN_SESSION_ERROR_NO;

}