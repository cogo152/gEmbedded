//
// Created by sondahi on 02.01.23.
//

#include "pinconfigdriver.h"
#include "registers.h"
#include "mapper.h"

#define GPIO_TYPES_LENGTH   (27)
#define CLOCK_TYPES_LENGTH  (1)
#define PWM_TYPES_LENGTH    (2)
#define I2C_TYPES_LENGTH    (2)
#define SPI_TYPES_LENGTH    (5)
#define UART_TYPES_LENGTH   (2)

static const PIN gpIOTypes[GPIO_TYPES_LENGTH] = {
        PIN_0,
        PIN_2,
        PIN_3,
        PIN_4,
        PIN_5,
        PIN_6,
        PIN_7,
        PIN_8,
        PIN_9,
        PIN_10,
        PIN_11,
        PIN_12,
        PIN_13,
        PIN_14,
        PIN_15,
        PIN_16,
        PIN_17,
        PIN_18,
        PIN_19,
        PIN_20,
        PIN_21,
        PIN_22,
        PIN_23,
        PIN_24,
        PIN_25,
        PIN_26,
        PIN_27,
};

static const PIN clockTypes[CLOCK_TYPES_LENGTH] = {
        PIN_4,
};

static const PIN pwmTypes[PWM_TYPES_LENGTH] = {
        PIN_18,
        PIN_19
};

static const PIN i2cTypes[I2C_TYPES_LENGTH] = {
        PIN_2,
        PIN_3,
};

static const PIN spiTypes[SPI_TYPES_LENGTH] = {
        PIN_7,
        PIN_8,
        PIN_9,
        PIN_10,
        PIN_11
};

static const PIN uartTypes[UART_TYPES_LENGTH] = {
        PIN_14,
        PIN_15,
};

static uint8_t isPinInArray(const PIN *pinArray, const uint8_t pinLength, const PIN pinToSearch) {

    for (int i = 0; i < pinLength; ++i) {
        const PIN pin = *pinArray++;
        if (pin == pinToSearch) {
            return TRUE;
        }
    }

    return FALSE;

}

static volatile uint8_t pinConfigInitialized = FALSE;
static struct PinConfigRegs *pinConfigRegs = NULL;

PIN_CONFIG_STATUS setupPinConfigDriver(void) {

    if (pinConfigInitialized == TRUE) {
        return PIN_CONFIG_ERROR;
    }

    void *gpioBase;

    const MAPPER_STATUS mapStatus = mapBaseRegister(MEMORY_FILE_NAME, BLOCK_SIZE, GPIO_BASE_ADDRESS, &gpioBase);
    if (mapStatus != MAPPER_SUCCESS) {
        return PIN_CONFIG_ERROR;
    } else {
        pinConfigRegs = (struct PinConfigRegs *) gpioBase;
        pinConfigInitialized = TRUE;
        return PIN_CONFIG_SUCCESS;
    }

}

PIN_CONFIG_STATUS shutdownPinConfigDriver(void) {

    if (pinConfigInitialized == FALSE) {
        return PIN_CONFIG_ERROR;
    }

    const MAPPER_STATUS unmapStatus = unmapBaseRegister((void **) &pinConfigRegs, BLOCK_SIZE);
    if (unmapStatus != MAPPER_SUCCESS) {
        return PIN_CONFIG_ERROR;
    } else {
        pinConfigRegs = NULL;
        pinConfigInitialized = FALSE;
        return PIN_CONFIG_SUCCESS;
    }

}

PIN_CONFIG_STATUS validatePin(const PIN_TYPE pinType, const PIN pinToValidate) {

    if (pinConfigInitialized == FALSE) {
        return PIN_CONFIG_ERROR;
    }

    uint8_t result = FALSE;

    switch (pinType) {
        case PIN_TYPE_GPIO : {
            result = isPinInArray(gpIOTypes, GPIO_TYPES_LENGTH, pinToValidate);
            break;
        }
        case PIN_TYPE_CLOCK : {
            result = isPinInArray(clockTypes, CLOCK_TYPES_LENGTH, pinToValidate);
            break;
        }
        case PIN_TYPE_PWM : {
            result = isPinInArray(pwmTypes, PWM_TYPES_LENGTH, pinToValidate);
            break;
        }
        case PIN_TYPE_I2C : {
            result = isPinInArray(i2cTypes, I2C_TYPES_LENGTH, pinToValidate);
            break;
        }
        case PIN_TYPE_SPI : {
            result = isPinInArray(spiTypes, SPI_TYPES_LENGTH, pinToValidate);
            break;
        }
        case PIN_TYPE_UART : {
            result = isPinInArray(uartTypes, UART_TYPES_LENGTH, pinToValidate);
            break;
        }
        default: {
            return PIN_CONFIG_ERROR;
        }
    }

    if (result == TRUE) {
        return PIN_CONFIG_SUCCESS;
    } else {
        return PIN_CONFIG_ERROR;
    }

}


PIN_CONFIG_STATUS configurePinFunction(PIN validatedPin, PIN_FUNCTION pinFunctionToConfigure) {

    if (pinConfigInitialized == FALSE) {
        return PIN_CONFIG_ERROR;
    }

    switch (pinFunctionToConfigure) {
        case PIN_FUNCTION_INPUT:
        case PIN_FUNCTION_OUTPUT:
        case PIN_FUNCTION_ALT_0:
        case PIN_FUNCTION_ALT_1:
        case PIN_FUNCTION_ALT_2:
        case PIN_FUNCTION_ALT_3:
        case PIN_FUNCTION_ALT_4:
        case PIN_FUNCTION_ALT_5: {
            const uint8_t registerSelector = validatedPin / 10;
            pinConfigRegs->FSEL[registerSelector] &= ~(7 << ((validatedPin % 10) * 3));
            pinConfigRegs->FSEL[registerSelector] |= (pinFunctionToConfigure << ((validatedPin % 10) * 3));
            break;
        }
        default: {
            return PIN_CONFIG_ERROR;
        }
    }

    return PIN_CONFIG_SUCCESS;

}

PIN_CONFIG_STATUS readPinFunction(PIN validatedPin, PIN_FUNCTION *pinFunctionToRead) {

    if (pinConfigInitialized == FALSE) {
        return PIN_CONFIG_ERROR;
    }

    const uint8_t registerSelector = validatedPin / 10;
    uint32_t registerLine = pinConfigRegs->FSEL[registerSelector];
    uint32_t mask = (7 << ((validatedPin % 10) * 3));
    uint32_t pinFunction = registerLine & mask;
    pinFunction >>= ((validatedPin % 10) * 3);
    *pinFunctionToRead = pinFunction;

    return PIN_CONFIG_SUCCESS;

}

/*

PIN_CONFIG_STATUS configurePullUpDown(PIN validatedPin, PULL_UP_DOWN pullUpDownToConfigure, struct PinConfigRegs *pinConfigRegs){

}

PIN_CONFIG_STATUS readPullUpDown(PIN validatedPin, PULL_UP_DOWN *pullUpDownToRead, struct PinConfigRegs *pinConfigRegs){

}
 */