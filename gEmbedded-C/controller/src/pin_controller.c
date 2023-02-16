//
// Created by sondahi on 15.02.23.
//

#include <pthread.h>

#include "pin_controller.h"
#include "pin.h"
#include "pin_store.h"
#include "pin_validator.h"
#include "pin_session.h"
#include "pin_driver.h"
#include "peripheral.h"


static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static volatile int state = PIN_CONTROLLER_FALSE;

int pinControllerInit() {

    volatile int status = PIN_CONTROLLER_ERROR_NO;

    const int lockStatus = pthread_mutex_lock(&mutex);
    if (lockStatus != 0) {
        status = PIN_CONTROLLER_ERROR_LOCK;
        goto Return;
    }

    if (state == PIN_CONTROLLER_TRUE) {
        status = PIN_CONTROLLER_ERROR_STATE;
        goto Unlock;
    }

    int pinDriverInitialized;
    isPinDriverInitialized(&pinDriverInitialized);
    if (pinDriverInitialized == PIN_DRIVER_FALSE) {
        const int pinDriverStatus = initPinDriver();
        if (pinDriverStatus != PIN_DRIVER_ERROR_NO) {
            status = PIN_CONTROLLER_ERROR_DRIVER;
        }
    }

    int pinStoreInitialized;
    isPinStoreInitialized(&pinStoreInitialized);
    if (pinStoreInitialized == PIN_DRIVER_FALSE) {
        const int pinStoreStatus = initPinStore();
        if (pinStoreStatus != PIN_DRIVER_ERROR_NO) {
            status = PIN_CONTROLLER_ERROR_STORE;
        }
    }

    state = PIN_CONTROLLER_TRUE;

    Unlock :
    {
        const int unlockStatus = pthread_mutex_unlock(&mutex);
        if (unlockStatus != 0) {
            status = PIN_CONTROLLER_ERROR_UNLOCK;
        }

    };

    Return :
    {
        return status;
    };

}

int pinControllerDestroy() {

    volatile int status = PIN_CONTROLLER_ERROR_NO;

    const int lockStatus = pthread_mutex_lock(&mutex);
    if (lockStatus != 0) {
        status = PIN_CONTROLLER_ERROR_LOCK;
        goto Return;
    }

    if (state == PIN_CONTROLLER_FALSE) {
        status = PIN_CONTROLLER_ERROR_STATE;
        goto Unlock;
    }

    int pinDriverInitialized;
    isPinDriverInitialized(&pinDriverInitialized);
    if (pinDriverInitialized == PIN_DRIVER_TRUE) {
        int closablePinLength;
        const int *closablePinReferences = getClosablePinReferences(&closablePinLength);
        if (closablePinReferences != NULL) {
            for (int i = 0; i < closablePinLength; ++i) {
                pin_t *pin = getPin(closablePinReferences[i]);
                int closeStatus;
                switch (pin->type) {
                    case PIN_TYPE_OUTPUT: {
                        closeStatus = destroyOutputPin(pin);
                        break;
                    }
                    case PIN_TYPE_INPUT: {
                        closeStatus = destroyInputPin(pin);
                        break;
                    }
                    default: {
                        closeStatus = destroyListenerPin(pin);
                        break;
                    }
                }
                if (closeStatus != PIN_DRIVER_ERROR_NO) {
                    status = PIN_CONTROLLER_ERROR_PIN_CLOSE;
                    break;
                }
            }
        }
        const int pinDriverStatus = destroyPinDriver();
        if (pinDriverStatus != PIN_DRIVER_ERROR_NO) {
            status = PIN_CONTROLLER_ERROR_DRIVER;
        }
    }

    int pinStoreInitialized;
    isPinStoreInitialized(&pinStoreInitialized);
    if (pinStoreInitialized == PIN_DRIVER_TRUE) {
        destroyPinStore();
    }

    state = PIN_CONTROLLER_FALSE;

    Unlock :
    {
        const int unlockStatus = pthread_mutex_unlock(&mutex);
        if (unlockStatus != 0) {
            status = PIN_CONTROLLER_ERROR_UNLOCK;
        }

    };

    Return :
    {
        return status;
    };

}

