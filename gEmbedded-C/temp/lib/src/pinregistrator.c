//
// Created by sondahi on 17.12.22.
//

#include <pthread.h>

#include "pin.h"

static uint8_t registeredPins[MAX_PIN_LENGTH];

static pthread_mutex_t registratorLock = PTHREAD_MUTEX_INITIALIZER;

PIN_STATUS registerPin(PIN validatedPin) {

    if (validatedPin < 0 || validatedPin > (MAX_PIN_LENGTH - 1)) {
        pthread_mutex_unlock(&registratorLock);
        return PIN_ERROR;
    }

    pthread_mutex_lock(&registratorLock);

    static uint8_t initialized;

    if (initialized == FALSE) {
        for (int i = 0; i < MAX_PIN_LENGTH; ++i) {
            registeredPins[i] = FALSE;
        }
        initialized = TRUE;
    }

    uint8_t result = registeredPins[validatedPin];
    if (result == TRUE) {
        pthread_mutex_unlock(&registratorLock);
        return PIN_ERROR;
    } else {
        registeredPins[validatedPin] = TRUE;
        pthread_mutex_unlock(&registratorLock);
        return PIN_SUCCESS;
    }

}