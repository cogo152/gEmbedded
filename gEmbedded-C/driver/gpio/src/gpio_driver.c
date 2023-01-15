//
// Created by sondahi on 12.01.23.
//

#include <stdlib.h>

#include "gpio_peripheral.h"
#include "gpio_driver.h"
#include "memory_mapper.h"

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

int setupGpioDriver(void) {

    const MAPPER_STATUS mapStatus = mapBaseRegister(MEMORY_FILE_NAME, BLOCK_SIZE, GPIO_BASE_ADDRESS, &gpioBase);
    if (mapStatus != MAPPER_SUCCESS) {
        return GPIO_STATUS_CONFIG_ERROR;
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

    return GPIO_STATUS_SUCCESS;

}

int shutdownGpioDriver(void) {

    const MAPPER_STATUS unmapStatus = unmapBaseRegister(&gpioBase, BLOCK_SIZE);
    if (unmapStatus != MAPPER_SUCCESS) {
        return GPIO_STATUS_CONFIG_ERROR;
    }

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

    return GPIO_STATUS_SUCCESS;
}

static void setPinFunction(const uint8_t pinNumber, const uint8_t pinFunction) {

    const uint8_t registerSelector = pinNumber / 10;
    FSEL[registerSelector] &= ~(0b111 << ((pinNumber % 10) * 3));
    FSEL[registerSelector] |= (pinFunction << ((pinNumber % 10) * 3));

}

static uint8_t readPinFunction(const uint8_t pinNumber) {

    const uint8_t registerSelector = pinNumber / 10;
    const uint32_t registerLine = FSEL[registerSelector];
    const uint32_t mask = (0b111 << ((pinNumber % 10) * 3));
    uint32_t pinFunction = registerLine & mask;
    pinFunction >>= ((pinNumber % 10) * 3);
    return pinFunction;

}

static void setPinPullUpDown(const uint8_t pinNumber, const uint8_t pullUpDown) {

    const uint8_t registerSelector = pinNumber / 16;
    PUP_PDN[registerSelector] &= ~(0b11 << ((pinNumber % 16) * 2));
    PUP_PDN[registerSelector] |= (pullUpDown << ((pinNumber % 16) * 2));

}

static uint8_t readPinPullUpDown(const uint8_t pinNumber) {

    const uint8_t registerSelector = pinNumber / 16;
    const uint32_t registerLine = PUP_PDN[registerSelector];
    const uint32_t mask = (0b11 << ((pinNumber % 16) * 2));
    uint32_t pullUpDown = registerLine & mask;
    pullUpDown >>= ((pinNumber % 16) * 2);
    return pullUpDown;

}

static uint32_t readPinLevel(const uint32_t pinReference) {

    uint32_t registerLine = *LEV;
    registerLine &= pinReference;

    return registerLine;

}

int openOutputPin(const uint8_t pinNumber, uint32_t *const pinReference) {

    setPinFunction(pinNumber, GPIO_PIN_FUNCTION_OUTPUT);
    const uint8_t pinFunction = readPinFunction(pinNumber);
    if (pinFunction != GPIO_PIN_FUNCTION_OUTPUT) {
        return GPIO_STATUS_CONFIG_ERROR;
    }

    *pinReference = 0b1 << ((pinNumber % 32) * 1);

    return GPIO_STATUS_SUCCESS;

}

void setOutputPinHigh(const uint32_t pinReference) {

    *SET = pinReference;

}

uint8_t readOutputPinLevel(const uint32_t pinReference) {

    const uint32_t pinLevel = readPinLevel(pinReference);

    if (pinLevel > 0) {
        return GPIO_PIN_LEVEL_HIGH;
    } else {
        return GPIO_PIN_LEVEL_LOW;
    }

}

void setOutputPinLow(const uint32_t pinReference) {

    *CLR = pinReference;

}

void closeOutputPin(uint32_t *const pinReference) {

    *pinReference = 0;

}

int openInputPin(const uint8_t pinNumber, const uint8_t pinPullUpDown, uint32_t *const pinReference) {

    setPinFunction(pinNumber, GPIO_PIN_FUNCTION_INPUT);
    const uint8_t pinFunction = readPinFunction(pinNumber);
    if (pinFunction != GPIO_PIN_FUNCTION_INPUT) {
        return GPIO_STATUS_CONFIG_ERROR;
    }

    setPinPullUpDown(pinNumber, pinPullUpDown);
    const uint8_t _pinPullUpDown = readPinPullUpDown(pinNumber);
    if (_pinPullUpDown != pinPullUpDown) {
        return GPIO_STATUS_CONFIG_ERROR;
    }

    *pinReference = 0b1 << ((pinNumber % 32) * 1);

    return GPIO_STATUS_SUCCESS;

}

int updateInputPin(const uint8_t pinNumber, const uint8_t pinPullUpDown) {

    setPinPullUpDown(pinNumber, pinPullUpDown);
    const uint8_t _pinPullUpDown = readPinPullUpDown(pinNumber);
    if (_pinPullUpDown != pinPullUpDown) {
        return GPIO_STATUS_CONFIG_ERROR;
    }

    return GPIO_STATUS_SUCCESS;

}

uint8_t readInputPinLevel(const uint32_t pinReference) {

    const uint32_t pinLevel = readPinLevel(pinReference);

    if (pinLevel > 0) {
        return GPIO_PIN_LEVEL_HIGH;
    } else {
        return GPIO_PIN_LEVEL_LOW;
    }

}

void closeInputPin(uint32_t *const pinReference) {

    *pinReference = 0;

}