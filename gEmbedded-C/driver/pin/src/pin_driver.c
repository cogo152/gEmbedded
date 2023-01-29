//
// Created by sondahi on 26.01.23.
//

#include <linux/gpio.h>
#include <sys/ioctl.h>
#include <sys/poll.h>

#include "pin_driver.h"
#include "peripheral.h"
#include "memory_mapper.h"

static void *base = NULL;
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

int setupPinDriver(void) {

    const int status = mapBaseRegister(MEMORY_FILE_NAME, BLOCK_SIZE, GPIO_BASE_ADDRESS, &base);
    if (status != MAPPER_EXCEPTION_NO_ERROR) {
        return PIN_DRIVER_EXCEPTION_SETUP_ERROR;
    }
    const volatile uintptr_t offset = (uintptr_t) base;

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

    return PIN_DRIVER_EXCEPTION_NO_ERROR;

}

int shutdownPinDriver(void) {

    const int status = unmapBaseRegister(&base, BLOCK_SIZE);
    if (status != MAPPER_EXCEPTION_NO_ERROR) {
        return PIN_DRIVER_EXCEPTION_SHUTDOWN_ERROR;
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

    return PIN_DRIVER_EXCEPTION_NO_ERROR;

}

static void setPinPullUpDown(const uint8_t pinNumber, const uint8_t pullUpDown) {

    const uint8_t registerSelector = pinNumber / PIN_CONFIG_PUD_MOD_DIV;
    const uint32_t clearValue = ~(PIN_CONFIG_PUD_MASK << ((pinNumber % PIN_CONFIG_PUD_MOD_DIV) * PIN_CONFIG_PUD_MUL));
    const uint32_t setValue = (pullUpDown << ((pinNumber % PIN_CONFIG_PUD_MOD_DIV) * PIN_CONFIG_PUD_MUL));
    registers.GPPUD[registerSelector] &= clearValue;
    registers.GPPUD[registerSelector] |= setValue;

}

static uint8_t readPinPullUpDown(const uint8_t pinNumber) {

    const uint8_t registerSelector = pinNumber / PIN_CONFIG_PUD_MOD_DIV;
    const uint32_t registerLine = registers.GPPUD[registerSelector];
    const uint32_t maskValue = (PIN_CONFIG_PUD_MASK << ((pinNumber % PIN_CONFIG_PUD_MOD_DIV) * PIN_CONFIG_PUD_MUL));
    uint32_t pullUpDown = registerLine & maskValue;
    pullUpDown >>= ((pinNumber % PIN_CONFIG_PUD_MOD_DIV) * PIN_CONFIG_PUD_MUL);
    return pullUpDown;

}

static uint32_t readPinLevel(const uint32_t pinReference) {

    uint32_t registerLine = registers.GPLEV[0];
    registerLine &= pinReference;

    return registerLine;

}

static void setPinEvent(const uint8_t pinNumber, const uint8_t pinEvent) {

    const uint8_t registerSelector = pinNumber / PIN_CONFIG_EVENT_MOD_DIV;
    const uint32_t clearValue = ~(PIN_CONFIG_EVENT_MASK
            << ((pinNumber % PIN_CONFIG_EVENT_MOD_DIV) * PIN_CONFIG_EVENT_MUL));
    const uint32_t setValue = (PIN_CONFIG_EVENT_SET << ((pinNumber % PIN_CONFIG_EVENT_MOD_DIV) * PIN_CONFIG_EVENT_MUL));

    registers.GPREN[registerSelector] &= clearValue;
    registers.GPFEN[registerSelector] &= clearValue;
    registers.GPHEN[registerSelector] &= clearValue;
    registers.GPLEN[registerSelector] &= clearValue;
    registers.GPAREN[registerSelector] &= clearValue;
    registers.GPAFEN[registerSelector] &= clearValue;
    registers.GPEDS[registerSelector] |= setValue;

    switch (pinEvent) {
        case PIN_CONFIG_EVENT_RISING: {
            registers.GPREN[registerSelector] |= setValue;
            return;
        }
        case PIN_CONFIG_EVENT_FALLING: {
            registers.GPFEN[registerSelector] |= setValue;
            return;
        }
        default: {
            registers.GPREN[registerSelector] |= setValue;
            registers.GPFEN[registerSelector] |= setValue;
            return;
        }
    }

}

static uint8_t readPinEvent(const uint8_t pinNumber) {

    const uint8_t registerSelector = pinNumber / PIN_CONFIG_EVENT_MOD_DIV;
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

int openOutputPin(output_pin_t *const outputPin) {

    setPinFunction(registers.GPFSEL, outputPin->number, PIN_CONFIG_FUNCTION_OUTPUT);
    const uint8_t _pinFunction = readPinFunction(registers.GPFSEL, outputPin->number);
    if (_pinFunction != PIN_CONFIG_FUNCTION_OUTPUT) {
        return PIN_CONFIG_EXCEPTION_FUNCTION_ERROR;
    }

    outputPin->reference = 1 << ((outputPin->number % 32) * 1);

    return PIN_CONFIG_EXCEPTION_NO_ERROR;

}

/*
void setOutputPinHigh(output_pin_t *const outputPin) {

    registers.GPSET[0] = outputPin->reference;

}
 */

void setOutputPinHigh(int reference){

    registers.GPSET[0] = reference;

}


void readOutputPinLevel(output_pin_t *const outputPin) {

    const uint32_t pinLevel = readPinLevel(outputPin->reference);

    if (pinLevel > 0) {
        outputPin->level = PIN_IO_LEVEL_HIGH;
    } else {
        outputPin->level = PIN_IO_LEVEL_LOW;
    }

}

void setOutputPinLow(output_pin_t *const outputPin) {

    registers.GPCLR[0] = outputPin->reference;
}

void closeOutputPin(output_pin_t *const outputPin) {

    setPinFunction(registers.GPFSEL, outputPin->number, PIN_CONFIG_FUNCTION_INPUT);
    setPinPullUpDown(outputPin->number, PIN_CONFIG_PUD_PULL_DOWN);

}

int openInputPin(input_pin_t *const inputPin) {

    setPinFunction(registers.GPFSEL, inputPin->number, PIN_CONFIG_FUNCTION_INPUT);
    const uint8_t _pinFunction = readPinFunction(registers.GPFSEL, inputPin->number);
    if (_pinFunction != PIN_CONFIG_FUNCTION_INPUT) {
        return PIN_CONFIG_EXCEPTION_FUNCTION_ERROR;
    }

    setPinPullUpDown(inputPin->number, inputPin->pullUpDown);
    const uint8_t _pinPullUpDown = readPinPullUpDown(inputPin->number);
    if (_pinPullUpDown != inputPin->pullUpDown) {
        return PIN_CONFIG_EXCEPTION_PULLUPDOWN_ERROR;
    }

    inputPin->reference = 1 << ((inputPin->number % 32) * 1);

    return PIN_CONFIG_EXCEPTION_NO_ERROR;

}

int updateInputPin(input_pin_t *const inputPin) {

    closeInputPin(inputPin);

    return openInputPin(inputPin);

}

void readInputPinLevel(input_pin_t *const inputPin) {

    const uint32_t pinLevel = readPinLevel(inputPin->reference);

    if (pinLevel > 0) {
        inputPin->level = PIN_IO_LEVEL_HIGH;
    } else {
        inputPin->level = PIN_IO_LEVEL_LOW;
    }

}

void closeInputPin(input_pin_t *const inputPin) {

    setPinPullUpDown(inputPin->number, PIN_CONFIG_PUD_PULL_DOWN);

}

int openListenerPin(listener_pin_t *const listenerPin) {

    const int fd = open(PIN_CONFIG_GPIO_CHIP, O_RDONLY);
    if (fd < 0) {
        return PIN_CONFIG_EXCEPTION_FILE_ERROR;
    }

    struct gpioevent_request rq;
    rq.lineoffset = listenerPin->number;
    rq.handleflags = GPIOHANDLE_REQUEST_INPUT;
    switch (listenerPin->cevent) {
        case PIN_CONFIG_EVENT_RISING: {
            rq.eventflags = GPIOEVENT_EVENT_RISING_EDGE;
            break;
        }
        case PIN_CONFIG_EVENT_FALLING: {
            rq.eventflags = GPIOEVENT_EVENT_FALLING_EDGE;
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
        return PIN_CONFIG_EXCEPTION_IOCTL_ERROR;
    }

    const uint8_t _pinFunction = readPinFunction(registers.GPFSEL, listenerPin->number);
    if (_pinFunction != PIN_CONFIG_FUNCTION_INPUT) {
        return PIN_CONFIG_EXCEPTION_FUNCTION_ERROR;
    }

    const uint8_t _pinEvent = readPinEvent(listenerPin->number);
    if (_pinEvent != listenerPin->cevent) {
        return PIN_CONFIG_EXCEPTION_EVENT_ERROR;
    }

    listenerPin->reference = rq.fd;

    return PIN_CONFIG_EXCEPTION_NO_ERROR;

}

int updateListenerPin(listener_pin_t *const listenerPin) {

    closeListenerPin(listenerPin);

    return openListenerPin(listenerPin);

}

int readListenerPinEvent(listener_pin_t *const listenerPin) {

    struct gpioevent_data data;
    struct pollfd pfd;

    pfd.fd = listenerPin->reference;
    pfd.events = POLLIN | POLLPRI;

    const int rv = poll(&pfd, 1, listenerPin->timeoutInMilSec);
    switch (rv) {
        case -1: {
            return PIN_IO_EXCEPTION_POLL_IO_ERROR;
        }
        case 0: {
            return PIN_IO_EXCEPTION_POLL_TIMEOUT_ERROR;
        }
        default: {
            const ssize_t rd = read(pfd.fd, &data, sizeof(data));
            if (rd <= 0) {
                return PIN_IO_EXCEPTION_FILE_ERROR;
            } else {
                if (data.id == GPIOEVENT_REQUEST_RISING_EDGE) {
                    listenerPin->revent = PIN_IO_EVENT_RISING;
                } else {
                    listenerPin->revent = PIN_IO_EVENT_FALLING;
                }
                listenerPin->timeStamp = data.timestamp;
                return PIN_IO_EXCEPTION_NO_ERROR;
            }
        }
    }

}

void closeListenerPin(listener_pin_t *const listenerPin) {

    close(listenerPin->reference);
    setPinPullUpDown(listenerPin->number, PIN_CONFIG_PUD_PULL_DOWN);

}