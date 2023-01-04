//
// Created by sondahi on 04.01.23.
//

#include <pthread.h>

#include "devicecontroller.h"
#include "pinconfigdriver.h"
#include "piniodriver.h"

static pthread_mutex_t deviceControllerLock = PTHREAD_MUTEX_INITIALIZER;
static volatile uint8_t deviceContextInitialized = FALSE;

static DEVICE_CONTROLLER_STATUS setupDrivers(void) {

    const volatile PIN_CONFIG_STATUS pinConfigStatus = setupPinConfigDriver();
    if (pinConfigStatus != PIN_CONFIG_SUCCESS) {
        return DEVICE_CONTROLLER_PIN_CONFIG_ERROR;
    }

    const volatile PIN_IO_STATUS pinIOStatus = setupPinIODriver();
    if (pinIOStatus != PIN_IO_SUCCESS) {
        return DEVICE_CONTROLLER_PIN_IO_ERROR;
    }

    return DEVICE_CONTROLLER_SUCCESS;

}

static DEVICE_CONTROLLER_STATUS shutdownDrivers(void) {

    const volatile PIN_CONFIG_STATUS pinConfigStatus = shutdownPinConfigDriver();
    if (pinConfigStatus != PIN_CONFIG_SUCCESS) {
        return DEVICE_CONTROLLER_PIN_CONFIG_ERROR;
    }

    const volatile PIN_IO_STATUS pinIOStatus = shutdownPinIODriver();
    if (pinIOStatus != PIN_IO_SUCCESS) {
        return DEVICE_CONTROLLER_PIN_IO_ERROR;
    }

    return DEVICE_CONTROLLER_SUCCESS;

}

// Thread safe
DEVICE_CONTROLLER_STATUS setupDeviceContext(void) {

    volatile int mutexResult = pthread_mutex_lock(&deviceControllerLock);

    volatile DEVICE_CONTROLLER_STATUS status;

    if (mutexResult != 0) {
        status = DEVICE_CONTROLLER_LOCK_ERROR;
        goto Return_Device_Controller_Status;
    }

    if (deviceContextInitialized == TRUE) {
        status = DEVICE_CONTROLLER_INITIALIZED_ERROR;
        goto Return_Device_Controller_Status;
    }

    status = setupDrivers();
    if (status != DEVICE_CONTROLLER_SUCCESS) {
        goto Return_Device_Controller_Status;
    }

    deviceContextInitialized = TRUE;

    Return_Device_Controller_Status :
    {
        if (mutexResult == 0) {
            mutexResult = pthread_mutex_unlock(&deviceControllerLock);
            if (mutexResult != 0) {
                status = DEVICE_CONTROLLER_UNLOCK_ERROR;
            }
        }
        return status;
    }

}

// Thread safe
DEVICE_CONTROLLER_STATUS shutdownDeviceContext(void) {

    volatile int mutexResult = pthread_mutex_lock(&deviceControllerLock);

    volatile DEVICE_CONTROLLER_STATUS status;

    if (mutexResult != 0) {
        status = DEVICE_CONTROLLER_LOCK_ERROR;
        goto Return_Device_Controller_Status;
    }

    if (deviceContextInitialized == FALSE) {
        status = DEVICE_CONTROLLER_NOT_INITIALIZED_ERROR;
        goto Return_Device_Controller_Status;
    }

    status = shutdownDrivers();
    if (status != DEVICE_CONTROLLER_SUCCESS) {
        goto Return_Device_Controller_Status;
    }

    deviceContextInitialized = FALSE;

    Return_Device_Controller_Status :
    {
        if (mutexResult == 0) {
            mutexResult = pthread_mutex_unlock(&deviceControllerLock);
            if (mutexResult != 0) {
                status = DEVICE_CONTROLLER_UNLOCK_ERROR;
            }
        }
        return status;
    }
}