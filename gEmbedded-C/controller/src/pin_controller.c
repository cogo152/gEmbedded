//
// Created by sondahi on 29.01.23.
//

#include <pthread.h>

#include "peripheral.h"

#include "pin_controller.h"
#include "pin.h"
#include "pin_session.h"
#include "pin_validator.h"
#include "pin_driver.h"
#include "pin_store.h"

static pthread_mutex_t controllerMutex = PTHREAD_MUTEX_INITIALIZER;

int setupPinController(void){

    initPinDriver();

    return PIN_CONTROLLER_EXCEPTION_NO_ERROR;

}

int shutdownPinController(void){

    destroyPinDriver();

    return PIN_CONTROLLER_EXCEPTION_NO_ERROR;

}

int openOutputPin(int pinNumber, int *reference){

    pin_t outputPin;
    outputPin.cNumber = pinNumber;
    outputPin.cFunction = PIN_CONFIG_FUNCTION_OUTPUT;

    validateOutputPin(&outputPin);

    initSession(&outputPin);

    initOutputPin(&outputPin);

    addPin(outputPin,reference);

    return PIN_CONTROLLER_EXCEPTION_NO_ERROR;

}

int setOutputPinHigh(int reference){

    pin_t *const outputPin = getPin(reference);

    lockSession(outputPin);

    unlockSession(outputPin);

    setPin(outputPin);

    return PIN_CONTROLLER_EXCEPTION_NO_ERROR;

}

int readOutputPinLevel(int reference, int *level){


    pin_t *const outputPin = getPin(reference);

    lockSession(outputPin);

    unlockSession(outputPin);

    readPin(outputPin);

    if(outputPin->ioLevel > 0){
        *level = PIN_IO_LEVEL_HIGH;
    } else {
        *level = PIN_IO_LEVEL_LOW;
    }

    return PIN_CONTROLLER_EXCEPTION_NO_ERROR;


}

int setOutputLow(int reference){

    pin_t *const outputPin = getPin(reference);

    lockSession(outputPin);

    if(outputPin->sState <0 ){
        return -1;
    }

    unlockSession(outputPin);

    clearPin(outputPin);

    return PIN_CONTROLLER_EXCEPTION_NO_ERROR;
}

int closeOutputPin(int reference){

    pin_t *const outputPin = getPin(reference);

    lockSession(outputPin);

    if(outputPin->sState <0 ){
        return -1;
    }

    unlockSession(outputPin);

    destroyOutputPin(outputPin);

    removePin(reference);

    return PIN_CONTROLLER_EXCEPTION_NO_ERROR;

}