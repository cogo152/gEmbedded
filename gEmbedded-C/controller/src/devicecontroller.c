//
// Created by sondahi on 04.01.23.
//

#include <pthread.h>

#include "devicecontroller.h"
#include "pinconfigdriver.h"
#include "piniodriver.h"

static pthread_mutex_t deviceControllerLock = PTHREAD_MUTEX_INITIALIZER;
static volatile uint8_t deviceContextInitialized = FALSE;

// Thread safe
DEVICE_CONTROLLER_STATUS setupDeviceContext(void) {

    volatile DEVICE_CONTROLLER_STATUS deviceControllerStatus = DEVICE_CONTROLLER_SUCCESS;

    volatile int mutexResult = pthread_mutex_lock(&deviceControllerLock);

    if (mutexResult != 0) {
        deviceControllerStatus = DEVICE_CONTROLLER_LOCK_ERROR;
        goto Return_Context_Status;
    }

    if (deviceContextInitialized == TRUE) {
        deviceControllerStatus = DEVICE_CONTROLLER_INITIALIZED_ERROR;
        goto Return_Context_Status;
    }

    const volatile PIN_CONFIG_STATUS pinConfigStatus = setupPinConfigDriver();
    if (pinConfigStatus != PIN_CONFIG_SUCCESS) {
        deviceControllerStatus = DEVICE_CONTROLLER_PIN_CONFIG_ERROR;
        goto Return_Context_Status;
    }

    const volatile PIN_IO_STATUS pinIOStatus = setupPinIODriver();
    if (pinIOStatus != PIN_IO_SUCCESS) {
        deviceControllerStatus = DEVICE_CONTROLLER_PIN_IO_ERROR;
        goto Return_Context_Status;
    }

    deviceContextInitialized = TRUE;

    Return_Context_Status :
    {
        if (mutexResult == 0) {
            mutexResult = pthread_mutex_unlock(&deviceControllerLock);
            if (mutexResult != 0) {
                deviceControllerStatus = DEVICE_CONTROLLER_UNLOCK_ERROR;
            }
        }
        return deviceControllerStatus;
    }

}

// Thread safe
DEVICE_CONTROLLER_STATUS shutdownDeviceContext(void) {

    volatile DEVICE_CONTROLLER_STATUS deviceControllerStatus = DEVICE_CONTROLLER_SUCCESS;

    volatile int mutexResult = pthread_mutex_lock(&deviceControllerLock);

    if (mutexResult != 0) {
        deviceControllerStatus = DEVICE_CONTROLLER_LOCK_ERROR;
        goto Return_Context_Status;
    }

    if (deviceContextInitialized == FALSE) {
        deviceControllerStatus = DEVICE_CONTROLLER_NOT_INITIALIZED_ERROR;
        goto Return_Context_Status;
    }

    const volatile PIN_CONFIG_STATUS pinConfigStatus = shutdownPinConfigDriver();
    if (pinConfigStatus != PIN_CONFIG_SUCCESS) {
        deviceControllerStatus = DEVICE_CONTROLLER_PIN_CONFIG_ERROR;
        goto Return_Context_Status;
    }

    const volatile PIN_IO_STATUS pinIOStatus = shutdownPinIODriver();
    if (pinIOStatus != PIN_IO_SUCCESS) {
        deviceControllerStatus = DEVICE_CONTROLLER_PIN_IO_ERROR;
        goto Return_Context_Status;
    }

    deviceContextInitialized = FALSE;

    Return_Context_Status :
    {
        if (mutexResult == 0) {
            mutexResult = pthread_mutex_unlock(&deviceControllerLock);
            if (mutexResult != 0) {
                deviceControllerStatus = DEVICE_CONTROLLER_UNLOCK_ERROR;
            }
        }
        return deviceControllerStatus;
    }

}