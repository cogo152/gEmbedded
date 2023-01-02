//
// Created by sondahi on 07.12.22.
//

#include<pthread.h>

#include "devicecontext.h"
#include "devicecontextlock.h"
#include "deviceregisters.h"
#include "mapper.h"
#include "session.h"

static pthread_mutex_t contextLock = PTHREAD_MUTEX_INITIALIZER;
static volatile uint8_t deviceContextInitialized = FALSE;
static const char *const deviceName = DEVICE_NAME;

static void *gpioBase = NULL;
static void *clockBase = NULL;
static void *pwmBase = NULL;
static void *i2cBase = NULL;

DEVICE_CONTEXT_STATUS setupDeviceContext(void) {

    int mutexResult;
    DEVICE_CONTEXT_STATUS deviceContextStatus = DEVICE_CONTEXT_SUCCESS;

    mutexResult = pthread_mutex_lock(&contextLock);
    if (mutexResult != 0) {
        deviceContextStatus = DEVICE_CONTEXT_LOCK_ERROR;
        goto Return_Context_Status;
    }

    if (deviceContextInitialized == TRUE) {
        deviceContextStatus = DEVICE_CONTEXT_INITIALIZED_ERROR;
        goto Return_Context_Status;
    }

    const MAPPER_STATUS gpioMapperStatus = mapBaseRegister(MEMORY_FILE_NAME, BLOCK_SIZE, GPIO_BASE_ADDRESS, &gpioBase);
    if (gpioMapperStatus != MAPPER_SUCCESS) {
        deviceContextStatus = DEVICE_CONTEXT_GPIOBASE_ERROR;
        goto Return_Context_Status;
    }

    const MAPPER_STATUS clockMapperStatus = mapBaseRegister(MEMORY_FILE_NAME, BLOCK_SIZE, CLOCK_BASE_ADDRESS,
                                                            &clockBase);
    if (clockMapperStatus != MAPPER_SUCCESS) {
        deviceContextStatus = DEVICE_CONTEXT_CLOCKBASE_ERROR;
        goto Return_Context_Status;
    }

    const MAPPER_STATUS pwmMapperStatus = mapBaseRegister(MEMORY_FILE_NAME, BLOCK_SIZE, PWM_BASE_ADDRESS, &pwmBase);
    if (pwmMapperStatus != MAPPER_SUCCESS) {
        deviceContextStatus = DEVICE_CONTEXT_PWMBASE_ERROR;
        goto Return_Context_Status;
    }

    const MAPPER_STATUS i2cMapperStatus = mapBaseRegister(MEMORY_FILE_NAME, BLOCK_SIZE, I2C_BASE_ADDRESS, &i2cBase);
    if (i2cMapperStatus != MAPPER_SUCCESS) {
        deviceContextStatus = DEVICE_CONTEXT_I2CBASE_ERROR;
        goto Return_Context_Status;
    }

    deviceContextInitialized = TRUE;

    Return_Context_Status :
    {
        if (mutexResult == 0) {
            mutexResult = pthread_mutex_unlock(&contextLock);
            if (mutexResult != 0) {
                deviceContextStatus = DEVICE_CONTEXT_UNLOCK_ERROR;
            }
        }
        return deviceContextStatus;
    }

}

