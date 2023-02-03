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

int initPinDriver(void) {

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

int destroyPinDriver(void) {

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

void setPinFunction(pin_t *const pin) {

    const uint8_t registerSelector = pin->cNumber / PIN_CONFIG_FUNCTION_MOD_DIV;
    const uint32_t clearValue = ~(PIN_CONFIG_FUNCTION_MASK
            << ((pin->cNumber % PIN_CONFIG_FUNCTION_MOD_DIV) * PIN_CONFIG_FUNCTION_MUL));
    const uint32_t setValue =
            pin->cFunction << ((pin->cNumber % PIN_CONFIG_FUNCTION_MOD_DIV) * PIN_CONFIG_FUNCTION_MUL);
    registers.GPFSEL[registerSelector] &= clearValue;
    registers.GPFSEL[registerSelector] |= setValue;

}

uint8_t getPinFunction(pin_t *const pin) {

    const uint8_t registerSelector = pin->cNumber / PIN_CONFIG_FUNCTION_MOD_DIV;
    const uint32_t registerLine = registers.GPFSEL[registerSelector];
    const uint32_t maskValue =
            PIN_CONFIG_FUNCTION_MASK << ((pin->cNumber % PIN_CONFIG_FUNCTION_MOD_DIV) * PIN_CONFIG_FUNCTION_MUL);
    uint32_t pinFunction = registerLine & maskValue;
    pinFunction >>= ((pin->cNumber % PIN_CONFIG_FUNCTION_MOD_DIV) * PIN_CONFIG_FUNCTION_MUL);

    return pinFunction;

}

void setPinPullUpDown(pin_t *const pin) {

    const uint8_t registerSelector = pin->cNumber / PIN_CONFIG_PUD_MOD_DIV;
    const uint32_t clearValue = ~(PIN_CONFIG_PUD_MASK
            << ((pin->cNumber % PIN_CONFIG_PUD_MOD_DIV) * PIN_CONFIG_PUD_MUL));
    const uint32_t setValue = (pin->cPullUpDown << ((pin->cNumber % PIN_CONFIG_PUD_MOD_DIV) * PIN_CONFIG_PUD_MUL));
    registers.GPPUD[registerSelector] &= clearValue;
    registers.GPPUD[registerSelector] |= setValue;

}

uint8_t getPinPullUpDown(pin_t *const pin) {

    const uint8_t registerSelector = pin->cNumber / PIN_CONFIG_PUD_MOD_DIV;
    const uint32_t registerLine = registers.GPPUD[registerSelector];
    const uint32_t maskValue = (PIN_CONFIG_PUD_MASK << ((pin->cNumber % PIN_CONFIG_PUD_MOD_DIV) * PIN_CONFIG_PUD_MUL));
    uint32_t pullUpDown = registerLine & maskValue;
    pullUpDown >>= ((pin->cNumber % PIN_CONFIG_PUD_MOD_DIV) * PIN_CONFIG_PUD_MUL);

    return pullUpDown;

}

int setPinEvent(pin_t *const pin, uint32_t *const ioReference) {

    const int fd = open(PIN_CONFIG_GPIO_CHIP, O_RDONLY);
    if (fd < 0) {
        return PIN_CONFIG_EXCEPTION_FILE_ERROR;
    }

    struct gpioevent_request rq;
    rq.lineoffset = pin->cNumber;
    rq.handleflags = GPIOHANDLE_REQUEST_INPUT;
    switch (pin->cEvent) {
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

    *ioReference = rq.fd;

    return PIN_CONFIG_EXCEPTION_NO_ERROR;

}

void updatePinEvent(pin_t *const pin) {

    const uint8_t registerSelector = pin->cNumber / PIN_CONFIG_EVENT_MOD_DIV;
    const uint32_t clearValue = ~(PIN_CONFIG_EVENT_MASK << ((pin->cNumber % PIN_CONFIG_EVENT_MOD_DIV) * PIN_CONFIG_EVENT_MUL));
    const uint32_t setValue = (PIN_CONFIG_EVENT_SET << ((pin->cNumber % PIN_CONFIG_EVENT_MOD_DIV) * PIN_CONFIG_EVENT_MUL));

    registers.GPREN[registerSelector] &= clearValue;
    registers.GPFEN[registerSelector] &= clearValue;
    registers.GPHEN[registerSelector] &= clearValue;
    registers.GPLEN[registerSelector] &= clearValue;
    registers.GPAREN[registerSelector] &= clearValue;
    registers.GPAFEN[registerSelector] &= clearValue;
    registers.GPEDS[registerSelector] |= setValue;

    switch (pin->cEvent) {
        case PIN_CONFIG_EVENT_RISING: {
            registers.GPREN[registerSelector] |= setValue;
            registers.GPEDS[registerSelector] |= setValue;
            return;
        }
        case PIN_CONFIG_EVENT_FALLING: {
            registers.GPFEN[registerSelector] |= setValue;
            registers.GPEDS[registerSelector] |= setValue;
            return;
        }
        default: {
            registers.GPREN[registerSelector] |= setValue;
            registers.GPFEN[registerSelector] |= setValue;
            registers.GPEDS[registerSelector] |= setValue;
            return;
        }
    }

}

uint8_t getPinEvent(pin_t *const pin) {

    const uint8_t registerSelector = pin->cNumber / PIN_CONFIG_EVENT_MOD_DIV;
    const uint32_t registerLineREN = registers.GPREN[registerSelector];
    const uint32_t registerLineFEN = registers.GPFEN[registerSelector];
    const uint32_t mask = (PIN_CONFIG_EVENT_MASK << ((pin->cNumber % PIN_CONFIG_EVENT_MOD_DIV) * PIN_CONFIG_EVENT_MUL));
    uint32_t eventRising = registerLineREN & mask;
    eventRising >>= ((pin->cNumber % PIN_CONFIG_EVENT_MOD_DIV) * PIN_CONFIG_EVENT_MUL);
    uint32_t eventFalling = registerLineFEN & mask;
    eventFalling >>= ((pin->cNumber % PIN_CONFIG_EVENT_MOD_DIV) * PIN_CONFIG_EVENT_MUL);
    if ((eventRising & eventFalling) == 1) {
        return PIN_CONFIG_EVENT_BOTH;
    } else if (eventRising == 1) {
        return PIN_CONFIG_EVENT_RISING;
    } else {
        return PIN_CONFIG_EVENT_FALLING;
    }

}

int initOutputPin(pin_t *const pin) {

    setPinFunction(pin);
    const uint8_t pinFunction = getPinFunction(pin);
    if (pinFunction != pin->cFunction) {
        return PIN_CONFIG_EXCEPTION_FUNCTION_ERROR;
    }

    pin->ioReference = 1 << ((pin->cNumber % 32) * 1);
    pin->sState = PIN_STATE_ELIGIBLE;

    return PIN_CONFIG_EXCEPTION_NO_ERROR;

}

void destroyOutputPin(pin_t *const pin) {

    pin->cFunction = PIN_CONFIG_FUNCTION_INPUT;
    pin->cPullUpDown = PIN_CONFIG_PUD_PULL_UP;

    setPinFunction(pin);
    setPinPullUpDown(pin);

    pin->sState = PIN_STATE_INELIGIBLE;

}

int initInputPin(pin_t *const pin) {

    setPinFunction(pin);
    const uint8_t pinFunction = getPinFunction(pin);
    if (pinFunction != pin->cFunction) {
        return PIN_CONFIG_EXCEPTION_FUNCTION_ERROR;
    }

    setPinPullUpDown(pin);
    const uint8_t pinPullUpDown = getPinPullUpDown(pin);
    if (pinPullUpDown != pin->cPullUpDown) {
        return PIN_CONFIG_EXCEPTION_PULLUPDOWN_ERROR;
    }

    pin->ioReference = 1 << ((pin->cNumber % 32) * 1);
    pin->sState = PIN_STATE_ELIGIBLE;

    return PIN_CONFIG_EXCEPTION_NO_ERROR;

}

int updateInputPin(pin_t *const pin) {

    setPinPullUpDown(pin);
    const uint8_t pinPullUpDown = getPinPullUpDown(pin);
    if (pinPullUpDown != pin->cPullUpDown) {
        return PIN_CONFIG_EXCEPTION_PULLUPDOWN_ERROR;
    }

    return PIN_CONFIG_EXCEPTION_NO_ERROR;

}

void destroyInputPin(pin_t *const pin) {

    pin->cPullUpDown = PIN_CONFIG_PUD_PULL_UP;

    setPinPullUpDown(pin);

    pin->sState = PIN_STATE_INELIGIBLE;

}

int initListenerPin(pin_t *const pin) {

    uint32_t ioReference;

    const int status = setPinEvent(pin, &ioReference);
    if (status != PIN_CONFIG_EXCEPTION_NO_ERROR) {
        return status;
    }

    const uint8_t pinFunction = getPinFunction(pin);
    if (pinFunction != pin->cFunction) {
        return PIN_CONFIG_EXCEPTION_FUNCTION_ERROR;
    }

    const uint8_t pinEvent = getPinEvent(pin);
    if (pinEvent != pin->cEvent) {
        return PIN_CONFIG_EXCEPTION_EVENT_ERROR;
    }

    pin->ioReference = ioReference;
    pin->sState = PIN_STATE_ELIGIBLE;

    return PIN_CONFIG_EXCEPTION_NO_ERROR;

}

int updateListenerPin(pin_t *const pin) {

    //destroyListenerPin(pin);
    //return initListenerPin(pin);

    updatePinEvent(pin);

    const uint8_t pinEvent = getPinEvent(pin);
    if (pinEvent != pin->cEvent) {
        return PIN_CONFIG_EXCEPTION_EVENT_ERROR;
    }

    return PIN_CONFIG_EXCEPTION_NO_ERROR;

}


void destroyListenerPin(pin_t *const pin) {

    close((int) pin->ioReference);

    pin->cPullUpDown = PIN_CONFIG_PUD_PULL_UP;

    setPinPullUpDown(pin);

    pin->sState = PIN_STATE_INELIGIBLE;

}

void setPin(pin_t *const pin) {

    registers.GPSET[0] = pin->ioReference;

}

void clearPin(pin_t *const pin) {

    registers.GPCLR[0] = pin->ioReference;
}


void readPin(pin_t *const pin) {

    uint32_t registerLine = registers.GPLEV[0];
    registerLine &= pin->ioReference;

    if (registerLine > 0) {
        pin->ioLevel = PIN_IO_LEVEL_HIGH;
    } else {
        pin->ioLevel = PIN_IO_LEVEL_LOW;
    }

}

int pollPin(pin_t *const pin) {

    struct gpioevent_data data;
    struct pollfd pfd;

    pfd.fd = (int) pin->ioReference;
    pfd.events = POLLIN | POLLPRI;

    const int rv = poll(&pfd, 1, pin->cEventTimeout);
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
                    pin->ioEvent = PIN_IO_EVENT_RISING;
                } else {
                    pin->ioEvent = PIN_IO_EVENT_FALLING;
                }
                pin->ioTimeStamp = data.timestamp;
                return PIN_IO_EXCEPTION_NO_ERROR;
            }
        }
    }

}