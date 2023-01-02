//
// Created by sondahi on 17.12.22.
//

#include <pthread.h>

#include "pin.h"

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

static pthread_mutex_t validatorLock = PTHREAD_MUTEX_INITIALIZER;

static uint8_t isPinInArray(const PIN *pinArray, const uint8_t pinLength, const PIN pinToSearch) {

    for (int i = 0; i < pinLength; ++i) {
        const PIN pin = *pinArray++;
        if (pin == pinToSearch) {
            return TRUE;
        }
    }

    return FALSE;

}

PIN_STATUS validatePin(PIN_TYPE pinType, PIN pinToValidate) {

    pthread_mutex_lock(&validatorLock);

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
            pthread_mutex_unlock(&validatorLock);
            return PIN_ERROR;
        }
    }

    pthread_mutex_unlock(&validatorLock);

    if (result == TRUE) {
        return PIN_SUCCESS;
    } else {
        return PIN_ERROR;
    }

}