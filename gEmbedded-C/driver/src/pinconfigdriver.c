//
// Created by sondahi on 02.01.23.
//

#include <linux/gpio.h>
#include <sys/ioctl.h>

#include "pinconfigdriver.h"
#include "registers.h"
#include "mapper.h"

static void *gpioBase = NULL;

static volatile uintptr_t *FSEL = NULL;
static volatile uintptr_t *REN = NULL;
static volatile uintptr_t *FEN = NULL;
static volatile uintptr_t *HEN = NULL;
static volatile uintptr_t *LEN = NULL;
static volatile uintptr_t *AREN = NULL;
static volatile uintptr_t *AFEN = NULL;
static volatile uintptr_t *PUP_PDN = NULL;

PIN_CONFIG_STATUS setupPinConfigDriver(void) {

    const MAPPER_STATUS mapStatus = mapBaseRegister(MEMORY_FILE_NAME, BLOCK_SIZE, GPIO_BASE_ADDRESS, &gpioBase);
    if (mapStatus != MAPPER_SUCCESS) {
        return PIN_CONFIG_ERROR;
    } else {
        FSEL = ((uintptr_t *) gpioBase + FSEL_OFFSET);
        REN = ((uintptr_t *) gpioBase + REN_OFFSET);
        FEN = ((uintptr_t *) gpioBase + FEN_OFFSET);
        HEN = ((uintptr_t *) gpioBase + HEN_OFFSET);
        LEN = ((uintptr_t *) gpioBase + LEN_OFFSET);
        AREN = ((uintptr_t *) gpioBase + AREN_OFFSET);
        AFEN = ((uintptr_t *) gpioBase + AFEN_OFFSET);
        PUP_PDN = ((uintptr_t *) gpioBase + PUP_PDN_OFFSET);
        return PIN_CONFIG_SUCCESS;
    }

}

PIN_CONFIG_STATUS shutdownPinConfigDriver(void) {

    const MAPPER_STATUS unmapStatus = unmapBaseRegister(&gpioBase, BLOCK_SIZE);
    if (unmapStatus != MAPPER_SUCCESS) {
        return PIN_CONFIG_ERROR;
    } else {
        FSEL = NULL;
        REN = NULL;
        FEN = NULL;
        HEN = NULL;
        LEN = NULL;
        AREN = NULL;
        AFEN = NULL;
        PUP_PDN = NULL;
        return PIN_CONFIG_SUCCESS;
    }

}

void configurePinFunction(PIN validatedPin, PIN_FUNCTION validatedPinFunction) {

    *FSEL &= ~(7 << ((validatedPin % 10) * 3));
    *FSEL |= (validatedPinFunction << ((validatedPin % 10) * 3));

}

PIN_FUNCTION readPinFunction(PIN validatedPin) {

    const uint32_t registerLine = *FSEL;
    uint32_t pinFunction = registerLine & (7 << ((validatedPin % 10) * 3));
    pinFunction >>= ((validatedPin % 10) * 3);
    return pinFunction;

}


void configurePinPullUpDown(PIN validatedPin, PULL_UP_DOWN validatedPinPullUpDown) {

    *PUP_PDN &= ~(3 << ((validatedPin % 16) * 2));
    *PUP_PDN |= (validatedPinPullUpDown << ((validatedPin % 16) * 2));

}

PULL_UP_DOWN readPinPullUpDown(PIN validatedPin) {

    const uint32_t registerLine = *PUP_PDN;
    uint32_t pinPullUpDown = registerLine & (3 << ((validatedPin % 16) * 2));
    pinPullUpDown >>= ((validatedPin % 16) * 2);
    return pinPullUpDown;

}

static void clearPinEvents(PIN validatedPin) {

    const uint32_t clearMask = ~(1 << ((validatedPin % 32) * 1));
    *REN &= clearMask;
    *FEN &= clearMask;
    *HEN &= clearMask;
    *LEN &= clearMask;
    *AREN &= clearMask;
    *AFEN &= clearMask;

}

PIN_CONFIG_STATUS configurePinEventLFS(PIN validatedPin, PIN_EVENT validatedPinEvent, int *fileDescriptor) {

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
            clearPinEvents(validatedPin);
            *fileDescriptor = 0;
            close(fd);
            return PIN_CONFIG_SUCCESS;
        }
        case PIN_EVENT_RISING: {
            clearPinEvents(validatedPin);
            rq.eventflags = GPIOEVENT_REQUEST_RISING_EDGE;
            break;
        }
        case PIN_EVENT_FALLING: {
            clearPinEvents(validatedPin);
            rq.eventflags = GPIOEVENT_REQUEST_FALLING_EDGE;
            break;
        }
        default: {
            clearPinEvents(validatedPin);
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

PIN_EVENT readPinEvent(PIN validatedPin) {

    const uint32_t mask = (1 << ((validatedPin % 32) * 1));
    const uint32_t registerLineREN = *REN;
    const uint32_t registerLineFEN = *FEN;
    uint32_t pinEventREN = registerLineREN & mask;
    pinEventREN >>= ((validatedPin % 32) * 1);
    uint32_t pinEventFEN = registerLineFEN & mask;
    pinEventFEN >>= ((validatedPin % 32) * 1);
    if ((pinEventREN & pinEventFEN) == TRUE) {
        return PIN_EVENT_BOTH;
    } else if (pinEventREN == TRUE) {
        return PIN_EVENT_RISING;
    } else if (pinEventFEN == TRUE) {
        return PIN_EVENT_FALLING;
    } else {
        return PIN_EVENT_NO_EVENT;
    }

}

void releasePinEvent(int fileDescriptor) {

    close(fileDescriptor);

}