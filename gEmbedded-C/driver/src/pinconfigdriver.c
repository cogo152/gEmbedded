//
// Created by sondahi on 02.01.23.
//

#include <linux/gpio.h>
#include <sys/ioctl.h>

#include "pinconfigdriver.h"
#include "registers.h"
#include "mapper.h"

static volatile uint8_t pinConfigInitialized = FALSE;
static struct PinConfigRegs *pinConfigRegs = NULL;

PIN_CONFIG_STATUS setupPinConfigDriver(void) {

    if (pinConfigInitialized == TRUE) {
        return PIN_CONFIG_ERROR;
    } else {
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

}

PIN_CONFIG_STATUS shutdownPinConfigDriver(void) {

    if (pinConfigInitialized == FALSE) {
        return PIN_CONFIG_ERROR;
    } else {
        const MAPPER_STATUS unmapStatus = unmapBaseRegister((void **) &pinConfigRegs, BLOCK_SIZE);
        if (unmapStatus != MAPPER_SUCCESS) {
            return PIN_CONFIG_ERROR;
        } else {
            pinConfigRegs = NULL;
            pinConfigInitialized = FALSE;
            return PIN_CONFIG_SUCCESS;
        }
    }

}

PIN_CONFIG_STATUS configurePinFunction(PIN validatedPin, PIN_FUNCTION validatedPinFunction) {

    if (pinConfigInitialized == FALSE) {
        return PIN_CONFIG_ERROR;
    } else {
        const uint8_t registerSelector = validatedPin / 10;
        pinConfigRegs->FSEL[registerSelector] &= ~(7 << ((validatedPin % 10) * 3));
        pinConfigRegs->FSEL[registerSelector] |= (validatedPinFunction << ((validatedPin % 10) * 3));
        return PIN_CONFIG_SUCCESS;
    }

}

PIN_CONFIG_STATUS readPinFunction(PIN validatedPin, PIN_FUNCTION *pinFunctionToRead) {

    if (pinConfigInitialized == FALSE) {
        return PIN_CONFIG_ERROR;
    } else {
        const uint8_t registerSelector = validatedPin / 10;
        const uint32_t registerLine = pinConfigRegs->FSEL[registerSelector];
        const uint32_t mask = (7 << ((validatedPin % 10) * 3));
        uint32_t pinFunction = registerLine & mask;
        pinFunction >>= ((validatedPin % 10) * 3);
        *pinFunctionToRead = pinFunction;
        return PIN_CONFIG_SUCCESS;
    }

}


PIN_CONFIG_STATUS configurePinPullUpDown(PIN validatedPin, PULL_UP_DOWN validatedPinPullUpDown) {

    if (pinConfigInitialized == FALSE) {
        return PIN_CONFIG_ERROR;
    } else {
        const uint8_t registerSelector = validatedPin / 16;
        pinConfigRegs->PUP_PDN[registerSelector] &= ~(3 << ((validatedPin % 16) * 2));
        pinConfigRegs->PUP_PDN[registerSelector] |= (validatedPinPullUpDown << ((validatedPin % 16) * 2));
        return PIN_CONFIG_SUCCESS;
    }

}

PIN_CONFIG_STATUS readPinPullUpDown(PIN validatedPin, PULL_UP_DOWN *pinPullUpDownToRead) {

    if (pinConfigInitialized == FALSE) {
        return PIN_CONFIG_ERROR;
    } else {
        const uint8_t registerSelector = validatedPin / 16;
        const uint32_t registerLine = pinConfigRegs->PUP_PDN[registerSelector];
        const uint32_t mask = (3 << ((validatedPin % 16) * 2));
        uint32_t pinPullUpDown = registerLine & mask;
        pinPullUpDown >>= ((validatedPin % 16) * 2);
        *pinPullUpDownToRead = pinPullUpDown;
        return PIN_CONFIG_SUCCESS;
    }

}

PIN_CONFIG_STATUS configurePinEvent(PIN validatedPin, PIN_EVENT validatedPinEvent){

    if (pinConfigInitialized == FALSE) {
        return PIN_CONFIG_ERROR;
    } else {
        const uint8_t registerSelector = validatedPin / 32;
        const uint32_t clearMask = ~(1 << ((validatedPin % 32) * 1));
        const uint32_t setMask = (1 << ((validatedPin % 32) * 1));
        switch (validatedPinEvent) {
            case PIN_EVENT_NO_EVENT : {
                pinConfigRegs->REN[registerSelector]&=clearMask;
                pinConfigRegs->FEN[registerSelector]&=clearMask;
            }
            case PIN_EVENT_RISING:{
                pinConfigRegs->REN[registerSelector]|=setMask;
                break;
            }
            case PIN_EVENT_FALLING: {
                pinConfigRegs->FEN[registerSelector]|=setMask;
                break;
            }
            default: {
                pinConfigRegs->REN[registerSelector]|=setMask;
                pinConfigRegs->FEN[registerSelector]|=setMask;
                break;
            }
        }
        return PIN_CONFIG_SUCCESS;
    }

}

PIN_CONFIG_STATUS configurePinEventLFS(PIN validatedPin, PIN_EVENT validatedPinEvent, int *fileDescriptor) {

    if (pinConfigInitialized == FALSE) {
        return PIN_CONFIG_ERROR;
    } else {
        int fd = open("/dev/gpiochip0", O_WRONLY);
        if (fileDescriptor < 0) {
            close(fd);
            return PIN_CONFIG_ERROR;
        }
        struct gpioevent_request rq;
        rq.lineoffset = (__u32) validatedPin;
        rq.handleflags = GPIOHANDLE_REQUEST_INPUT;
        switch (validatedPinEvent) {
            case PIN_EVENT_NO_EVENT: {
                const uint8_t registerSelector = validatedPin / 32;
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
            default: {
                rq.eventflags = GPIOEVENT_REQUEST_BOTH_EDGES;
                break;
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

}

PIN_CONFIG_STATUS readPinEvent(PIN validatedPin, PIN_EVENT *pinEventToRead) {

    if (pinConfigInitialized == FALSE) {
        return PIN_CONFIG_ERROR;
    } else {
        const uint8_t registerSelector = validatedPin / 32;
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

}

PIN_CONFIG_STATUS releasePinEvent(int fileDescriptor) {

    if (pinConfigInitialized == FALSE) {
        return PIN_CONFIG_ERROR;
    } else {
        if (fileDescriptor < 0) {
            return PIN_CONFIG_ERROR;
        } else {
            close(fileDescriptor);
            return PIN_CONFIG_SUCCESS;
        }
    }

}