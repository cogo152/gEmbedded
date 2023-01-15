//
// Created by sondahi on 12.01.23.
//

#include <stdlib.h>

#include "gpio_peripheral.h"
#include "gpio_driver.h"
#include "memory_mapper.h"

static volatile uint8_t initialized = FALSE;

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

static uint32_t *outputPins = NULL;
static volatile uint8_t outputPinsSize = 0;

GPIO_CONFIG_STATUS setupGpioDriver(void) {

    if(initialized == TRUE){
        return GPIO_CONFIG_ERROR;
    }

    const MAPPER_STATUS mapStatus = mapBaseRegister(MEMORY_FILE_NAME, BLOCK_SIZE, GPIO_BASE_ADDRESS, &gpioBase);
    if (mapStatus != MAPPER_SUCCESS) {
        return GPIO_CONFIG_ERROR;
    }

    outputPins = (uint32_t *) malloc(PIN_ARRAY_LENGTH * sizeof(uint32_t));
    if (outputPins == NULL) {
        return GPIO_CONFIG_ERROR;
    } else{
        outputPinsSize = PIN_ARRAY_LENGTH;
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

    initialized = TRUE;

    return GPIO_CONFIG_SUCCESS;

}

GPIO_CONFIG_STATUS shutdownGpioDriver(void) {

    if(initialized == FALSE){
        return GPIO_CONFIG_ERROR;
    }

    const MAPPER_STATUS unmapStatus = unmapBaseRegister(&gpioBase, BLOCK_SIZE);
    if (unmapStatus != MAPPER_SUCCESS) {
        return GPIO_CONFIG_ERROR;
    }

    free((void *) outputPins);

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

    initialized = FALSE;

    return GPIO_CONFIG_SUCCESS;
}


static void setPinFunction(uint8_t pinNumber, uint8_t pinFunction) {

    const uint8_t registerSelector = pinNumber / 10;
    FSEL[registerSelector] &= ~(7 << ((pinNumber % 10) * 3));
    FSEL[registerSelector] |= (pinFunction << ((pinNumber % 10) * 3));

}

GPIO_CONFIG_STATUS openOutputPin(uint8_t pinNumber) {

    if(initialized == FALSE){
        return GPIO_CONFIG_ERROR;
    }

    setPinFunction(pinNumber, PIN_FUNCTION_OUTPUT);

    return GPIO_CONFIG_SUCCESS;

}

GPIO_CONFIG_STATUS registerOutputPin(uint8_t pinNumber, uint8_t *pinReference){

    if(initialized == FALSE){
        return GPIO_CONFIG_ERROR;
    }

    static volatile uint8_t index = 0;
    if(index == outputPinsSize){
        outputPins = (uint32_t *) realloc((void *) outputPins, (outputPinsSize * sizeof(uint32_t)) + (PIN_ARRAY_LENGTH * sizeof(uint32_t)));
        if(outputPins == NULL){
            return GPIO_CONFIG_ERROR;
        } else {
            outputPinsSize += PIN_ARRAY_LENGTH;
        }
    }
    outputPins[index] = 1 << ((pinNumber % 32) * 1);
    *pinReference = index;
    ++index;

    return GPIO_CONFIG_SUCCESS;
}

GPIO_IO_STATUS setHighOutputPin(uint8_t pinReference) {

    if(initialized == FALSE){
        return GPIO_IO_ERROR;
    }

    *SET = outputPins[pinReference];

    return GPIO_IO_SUCCESS;
}

GPIO_IO_STATUS readOutputPin(uint8_t pinReference, uint8_t *pinLevel) {

    if(initialized == FALSE){
        return GPIO_IO_ERROR;
    }

    volatile uint32_t registerLine = *LEV;
    registerLine &= outputPins[pinReference];
    if (registerLine > 0) {
        *pinLevel = PIN_LEVEL_HIGH;
    } else {
        *pinLevel = PIN_LEVEL_LOW;
    }

    return GPIO_IO_SUCCESS;
}

GPIO_IO_STATUS setLowOutputPin(uint8_t pinReference) {

    if(initialized == FALSE){
        return GPIO_IO_ERROR;
    }

    *CLR = outputPins[pinReference];

    return GPIO_IO_SUCCESS;

}

GPIO_CONFIG_STATUS closeOutputPin(uint8_t pinReference) {

    if(initialized == FALSE){
        return GPIO_CONFIG_ERROR;
    }

    outputPins[pinReference] = 0;

    return GPIO_CONFIG_SUCCESS;
}