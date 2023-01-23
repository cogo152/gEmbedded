//
// Created by sondahi on 23.01.23.
//

#include <linux/gpio.h>
#include <sys/poll.h>

#include "pin_io_driver.h"
#include "peripheral.h"

static struct PinIORegs *registers = NULL;

int openPinIODriver(void) {

    const int status = requestPinIORegs(&registers);
    if (status != PERIPHERAL_EXCEPTION_SUCCESS) {
        return PIN_IO_EXCEPTION_PERIPHERAL_ERROR;
    }

    return PIN_IO_EXCEPTION_SUCCESS;

}

int closePinIODriver(void) {

    const int status = releasePinIORegs(&registers);
    if (status != PERIPHERAL_EXCEPTION_SUCCESS) {
        return PIN_IO_EXCEPTION_PERIPHERAL_ERROR;
    }

    return PIN_IO_EXCEPTION_SUCCESS;

}

static uint32_t readPinLevel(const uint32_t pinReference) {

    uint32_t registerLine = registers->LEV[0];
    registerLine &= pinReference;

    return registerLine;

}

void setOutputPinHigh(struct output_pin_t *outputPin) {

    registers->SET[0] = outputPin->reference;

}

void readOutputPinLevel(struct output_pin_t *outputPin) {

    const uint32_t pinLevel = readPinLevel(outputPin->reference);

    if (pinLevel > 0) {
        outputPin->level = PIN_IO_LEVEL_HIGH;
    } else {
        outputPin->level = PIN_IO_LEVEL_LOW;
    }

}

void setOutputPinLow(struct output_pin_t *outputPin) {

    registers->CLR[0] = outputPin->reference;
}

void readInputPinLevel(struct input_pin_t *inputPin) {

    const uint32_t pinLevel = readPinLevel(inputPin->reference);

    if (pinLevel > 0) {
        inputPin->level = PIN_IO_LEVEL_HIGH;
    } else {
        inputPin->level = PIN_IO_LEVEL_LOW;
    }

}

int readListenerPinEvent(struct listener_pin_t *listenerPin) {

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
                return PIN_IO_EXCEPTION_SUCCESS;
            }
        }
    }

}