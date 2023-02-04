//
// Created by sondahi on 29.01.23.
//

#include <pthread.h>

#include "pin_session.h"

static pthread_mutex_t cLock = PTHREAD_MUTEX_INITIALIZER;

int lockPinConfigSession(void ){

    const int status = pthread_mutex_lock(&cLock);
    if (status != 0) {
        return PIN_SESSION_EXCEPTION_LOCK_ERROR;
    }

    return PIN_SESSION_EXCEPTION_NO_ERROR;

}

int unlockPinConfigSession(void ){

    const int status = pthread_mutex_unlock(&cLock);
    if (status != 0) {
        return PIN_SESSION_EXCEPTION_UNLOCK_ERROR;
    }

    return PIN_SESSION_EXCEPTION_NO_ERROR;

}

int initPinIOSession(pin_t *const pin) {

    const int status = pthread_mutex_init(&pin->sLock, NULL);
    if (status != 0) {
        return PIN_SESSION_EXCEPTION_INIT_ERROR;
    }

    return PIN_SESSION_EXCEPTION_NO_ERROR;

}

int lockPinIOSession(pin_t *const pin) {

    const int status = pthread_mutex_lock(&pin->sLock);
    if (status != 0) {
        return PIN_SESSION_EXCEPTION_LOCK_ERROR;
    }

    return PIN_SESSION_EXCEPTION_NO_ERROR;

}

int unlockPinIOSession(pin_t *const pin) {

    const int status = pthread_mutex_unlock(&pin->sLock);
    if (status != 0) {
        return PIN_SESSION_EXCEPTION_UNLOCK_ERROR;
    }

    return PIN_SESSION_EXCEPTION_NO_ERROR;

}

int destroyPinIOSession(pin_t *const pin) {

    const int status = pthread_mutex_destroy(&pin->sLock);
    if (status != 0) {
        return PIN_SESSION_EXCEPTION_DESTROY_ERROR;
    }

    return PIN_SESSION_EXCEPTION_NO_ERROR;

}