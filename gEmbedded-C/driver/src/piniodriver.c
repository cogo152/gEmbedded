//
// Created by sondahi on 04.01.23.
//

#include <sys/poll.h>
#include <linux/gpio.h>

#include "piniodriver.h"
#include "registers.h"
#include "mapper.h"

static volatile uint8_t pinIOInitialized = FALSE;
static struct PinIORegs *pinIORegs = NULL;

PIN_IO_STATUS setupPinIODriver(void) {

    if (pinIOInitialized == TRUE) {
        return PIN_IO_ERROR;
    } else {
        void *gpioBase;
        const MAPPER_STATUS mapStatus = mapBaseRegister(MEMORY_FILE_NAME, BLOCK_SIZE, GPIO_BASE_ADDRESS, &gpioBase);
        if (mapStatus != MAPPER_SUCCESS) {
            return PIN_IO_ERROR;
        } else {
            pinIORegs = (struct PinIORegs *) gpioBase;
            pinIOInitialized = TRUE;
            return PIN_IO_SUCCESS;
        }
    }

}

PIN_IO_STATUS shutdownPinIODriver(void) {

    if (pinIOInitialized == FALSE) {
        return PIN_IO_ERROR;
    } else {
        const MAPPER_STATUS unmapStatus = unmapBaseRegister((void **) &pinIORegs, BLOCK_SIZE);
        if (unmapStatus != MAPPER_SUCCESS) {
            return PIN_IO_ERROR;
        } else {
            pinIORegs = NULL;
            pinIOInitialized = FALSE;
            return PIN_IO_SUCCESS;
        }
    }

}

PIN_IO_STATUS setPin(const PIN validatedPin) {

    if (pinIOInitialized == FALSE) {
        return PIN_IO_ERROR;
    } else {
        const uint8_t registerSelector = validatedPin / 32;
        const uint32_t bitField = (1 << (validatedPin % 32));
        pinIORegs->SET[registerSelector] = bitField;
        return PIN_IO_SUCCESS;
    }

}

PIN_IO_STATUS clearPin(const PIN validatedPin) {

    if (pinIOInitialized == FALSE) {
        return PIN_IO_ERROR;
    } else {
        const uint8_t registerSelector = validatedPin / 32;
        const uint32_t bitField = (1 << (validatedPin % 32));
        pinIORegs->CLR[registerSelector] = bitField;
        return PIN_IO_SUCCESS;
    }

}

PIN_IO_STATUS readPinLevel(const PIN validatedPin, uint8_t *pinLevelToRead) {

    if (pinIOInitialized == FALSE) {
        return PIN_IO_ERROR;
    } else {
        const uint8_t registerSelector = validatedPin / 32;
        const uint32_t mask = 1 << (validatedPin % 32);
        uint32_t registerLine = pinIORegs->LEV[registerSelector];
        registerLine &= mask;
        if (registerLine > 0) {
            *pinLevelToRead = TRUE;
        } else {
            *pinLevelToRead = FALSE;
        }
        return PIN_IO_SUCCESS;
    }

}

PIN_IO_STATUS invokePinEvent(PIN validatedPin){

    if (pinIOInitialized == FALSE) {
        return PIN_IO_ERROR;
    } else {
        const uint8_t registerSelector = validatedPin / 32;
        const uint32_t bitField = (1 << (validatedPin % 32));
        pinIORegs->EDS[registerSelector] = bitField;
        return PIN_IO_SUCCESS;
    }
}

PIN_IO_STATUS pollPinEvent(struct pinevent *const pinEvent){

    if (pinIOInitialized == FALSE) {
        return PIN_IO_ERROR;
    } else {
        struct pollfd pollFd;
        pollFd.fd = pinEvent->fileDescriptor;
        pollFd.events = POLLIN | POLLPRI;
        const int pollResult = poll(&pollFd, 1, pinEvent->timeoutInMilSec);
        switch (pollResult) {
            case -1: {
                return PIN_IO_ERROR;
            }
            case 0 : {
                pinEvent->result = PIN_EVENT_RESULT_TIMEOUT;
                return PIN_IO_SUCCESS;
            }
            default: {
                struct gpioevent_data event;
                const ssize_t readResult = read(pollFd.fd, &event, sizeof(event));
                if (readResult < 1) {
                    return PIN_IO_ERROR;
                } else {
                    pinEvent->timestamp = event.timestamp;
                    if (event.id == GPIOEVENT_REQUEST_RISING_EDGE) {
                        pinEvent->result = PIN_EVENT_RESULT_RISING;
                    } else {
                        pinEvent->result = PIN_EVENT_RESULT_FALLING;
                    }
                    return PIN_IO_SUCCESS;
                }
            }
        }
    }

}