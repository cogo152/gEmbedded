//
// Created by sondahi on 29.01.23.
//

#include <pthread.h>

#include "pin_session.h"

static pthread_mutex_t cLock = PTHREAD_MUTEX_INITIALIZER;

int lockConfig(void ){

    const int status = pthread_mutex_lock(&cLock);
    if (status != 0) {
        return PIN_SESSION_EXCEPTION_LOCK_ERROR;
    }

    return PIN_SESSION_EXCEPTION_NO_ERROR;

}

int unlockConfig(void ){

    const int status = pthread_mutex_unlock(&cLock);
    if (status != 0) {
        return PIN_SESSION_EXCEPTION_UNLOCK_ERROR;
    }

    return PIN_SESSION_EXCEPTION_NO_ERROR;

}

int initSession(pin_t *const pin) {

    const int status = pthread_mutex_init(&pin->sLock, NULL);
    if (status != 0) {
        return PIN_SESSION_EXCEPTION_INIT_ERROR;
    }

    return PIN_SESSION_EXCEPTION_NO_ERROR;

}

int lockSession(pin_t *const pin) {

    const int status = pthread_mutex_lock(&pin->sLock);
    if (status != 0) {
        return PIN_SESSION_EXCEPTION_LOCK_ERROR;
    }

    return PIN_SESSION_EXCEPTION_NO_ERROR;

}

int unlockSession(pin_t *const pin) {

    const int status = pthread_mutex_unlock(&pin->sLock);
    if (status != 0) {
        return PIN_SESSION_EXCEPTION_UNLOCK_ERROR;
    }

    return PIN_SESSION_EXCEPTION_NO_ERROR;

}

int destroySession(pin_t *const pin) {

    const int status = pthread_mutex_destroy(&pin->sLock);
    if (status != 0) {
        return PIN_SESSION_EXCEPTION_DESTROY_ERROR;
    }

    return PIN_SESSION_EXCEPTION_NO_ERROR;

}