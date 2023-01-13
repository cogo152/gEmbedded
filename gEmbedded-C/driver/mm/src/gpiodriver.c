//
// Created by sondahi on 12.01.23.
//

#include "stdlib.h"

#include "gpiodriver.h"
#include "bcm2711_gpio.h"
#include "mapper.h"

#define INITIAL_PIN_ARRAY_SIZE  (4)

static void *gpioBase = NULL;

static volatile uintptr_t *FSEL = NULL;
static volatile uintptr_t *REN = NULL;
static volatile uintptr_t *FEN = NULL;
static volatile uintptr_t *HEN = NULL;
static volatile uintptr_t *LEN = NULL;
static volatile uintptr_t *AREN = NULL;
static volatile uintptr_t *AFEN = NULL;
static volatile uintptr_t *PUP_PDN = NULL;

static volatile uintptr_t *SET = NULL;
static volatile uintptr_t *CLR = NULL;
static volatile uintptr_t *LEV = NULL;
static volatile uintptr_t *EDS = NULL;

static uint32_t *outputPins;
static uint32_t *inputPins;
static uint32_t *listenerPins;
static uint32_t *alternatePins;

static GPIO_STATUS setupGpioDriver(void) {

    const MAPPER_STATUS mapStatus = mapBaseRegister(MEMORY_FILE_NAME, BLOCK_SIZE, GPIO_BASE_ADDRESS, &gpioBase);
    if (mapStatus != MAPPER_SUCCESS) {
        return GPIO_ERROR;
    }

    outputPins = (uint32_t *) malloc(INITIAL_PIN_ARRAY_SIZE * sizeof(uint32_t));
    if (outputPins == NULL) {
        return GPIO_ERROR;
    }

    inputPins = (uint32_t *) malloc(INITIAL_PIN_ARRAY_SIZE * sizeof(uint32_t));
    if (inputPins == NULL) {
        return GPIO_ERROR;
    }

    listenerPins = (uint32_t *) malloc(INITIAL_PIN_ARRAY_SIZE * sizeof(uint32_t));
    if (listenerPins == NULL) {
        return GPIO_ERROR;
    }

    alternatePins = (uint32_t *) malloc(INITIAL_PIN_ARRAY_SIZE * sizeof(uint32_t));
    if (alternatePins == NULL) {
        return GPIO_ERROR;
    }

    FSEL = ((uintptr_t *) gpioBase) + FSEL_OFFSET;
    REN = ((uintptr_t *) gpioBase) + REN_OFFSET;
    FEN = ((uintptr_t *) gpioBase) + FEN_OFFSET;
    HEN = ((uintptr_t *) gpioBase) + HEN_OFFSET;
    LEN = ((uintptr_t *) gpioBase) + LEN_OFFSET;
    AREN = ((uintptr_t *) gpioBase) + AREN_OFFSET;
    AFEN = ((uintptr_t *) gpioBase) + AFEN_OFFSET;
    PUP_PDN = ((uintptr_t *) gpioBase) + PUP_PDN_OFFSET;

    SET = ((uintptr_t *) gpioBase + SET_OFFSET);
    CLR = ((uintptr_t *) gpioBase + CLR_OFFSET);
    LEV = ((uintptr_t *) gpioBase + LEV_OFFSET);
    EDS = ((uintptr_t *) gpioBase + EDS_OFFSET);

    return GPIO_SUCCESS;

}

static GPIO_STATUS shutdownGpioDriver(void) {

    const MAPPER_STATUS unmapStatus = unmapBaseRegister(&gpioBase, BLOCK_SIZE);
    if (unmapStatus != MAPPER_SUCCESS) {
        return GPIO_ERROR;
    }

    free((void *) outputPins);
    free((void *) inputPins);
    free((void *) listenerPins);
    free((void *) alternatePins);

    FSEL = NULL;
    REN = NULL;
    FEN = NULL;
    HEN = NULL;
    LEN = NULL;
    AREN = NULL;
    AFEN = NULL;
    PUP_PDN = NULL;

    SET = NULL;
    CLR = NULL;
    LEV = NULL;
    EDS = NULL;

    return GPIO_SUCCESS;
}


static void setPinFunction(uint8_t pinNumber, uint8_t pinFunction) {

    uint8_t const registerSelector = pinNumber / 10;

    FSEL[registerSelector] &= ~(7 << ((pinNumber % 10) * 3));
    FSEL[registerSelector] |= (pinFunction << ((pinNumber % 10) * 3));

}

static GPIO_STATUS openOutputPin(uint8_t pinNumber, uint8_t *pinReference) {

    static volatile uint8_t index = 0;

    setPinFunction(pinNumber, PIN_FUNCTION_OUTPUT);
    outputPins[index] = 1 << ((pinNumber % 32) * 1);
    *pinReference = index;
    ++index;

    return GPIO_SUCCESS;
}

static GPIO_STATUS setOutputPin(uint8_t pinReference) {

    *SET = outputPins[pinReference];

    return GPIO_SUCCESS;
}

static GPIO_STATUS readOutputPin(uint8_t pinReference, uint8_t *pinLevel) {

    volatile uint32_t registerLine = *LEV;
    registerLine &= outputPins[pinReference];
    if (registerLine > 0) {
        *pinLevel = PIN_LEVEL_HIGH;
    } else {
        *pinLevel = PIN_LEVEL_LOW;
    }

    return GPIO_SUCCESS;
}

static GPIO_STATUS clearOutputPin(uint8_t pinReference) {

    *CLR = outputPins[pinReference];

    return GPIO_SUCCESS;

}

static GPIO_STATUS closeOutputPin(uint8_t pinReference) {

    outputPins[pinReference] = 0;

    return GPIO_SUCCESS;
}

static GPIO_STATUS openInputPin(uint8_t pinNumber, uint8_t pullUpDown, uint8_t *pinReference) {

    return GPIO_SUCCESS;
}

static GPIO_STATUS readInputPin(uint8_t pinReference, uint8_t *pinLevel) {

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

void bindGpioMM(void) {
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

void unbindGpioMM(void) {
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