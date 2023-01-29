//
// Created by sondahi on 29.01.23.
//

#include "pin_session.h"
#include "pin_exception.h"

int initSession(pthread_mutex_t *const mutex) {

    const int status = pthread_mutex_init(mutex, NULL);
    if (status != 0) {
        return PIN_SESSION_EXCEPTION_INIT_ERROR;
    }

    return PIN_SESSION_EXCEPTION_NO_ERROR;

}

int lockSession(pthread_mutex_t *const mutex) {

    const int status = pthread_mutex_lock(mutex);
    if (status != 0) {
        return PIN_SESSION_EXCEPTION_LOCK_ERROR;
    }

    return PIN_SESSION_EXCEPTION_NO_ERROR;

}

int unlockSession(pthread_mutex_t *const mutex) {

    const int status = pthread_mutex_unlock(mutex);
    if (status != 0) {
        return PIN_SESSION_EXCEPTION_UNLOCK_ERROR;
    }

    return PIN_SESSION_EXCEPTION_NO_ERROR;

}

int destroySession(pthread_mutex_t *const mutex) {

    const int status = pthread_mutex_destroy(mutex);
    if (status != 0) {
        return PIN_SESSION_EXCEPTION_DESTROY_ERROR;
    }

    return PIN_SESSION_EXCEPTION_NO_ERROR;

}