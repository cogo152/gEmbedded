//
// Created by sondahi on 12.01.23.
//

#include "gpiodriver.h"

static GPIO_STATUS setupGpioDriver(void ){

    return GPIO_SUCCESS;
}

static GPIO_STATUS shutdownGpioDriver(void ){


    return GPIO_SUCCESS;
}

static GPIO_STATUS openOutputPin(uint8_t pinNumber, uint8_t *pinReference) {

    return GPIO_SUCCESS;
}

static GPIO_STATUS setOutputPin(uint8_t pinReference) {

    return GPIO_SUCCESS;
}

static GPIO_STATUS readOutputPin(uint8_t pinReference) {

    return GPIO_SUCCESS;
}

static GPIO_STATUS clearOutputPin(uint8_t pinReference) {

    return GPIO_SUCCESS;
}

static GPIO_STATUS closeOutputPin(uint8_t pinReference) {

    return GPIO_SUCCESS;
}

static GPIO_STATUS openInputPin(uint8_t pinNumber, uint8_t pullUpDown, uint8_t *pinReference) {

    return GPIO_SUCCESS;
}

static GPIO_STATUS readInputPin(uint8_t pinReference, uint8_t *valueToRead) {

    return GPIO_SUCCESS;
}

static GPIO_STATUS closeInputPin(uint8_t pinReference) {

    return GPIO_SUCCESS;
}

static GPIO_STATUS openListenerPin(uint8_t pinNumber, uint8_t event, uint8_t *pinReference) {

    return GPIO_SUCCESS;
}

static GPIO_STATUS readListenerPin(uint8_t pinReference) {

    return GPIO_SUCCESS;
}

static GPIO_STATUS closeListenerPin(uint8_t pinReference) {

    return GPIO_SUCCESS;
}

static GPIO_STATUS openAlternatePin(uint8_t pinNumber, uint8_t alternate, uint8_t *pinReference) {

    return GPIO_SUCCESS;
}

static GPIO_STATUS closeAlternatePin(uint8_t pinReference) {

    return GPIO_SUCCESS;
}

void bindGpioLFS(void) {
    gpioDriver.setupGpioDriver = setupGpioDriver;
    gpioDriver.shutdownGpioDriver = shutdownGpioDriver;
    gpioDriver.openOutputPin = openOutputPin;
    gpioDriver.setOutputPin = setOutputPin;
    gpioDriver.readOutputPin = readOutputPin;
    gpioDriver.clearOutputPin = clearOutputPin;
    gpioDriver.closeOutputPin = closeOutputPin;
    gpioDriver.openInputPin = openInputPin;
    gpioDriver.readInputPin = readInputPin;
    gpioDriver.closeInputPin = closeInputPin;
    gpioDriver.openListenerPin = openListenerPin;
    gpioDriver.readListenerPin = readListenerPin;
    gpioDriver.closeListenerPin = closeListenerPin;
    gpioDriver.openAlternatePin = openAlternatePin;
    gpioDriver.closeAlternatePin = closeAlternatePin;
}

void unbindGpioLFS(void) {
    gpioDriver.setupGpioDriver = NULL;
    gpioDriver.shutdownGpioDriver = NULL;
    gpioDriver.openOutputPin = NULL;
    gpioDriver.setOutputPin = NULL;
    gpioDriver.readOutputPin = NULL;
    gpioDriver.clearOutputPin = NULL;
    gpioDriver.closeOutputPin = NULL;
    gpioDriver.openInputPin = NULL;
    gpioDriver.readInputPin = NULL;
    gpioDriver.closeInputPin = NULL;
    gpioDriver.openListenerPin = NULL;
    gpioDriver.readListenerPin = NULL;
    gpioDriver.closeListenerPin = NULL;
    gpioDriver.openAlternatePin = NULL;
    gpioDriver.closeAlternatePin = NULL;
}