int outputPinOpen(const uint8_t pinNumber, int *const reference) {

    volatile int status = PIN_CONTROLLER_ERROR_NO;

    const int lockStatus = pthread_mutex_lock(&mutex);
    if (lockStatus != 0) {
        status = PIN_CONTROLLER_ERROR_LOCK;
    }

    if (state == PIN_CONTROLLER_FALSE) {
        status = PIN_CONTROLLER_ERROR_STATE;
    }

    const int unlockStatus = pthread_mutex_unlock(&mutex);
    if (unlockStatus != 0) {
        status = PIN_CONTROLLER_ERROR_UNLOCK;
    }

    if (status != PIN_CONTROLLER_ERROR_NO) {
        goto Return;
    }

    const int configSessionLockStatus = lockPinConfigSession();
    if (configSessionLockStatus != PIN_SESSION_ERROR_NO) {
        status = PIN_CONTROLLER_ERROR_CONFIG_LOCK;
        goto Return;
    }

    int pinAdded;
    isPinAdded(pinNumber, &pinAdded);
    if (pinAdded == PIN_STORE_TRUE) {
        status = PIN_CONTROLLER_ERROR_PIN_OPENED;
        goto Unlock;
    }

    pin_t outputPin = {
            .type = PIN_TYPE_OUTPUT,
            .cNumber = pinNumber,
            .cFunction = PIN_CONFIG_FUNCTION_OUTPUT,
    };

    const int validationStatus = validateOutputPin(&outputPin);
    if (validationStatus != PIN_VALIDATOR_ERROR_NO) {
        status = PIN_CONTROLLER_ERROR_PIN_VALIDATION;
        goto Unlock;
    }

    const int initStatus = initOutputPin(&outputPin);
    if (initStatus != PIN_DRIVER_ERROR_NO) {
        status = PIN_CONTROLLER_ERROR_PIN_INIT;
        goto Unlock;
    }

    const int sessionInitStatus = initPinIOSession(&outputPin);
    if (sessionInitStatus != PIN_SESSION_ERROR_NO) {
        status = PIN_CONTROLLER_ERROR_PIN_SESSION_INIT;
        goto Unlock;
    }

    const int addStatus = addPin(outputPin, reference);
    if (addStatus != PIN_STORE_ERROR_NO) {
        status = PIN_CONTROLLER_ERROR_PIN_ADD;
        goto Unlock;
    }

    Unlock :
    {
        const int configSessionUnlockStatus = unlockPinConfigSession();
        if (configSessionUnlockStatus != PIN_SESSION_ERROR_NO) {
            status = PIN_CONTROLLER_ERROR_CONFIG_UNLOCK;
        }

    };

    Return :
    {
        return status;
    };

}

int outputPinClose(const int reference) {

    volatile int status = PIN_CONTROLLER_ERROR_NO;

    const int lockStatus = pthread_mutex_lock(&mutex);
    if (lockStatus != 0) {
        status = PIN_CONTROLLER_ERROR_LOCK;
    }

    if (state == PIN_CONTROLLER_FALSE) {
        status = PIN_CONTROLLER_ERROR_STATE;
    }

    const int unlockStatus = pthread_mutex_unlock(&mutex);
    if (unlockStatus != 0) {
        status = PIN_CONTROLLER_ERROR_UNLOCK;
    }

    if (status != PIN_CONTROLLER_ERROR_NO) {
        goto Return;
    }

    const int configSessionLockStatus = lockPinConfigSession();
    if (configSessionLockStatus != PIN_SESSION_ERROR_NO) {
        status = PIN_CONTROLLER_ERROR_CONFIG_LOCK;
        goto Return;
    }

    pin_t *outputPin = getPin(reference);

    int pinAdded;
    isPinAdded(outputPin->cNumber, &pinAdded);
    if (pinAdded == PIN_STORE_FALSE) {
        status = PIN_CONTROLLER_ERROR_PIN_CLOSED;
        goto Unlock;
    }

    const int destroyStatus = destroyOutputPin(outputPin);
    if (destroyStatus != PIN_DRIVER_ERROR_NO) {
        status = PIN_CONTROLLER_ERROR_PIN_DESTROY;
        goto Unlock;
    }

    const int sessionDestroyStatus = destroyPinIOSession(outputPin);
    if (sessionDestroyStatus != PIN_SESSION_ERROR_NO) {
        status = PIN_CONTROLLER_ERROR_PIN_SESSION_DESTROY;
        goto Unlock;
    }

    removePin(reference);

    Unlock :
    {
        const int configSessionUnlockStatus = unlockPinConfigSession();
        if (configSessionUnlockStatus != PIN_SESSION_ERROR_NO) {
            status = PIN_CONTROLLER_ERROR_CONFIG_UNLOCK;
        }

    };

    Return :
    {
        return status;
    };

}