DEVICE_CONTEXT_STATUS shutdownDeviceContext(void) {

    int mutexResult;
    DEVICE_CONTEXT_STATUS deviceContextStatus = DEVICE_CONTEXT_SUCCESS;

    mutexResult = pthread_mutex_lock(&contextLock);
    if (mutexResult != 0) {
        deviceContextStatus = DEVICE_CONTEXT_LOCK_ERROR;
        goto Return_Context_Status;
    }

    if (deviceContextInitialized == FALSE) {
        deviceContextStatus = DEVICE_CONTEXT_NOT_INITIALIZED_ERROR;
        goto Return_Context_Status;
    }

    const MAPPER_STATUS gpioMapperStatus = unmapBaseRegister(&gpioBase, BLOCK_SIZE);
    if (gpioMapperStatus != MAPPER_SUCCESS) {
        deviceContextStatus = DEVICE_CONTEXT_GPIOBASE_ERROR;
        goto Return_Context_Status;
    }

    const MAPPER_STATUS clockMapperStatus = unmapBaseRegister(&clockBase, BLOCK_SIZE);
    if (clockMapperStatus != MAPPER_SUCCESS) {
        deviceContextStatus = DEVICE_CONTEXT_CLOCKBASE_ERROR;
        goto Return_Context_Status;
    }

    const MAPPER_STATUS pwmMapperStatus = unmapBaseRegister(&pwmBase, BLOCK_SIZE);
    if (pwmMapperStatus != MAPPER_SUCCESS) {
        deviceContextStatus = DEVICE_CONTEXT_PWMBASE_ERROR;
        goto Return_Context_Status;
    }

    const MAPPER_STATUS i2cMapperStatus = unmapBaseRegister(&i2cBase, BLOCK_SIZE);
    if (i2cMapperStatus != MAPPER_SUCCESS) {
        deviceContextStatus = DEVICE_CONTEXT_I2CBASE_ERROR;
        goto Return_Context_Status;
    }

    deviceContextInitialized = FALSE;

    Return_Context_Status :
    {
        if (mutexResult == 0) {
            mutexResult = pthread_mutex_unlock(&contextLock);
            if (mutexResult != 0) {
                deviceContextStatus = DEVICE_CONTEXT_UNLOCK_ERROR;
            }
        }
        return deviceContextStatus;
    }

}

const char *getDeviceName(void) {

    return deviceName;

}

uint8_t isDeviceInitialized(void) {

    pthread_mutex_lock(&contextLock);

    const uint8_t initialized = deviceContextInitialized;

    pthread_mutex_unlock(&contextLock);

    return initialized;

}

DEVICE_CONTEXT_STATUS requestPinConfigRegs(struct PinConfigRegs **const pPinConfigRegs) {

    if ((deviceContextInitialized == FALSE) || pPinConfigRegs == NULL) {
        return DEVICE_CONTEXT_REGISTER_ERROR;
    }

    *pPinConfigRegs = (struct PinConfigRegs *) gpioBase;

    return DEVICE_CONTEXT_SUCCESS;

}

DEVICE_CONTEXT_STATUS requestPinIORegs(struct PinIORegs **const pPinIORegs) {

    if ((deviceContextInitialized == FALSE) || pPinIORegs == NULL) {
        return DEVICE_CONTEXT_REGISTER_ERROR;
    }

    *pPinIORegs = (struct PinIORegs *) gpioBase;

    return DEVICE_CONTEXT_SUCCESS;

}

DEVICE_CONTEXT_STATUS requestClockRegs(const CLOCK_ID clockId, struct ClockRegs **const pClockRegs) {

    if ((deviceContextInitialized == FALSE) || pClockRegs == NULL) {
        return DEVICE_CONTEXT_REGISTER_ERROR;
    }

    switch (clockId) {
        case CLOCK_GP_0: {
            *pClockRegs = (struct ClockRegs *) (clockBase + CLOCK_GP0_OFFSET);
            break;
        }
        case CLOCK_PWM: {
            *pClockRegs = (struct ClockRegs *) (clockBase + CLOCK_PWM_OFFSET);
            break;
        }
        default: {
            return DEVICE_CONTEXT_REGISTER_ERROR;
        }
    }

    return DEVICE_CONTEXT_SUCCESS;

}

DEVICE_CONTEXT_STATUS requestPWMRegs(struct PWMRegs **const pPWMRegs) {

    if ((deviceContextInitialized == FALSE) || pPWMRegs == NULL) {
        return DEVICE_CONTEXT_REGISTER_ERROR;
    }

    *pPWMRegs = (struct PWMRegs *) pwmBase;

    return DEVICE_CONTEXT_SUCCESS;

}

DEVICE_CONTEXT_STATUS requestI2CRegs(struct I2CRegs **const pI2CRegs) {

    if ((deviceContextInitialized == FALSE) || pI2CRegs == NULL) {
        return DEVICE_CONTEXT_REGISTER_ERROR;
    }

    *pI2CRegs = (struct I2CRegs *) i2cBase;

    return DEVICE_CONTEXT_SUCCESS;

}

SESSION_STATUS initSession(struct session *session){

    return SESSION_SUCCESS;

}

SESSION_STATUS destroySession(struct session *session){

    return SESSION_SUCCESS;
}