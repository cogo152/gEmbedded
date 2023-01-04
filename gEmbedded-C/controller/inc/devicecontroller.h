//
// Created by sondahi on 04.01.23.
//

#ifndef GEMBEDDED_C_DEVICECONTROLLER_H
#define GEMBEDDED_C_DEVICECONTROLLER_H

#include "common.h"

typedef enum {
    DEVICE_CONTROLLER_SUCCESS = 0,
    DEVICE_CONTROLLER_LOCK_ERROR = 1,
    DEVICE_CONTROLLER_UNLOCK_ERROR = 2,
    DEVICE_CONTROLLER_INITIALIZED_ERROR = 3,
    DEVICE_CONTROLLER_NOT_INITIALIZED_ERROR = 4,
    DEVICE_CONTROLLER_PIN_CONFIG_ERROR = 5,
    DEVICE_CONTROLLER_PIN_IO_ERROR = 6,
} DEVICE_CONTROLLER_STATUS;

// Thread safe
DEVICE_CONTROLLER_STATUS setupDeviceContext(void);

// Thread safe
DEVICE_CONTROLLER_STATUS shutdownDeviceContext(void);

// Not thread safe
const char *getDeviceName(void);

// Thread safe
uint8_t isDeviceInitialized(void);

#endif //GEMBEDDED_C_DEVICECONTROLLER_H