int outputPinWrite(const int reference) {

    volatile int status = PIN_CONTROLLER_ERROR_NO;

    const int lockStatus = pthread_mutex_lock(&mutex);
    if (lockStatus != 0) {
        status = PIN_CONTROLLER_ERROR_LOCK;
    }

    if (state == PIN_CONTROLLER_FALSE) {
        status = PIN_CONTROLLER_ERROR_STATE;
    }

    const int unlockStatus = pthread_mutex_unlock(&mutex);
    if (unlockStatus != 0) {
        status = PIN_CONTROLLER_ERROR_UNLOCK;
    }

    if (status != PIN_CONTROLLER_ERROR_NO) {
        goto Return;
    }

    pin_t *outputPin = getPin(reference);

    const int ioSessionLockStatus = lockPinIOSession(outputPin);
    if (ioSessionLockStatus != PIN_SESSION_ERROR_NO) {
        status = PIN_CONTROLLER_ERROR_IO_LOCK;
        goto Return;
    }

    const int setStatus = setPin(outputPin);
    if (setStatus != PIN_DRIVER_ERROR_NO) {
        status = PIN_CONTROLLER_ERROR_STATE;
        goto Unlock;
    }

    Unlock :
    {
        const int ioSessionUnlockStatus = unlockPinIOSession(outputPin);
        if (ioSessionUnlockStatus != PIN_SESSION_ERROR_NO) {
            status = PIN_CONTROLLER_ERROR_IO_UNLOCK;
        }

    };

    Return :
    {
        return status;
    };

}

int outputPinClear(const int reference) {

    volatile int status = PIN_CONTROLLER_ERROR_NO;

    const int lockStatus = pthread_mutex_lock(&mutex);
    if (lockStatus != 0) {
        status = PIN_CONTROLLER_ERROR_LOCK;
    }

    if (state == PIN_CONTROLLER_FALSE) {
        status = PIN_CONTROLLER_ERROR_STATE;
    }

    const int unlockStatus = pthread_mutex_unlock(&mutex);
    if (unlockStatus != 0) {
        status = PIN_CONTROLLER_ERROR_UNLOCK;
    }

    if (status != PIN_CONTROLLER_ERROR_NO) {
        goto Return;
    }

    pin_t *outputPin = getPin(reference);

    const int ioSessionLockStatus = lockPinIOSession(outputPin);
    if (ioSessionLockStatus != PIN_SESSION_ERROR_NO) {
        status = PIN_CONTROLLER_ERROR_IO_LOCK;
        goto Return;
    }

    const int clearStatus = clearPin(outputPin);
    if (clearStatus != PIN_DRIVER_ERROR_NO) {
        status = PIN_CONTROLLER_ERROR_STATE;
        goto Unlock;
    }

    Unlock :
    {
        const int ioSessionUnlockStatus = unlockPinIOSession(outputPin);
        if (ioSessionUnlockStatus != PIN_SESSION_ERROR_NO) {
            status = PIN_CONTROLLER_ERROR_IO_UNLOCK;
        }

    };

    Return :
    {
        return status;
    };

}

int outputPinRead(const int reference, int *const pinLevel) {

    volatile int status = PIN_CONTROLLER_ERROR_NO;

    const int lockStatus = pthread_mutex_lock(&mutex);
    if (lockStatus != 0) {
        status = PIN_CONTROLLER_ERROR_LOCK;
    }

    if (state == PIN_CONTROLLER_FALSE) {
        status = PIN_CONTROLLER_ERROR_STATE;
    }

    const int unlockStatus = pthread_mutex_unlock(&mutex);
    if (unlockStatus != 0) {
        status = PIN_CONTROLLER_ERROR_UNLOCK;
    }

    if (status != PIN_CONTROLLER_ERROR_NO) {
        goto Return;
    }

    pin_t *outputPin = getPin(reference);

    const int ioSessionLockStatus = lockPinIOSession(outputPin);
    if (ioSessionLockStatus != PIN_SESSION_ERROR_NO) {
        status = PIN_CONTROLLER_ERROR_IO_LOCK;
        goto Return;
    }

    const int readStatus = readPin(outputPin);
    if (readStatus != PIN_DRIVER_ERROR_NO) {
        status = PIN_CONTROLLER_ERROR_STATE;
        goto Unlock;
    }

    if(outputPin->ioLevel == PIN_DRIVER_IO_LEVEL_HIGH){
        *pinLevel = PIN_CONTROLLER_PIN_LEVEL_HIGH;
    } else {
        *pinLevel = PIN_CONTROLLER_PIN_LEVEL_LOW;
    }

    Unlock :
    {
        const int ioSessionUnlockStatus = unlockPinIOSession(outputPin);
        if (ioSessionUnlockStatus != PIN_SESSION_ERROR_NO) {
            status = PIN_CONTROLLER_ERROR_IO_UNLOCK;
        }

    };

    Return :
    {
        return status;
    };

}