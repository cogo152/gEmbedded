//
// Created by sondahi on 04.01.23.
//

#include <sys/poll.h>
#include <linux/gpio.h>

#include "piniodriver.h"
#include "registers.h"
#include "mapper.h"

static volatile uint8_t pinIOInitialized = FALSE;

static void *gpioBase = NULL;

static volatile uintptr_t *SET = NULL;
static volatile uintptr_t *CLR = NULL;
static volatile uintptr_t *LEV = NULL;
static volatile uintptr_t *EDS = NULL;

PIN_IO_STATUS setupPinIODriver(void) {

    if (pinIOInitialized == TRUE) {
        return PIN_IO_ERROR;
    } else {
        const MAPPER_STATUS mapStatus = mapBaseRegister(MEMORY_FILE_NAME, BLOCK_SIZE, GPIO_BASE_ADDRESS, &gpioBase);
        if (mapStatus != MAPPER_SUCCESS) {
            return PIN_IO_ERROR;
        } else {
            SET = ((uintptr_t *) gpioBase + SET_OFFSET);
            CLR = ((uintptr_t *) gpioBase + CLR_OFFSET);
            LEV = ((uintptr_t *) gpioBase + LEV_OFFSET);
            EDS = ((uintptr_t *) gpioBase + EDS_OFFSET);
            pinIOInitialized = TRUE;
            return PIN_IO_SUCCESS;
        }
    }

}

PIN_IO_STATUS shutdownPinIODriver(void) {

    if (pinIOInitialized == FALSE) {
        return PIN_IO_ERROR;
    } else {
        const MAPPER_STATUS unmapStatus = unmapBaseRegister(&gpioBase, BLOCK_SIZE);
        if (unmapStatus != MAPPER_SUCCESS) {
            return PIN_IO_ERROR;
        } else {
            SET = NULL;
            CLR = NULL;
            LEV = NULL;
            EDS = NULL;
            pinIOInitialized = FALSE;
            return PIN_IO_SUCCESS;
        }
    }

}

uint32_t getPinIOBitField(PIN validatedPin){

    return (1 << (validatedPin % 32) * 1);

}

void setPin(uint32_t bitField){

    *SET = bitField;

}

void clearPin(uint32_t bitField){

    *CLR = bitField;

}

uint8_t readPinLevel(uint32_t bitField){

    uint32_t registerLine = *LEV;
    registerLine &= bitField;
    if (registerLine > 0) {
        return TRUE;
    } else {
        return FALSE;
    }

}

void invokePinEvent(uint32_t bitField){

    *EDS = bitField;

}

PIN_IO_STATUS pollPinEvent(struct pinevent *const pinEvent){

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