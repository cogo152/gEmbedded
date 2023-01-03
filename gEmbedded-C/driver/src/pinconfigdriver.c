//
// Created by sondahi on 02.01.23.
//

#include <linux/gpio.h>
#include <sys/ioctl.h>

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
            return PIN_CONFIG_SUCCESS;
        }
        default: {
            return PIN_CONFIG_ERROR;
        }
    }

}

PIN_CONFIG_STATUS readPinFunction(PIN validatedPin, PIN_FUNCTION *pinFunctionToRead) {

    if (pinConfigInitialized == FALSE) {
        return PIN_CONFIG_ERROR;
    }

    const uint8_t registerSelector = validatedPin / 10;
    const uint32_t registerLine = pinConfigRegs->FSEL[registerSelector];
    const uint32_t mask = (7 << ((validatedPin % 10) * 3));
    uint32_t pinFunction = registerLine & mask;
    pinFunction >>= ((validatedPin % 10) * 3);
    *pinFunctionToRead = pinFunction;

    return PIN_CONFIG_SUCCESS;

}


PIN_CONFIG_STATUS configurePinPullUpDown(PIN validatedPin, PULL_UP_DOWN pullUpDownToConfigure) {

    if (pinConfigInitialized == FALSE) {
        return PIN_CONFIG_ERROR;
    }

    switch (pullUpDownToConfigure) {
        case PULL_UP_DOWN_NO_RESISTOR:
        case PULL_UP_DOWN_PULL_UP:
        case PULL_UP_DOWN_PULL_DOWN: {
            const uint8_t registerSelector = validatedPin / 16;
            pinConfigRegs->PUP_PDN[registerSelector] &= ~(3 << ((validatedPin % 16) * 2));
            pinConfigRegs->PUP_PDN[registerSelector] |= (pullUpDownToConfigure << ((validatedPin % 16) * 2));
            return PIN_CONFIG_SUCCESS;
        }
        default: {
            return PIN_CONFIG_ERROR;
        }
    }

}

PIN_CONFIG_STATUS readPinPullUpDown(PIN validatedPin, PULL_UP_DOWN *pullUpDownToRead) {

    if (pinConfigInitialized == FALSE) {
        return PIN_CONFIG_ERROR;
    }

    const uint8_t registerSelector = validatedPin / 16;
    const uint32_t registerLine = pinConfigRegs->PUP_PDN[registerSelector];
    const uint32_t mask = (3 << ((validatedPin % 16) * 2));
    uint32_t pullUpDown = registerLine & mask;
    pullUpDown >>= ((validatedPin % 16) * 2);
    *pullUpDownToRead = pullUpDown;

    return PIN_CONFIG_SUCCESS;

}

PIN_CONFIG_STATUS configurePinEvent(PIN validatedPin, PIN_EVENT pinEventToConfigure, int *fileDescriptor) {

    if (pinConfigInitialized == FALSE) {
        return PIN_CONFIG_ERROR;
    }

    int fd = open("/dev/gpiochip0", O_WRONLY);
    if (fileDescriptor < 0) {
        close(fd);
        return PIN_CONFIG_ERROR;
    }

    struct gpioevent_request rq;

    rq.lineoffset = (__u32) validatedPin;
    rq.handleflags = GPIOHANDLE_REQUEST_INPUT;

    switch (pinEventToConfigure) {
        case PIN_EVENT_NO_EVENT: {
            const uint8_t registerSelector = validatedPin / 31;
            pinConfigRegs->REN[registerSelector] &= ~(1 << ((validatedPin % 32) * 1));
            pinConfigRegs->FEN[registerSelector] &= ~(1 << ((validatedPin % 32) * 1));
            *fileDescriptor = 0;
            close(fd);
            return PIN_CONFIG_SUCCESS;
        }
        case PIN_EVENT_RISING: {
            rq.eventflags = GPIOEVENT_REQUEST_RISING_EDGE;
            break;
        }
        case PIN_EVENT_FALLING: {
            rq.eventflags = GPIOEVENT_REQUEST_FALLING_EDGE;
            break;
        }
        case PIN_EVENT_BOTH: {
            rq.eventflags = GPIOEVENT_REQUEST_BOTH_EDGES;
            break;
        }
        default: {
            close(fd);
            return PIN_CONFIG_ERROR;
        }
    }

    int result = ioctl(fd, GPIO_GET_LINEEVENT_IOCTL, &rq);
    if (result < 0) {
        close(fd);
        return PIN_CONFIG_ERROR;
    }

    close(fd);

    *fileDescriptor = rq.fd;

    return PIN_CONFIG_SUCCESS;
}

PIN_CONFIG_STATUS readPinEvent(PIN validatedPin, PIN_EVENT *pinEventToRead) {

    if (pinConfigInitialized == FALSE) {
        return PIN_CONFIG_ERROR;
    }

    const uint8_t registerSelector = validatedPin / 31;
    const uint32_t mask = (1 << ((validatedPin % 32) * 1));

    const uint32_t registerLineREN = pinConfigRegs->REN[registerSelector];
    const uint32_t registerLineFEN = pinConfigRegs->FEN[registerSelector];

    uint32_t pinEventREN = registerLineREN & mask;
    pinEventREN >>= ((validatedPin % 32) * 1);

    uint32_t pinEventFEN = registerLineFEN & mask;
    pinEventFEN >>= ((validatedPin % 32) * 1);

    if ((pinEventREN & pinEventFEN) == TRUE) {
        *pinEventToRead = PIN_EVENT_BOTH;
    } else if (pinEventREN == TRUE) {
        *pinEventToRead = PIN_EVENT_RISING;
    } else if (pinEventFEN == TRUE) {
        *pinEventToRead = PIN_EVENT_FALLING;
    } else {
        *pinEventToRead = PIN_EVENT_NO_EVENT;
    }

    return PIN_CONFIG_SUCCESS;

}