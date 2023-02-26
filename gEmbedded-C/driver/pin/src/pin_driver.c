//
// Created by sondahi on 26.01.23.
//

#include <sys/ioctl.h>
#include <sys/poll.h>

#include "pin_driver.h"
#include "peripheral.h"
#include "memory_mapper.h"

static void *gpioBase = NULL;

static gpio_registers_t registers = {
        .GPFSEL = NULL,
        .GPSET = NULL,
        .GPCLR = NULL,
        .GPLEV = NULL,
        .GPEDS = NULL,
        .GPREN = NULL,
        .GPFEN = NULL,
        .GPHEN = NULL,
        .GPLEN = NULL,
        .GPAREN = NULL,
        .GPAFEN = NULL,
        .GPPUD = NULL
};

PIN_DRIVER_ERROR initPinDriver(void) {

    const MAPPER_ERROR status = mapBaseRegister(MEMORY_FILE_NAME, BLOCK_SIZE, GPIO_BASE_ADDRESS, &gpioBase);
    if (status != MAPPER_ERROR_NO) {
        return PIN_DRIVER_ERROR_MAP;
    }

    const volatile uintptr_t offset = (uintptr_t) gpioBase;
    registers.GPFSEL = (uintptr_t *) (offset + GPIO_GPFSEL_OFFSET);
    registers.GPSET = (uintptr_t *) (offset + GPIO_GPSET_OFFSET);
    registers.GPCLR = (uintptr_t *) (offset + GPIO_GPCLR_OFFSET);
    registers.GPLEV = (uintptr_t *) (offset + GPIO_GPLEV_OFFSET);
    registers.GPEDS = (uintptr_t *) (offset + GPIO_GPEDS_OFFSET);
    registers.GPREN = (uintptr_t *) (offset + GPIO_GPREN_OFFSET);
    registers.GPFEN = (uintptr_t *) (offset + GPIO_GPFEN_OFFSET);
    registers.GPHEN = (uintptr_t *) (offset + GPIO_GPHEN_OFFSET);
    registers.GPLEN = (uintptr_t *) (offset + GPIO_GPLEN_OFFSET);
    registers.GPAREN = (uintptr_t *) (offset + GPIO_GPAREN_OFFSET);
    registers.GPAFEN = (uintptr_t *) (offset + GPIO_GPAFEN_OFFSET);
    registers.GPPUD = (uintptr_t *) (offset + GPIO_GPPUD_OFFSET);

    return PIN_DRIVER_ERROR_NO;

}

PIN_DRIVER_ERROR destroyPinDriver(void) {

    const int status = unmapBaseRegister(&gpioBase, BLOCK_SIZE);
    if (status != MAPPER_ERROR_NO) {
        return PIN_DRIVER_ERROR_UNMAP;
    }

    registers.GPFSEL = NULL;
    registers.GPSET = NULL;
    registers.GPCLR = NULL;
    registers.GPLEV = NULL;
    registers.GPEDS = NULL;
    registers.GPREN = NULL;
    registers.GPFEN = NULL;
    registers.GPHEN = NULL;
    registers.GPLEN = NULL;
    registers.GPAREN = NULL;
    registers.GPAFEN = NULL;
    registers.GPPUD = NULL;

    gpioBase = NULL;

    return PIN_DRIVER_ERROR_NO;

}

void setPinFunction(const uint8_t pinNumber, const uint8_t pinFunction) {

    const uint32_t registerSelector = pinNumber / PIN_CONFIG_FUNCTION_MOD_DIV;
    const uint32_t clearValue = ~(PIN_CONFIG_FUNCTION_MASK << ((pinNumber % PIN_CONFIG_FUNCTION_MOD_DIV) * PIN_CONFIG_FUNCTION_MUL));
    const uint32_t setValue = pinFunction << ((pinNumber % PIN_CONFIG_FUNCTION_MOD_DIV) * PIN_CONFIG_FUNCTION_MUL);

    registers.GPFSEL[registerSelector] &= clearValue;
    registers.GPFSEL[registerSelector] |= setValue;

}

uint8_t readPinFunction(const uint8_t pinNumber) {

    const uint32_t registerSelector = pinNumber / PIN_CONFIG_FUNCTION_MOD_DIV;
    const uint32_t registerLine = registers.GPFSEL[registerSelector];
    const uint32_t maskValue = PIN_CONFIG_FUNCTION_MASK << ((pinNumber % PIN_CONFIG_FUNCTION_MOD_DIV) * PIN_CONFIG_FUNCTION_MUL);

    uint32_t pinFunction = registerLine & maskValue;
    pinFunction >>= ((pinNumber % PIN_CONFIG_FUNCTION_MOD_DIV) * PIN_CONFIG_FUNCTION_MUL);

    return pinFunction;

}

