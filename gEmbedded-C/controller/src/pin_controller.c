//
// Created by sondahi on 29.01.23.
//

#include <pthread.h>

#include "pin_controller.h"
#include "pin.h"
#include "pin_session.h"
#include "pin_validator.h"
#include "pin_driver.h"
#include "pin_store.h"

static pthread_mutex_t controllerMutex = PTHREAD_MUTEX_INITIALIZER;

int pinControllerSetup(void){

    setupPinDriver();

    return PIN_CONTROLLER_EXCEPTION_NO_ERROR;

}

int pintControllerShutdown(void){

    shutdownPinDriver();

    return PIN_CONTROLLER_EXCEPTION_NO_ERROR;

}

int outputPinOpen(int pinNumber, int *reference){

    output_pin_t outputPin;
    pthread_mutex_t sessionMutex;

    initSession(&sessionMutex);

    outputPin.mutex=sessionMutex;
    outputPin.number = pinNumber;

    validateOutputPin(&outputPin);

    openOutputPin(&outputPin);

    outputPin.status = 1;

    pin_t pin;

    pin.outputPin = outputPin;

    addPin(pin,reference);

    return PIN_CONTROLLER_EXCEPTION_NO_ERROR;

}

int outputPinSet(int reference){

    output_pin_t *const outputPin = &getPin(reference)->outputPin;

    lockSession(&outputPin->mutex);

    // check status

    unlockSession(&outputPin->mutex);

    setOutputPinHigh(outputPin);

    return PIN_CONTROLLER_EXCEPTION_NO_ERROR;

}

int outputPinRead(int reference, int *level){


    output_pin_t *const outputPin = &getPin(reference)->outputPin;

    lockSession(&outputPin->mutex);

    // check status

    unlockSession(&outputPin->mutex);

    readOutputPinLevel(outputPin);

    *level = outputPin->level;

    return PIN_CONTROLLER_EXCEPTION_NO_ERROR;


}

int outputPinClear(int reference){

    output_pin_t *const outputPin = &getPin(reference)->outputPin;

    lockSession(&outputPin->mutex);

    // check status

    unlockSession(&outputPin->mutex);

    setOutputPinLow(outputPin);

    return PIN_CONTROLLER_EXCEPTION_NO_ERROR;

}

int outputPinClose(int reference){

    output_pin_t *const outputPin = &getPin(reference)->outputPin;

    closeOutputPin(outputPin);

    removePin(reference);

    return PIN_CONTROLLER_EXCEPTION_NO_ERROR;

}