void setPinPullUpDown(const uint8_t pinNumber, const uint8_t pullUpDown) {

    const uint32_t registerSelector = pinNumber / PIN_CONFIG_PUD_MOD_DIV;
    const uint32_t clearValue = ~(PIN_CONFIG_PUD_MASK << ((pinNumber % PIN_CONFIG_PUD_MOD_DIV) * PIN_CONFIG_PUD_MUL));
    const uint32_t setValue = (pullUpDown << ((pinNumber % PIN_CONFIG_PUD_MOD_DIV) * PIN_CONFIG_PUD_MUL));

    registers.GPPUD[registerSelector] &= clearValue;
    registers.GPPUD[registerSelector] |= setValue;

}

uint8_t readPinPullUpDown(const uint8_t pinNumber) {

    const uint32_t registerSelector = pinNumber / PIN_CONFIG_PUD_MOD_DIV;
    const uint32_t registerLine = registers.GPPUD[registerSelector];
    const uint32_t maskValue = (PIN_CONFIG_PUD_MASK << ((pinNumber % PIN_CONFIG_PUD_MOD_DIV) * PIN_CONFIG_PUD_MUL));

    uint32_t pullUpDown = registerLine & maskValue;
    pullUpDown >>= ((pinNumber % PIN_CONFIG_PUD_MOD_DIV) * PIN_CONFIG_PUD_MUL);

    return pullUpDown;

}

PIN_DRIVER_ERROR setPinEvent(const uint8_t pinNumber, const uint8_t pinEvent, int *const fileDescriptor) {

    const int fd = open(PIN_CONFIG_GPIO_CHIP, O_RDONLY);
    if (fd < 0) {
        return PIN_DRIVER_ERROR_FILE;
    }

    struct gpioevent_request rq;
    rq.lineoffset = pinNumber;
    rq.handleflags = GPIOHANDLE_REQUEST_INPUT;
    switch (pinEvent) {
        case PIN_CONFIG_EVENT_RISING: {
            rq.eventflags = GPIOEVENT_REQUEST_RISING_EDGE;
            break;
        }
        case PIN_CONFIG_EVENT_FALLING: {
            rq.eventflags = GPIOEVENT_REQUEST_FALLING_EDGE;
            break;
        }
        default: {
            rq.eventflags = GPIOEVENT_REQUEST_BOTH_EDGES;
            break;
        }
    }

    const int ic = ioctl(fd, GPIO_GET_LINEEVENT_IOCTL, &rq);
    close(fd);
    if (ic < 0) {
        return PIN_DRIVER_ERROR_IOCTL;
    }

    *fileDescriptor = rq.fd;

    return PIN_DRIVER_ERROR_NO;

}

uint8_t readPinEvent(const uint8_t pinNumber) {

    const uint32_t registerSelector = pinNumber / PIN_CONFIG_EVENT_MOD_DIV;
    const uint32_t registerLineREN = registers.GPREN[registerSelector];
    const uint32_t registerLineFEN = registers.GPFEN[registerSelector];
    const uint32_t mask = (PIN_CONFIG_EVENT_MASK << ((pinNumber % PIN_CONFIG_EVENT_MOD_DIV) * PIN_CONFIG_EVENT_MUL));

    uint32_t eventRising = registerLineREN & mask;
    eventRising >>= ((pinNumber % PIN_CONFIG_EVENT_MOD_DIV) * PIN_CONFIG_EVENT_MUL);
    uint32_t eventFalling = registerLineFEN & mask;
    eventFalling >>= ((pinNumber % PIN_CONFIG_EVENT_MOD_DIV) * PIN_CONFIG_EVENT_MUL);
    if ((eventRising & eventFalling) == 1) {
        return PIN_CONFIG_EVENT_BOTH;
    } else if (eventRising == 1) {
        return PIN_CONFIG_EVENT_RISING;
    } else {
        return PIN_CONFIG_EVENT_FALLING;
    }

}

void closePinEvent(const int fileDescriptor) {

    close(fileDescriptor);

}


uint32_t getPinBitField(const uint8_t pinNumber) {

    return 1 << ((pinNumber % 32) * 1);

}

void setPin(const uint32_t pinBitField) {

    registers.GPSET[0] = pinBitField;

}

void clearPin(const uint32_t pinBitField) {

    registers.GPCLR[0] = pinBitField;

}


uint32_t readPin(const uint32_t pinBitField) {

    uint32_t registerLine = registers.GPLEV[0];
    registerLine &= pinBitField;

    return registerLine;

}

PIN_DRIVER_ERROR pollPin(const int fileDescriptor, const int timeoutInMilSec, struct gpioevent_data *const eventData) {

    struct pollfd pfd;

    pfd.fd = fileDescriptor;
    pfd.events = POLLIN | POLLPRI;

    const int rv = poll(&pfd, 1, timeoutInMilSec);
    switch (rv) {
        case -1: {
            return PIN_DRIVER_ERROR_IO_POLL;
        }
        case 0: {
            return PIN_DRIVER_ERROR_IO_POLL_TIMEOUT;
        }
        default: {
            const ssize_t rd = read(pfd.fd, eventData, sizeof(*eventData));
            if (rd <= 0) {
                return PIN_DRIVER_ERROR_FILE;
            } else {
                return PIN_DRIVER_ERROR_NO;
            }
        }
    }

}

