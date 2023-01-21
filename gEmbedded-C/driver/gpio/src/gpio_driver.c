//
// Created by sondahi on 12.01.23.
//

#include <linux/gpio.h>
#include <sys/ioctl.h>
#include <sys/poll.h>

#include "gpio_peripheral.h"
#include "gpio_driver.h"
#include "memory_mapper.h"

static void *gpioBase = NULL;
static volatile uintptr_t *FSEL = NULL;
static volatile uintptr_t *REN = NULL;
static volatile uintptr_t *FEN = NULL;
static volatile uintptr_t *HEN = NULL;
static volatile uintptr_t *LEN = NULL;
static volatile uintptr_t *AREN = NULL;
static volatile uintptr_t *AFEN = NULL;
static volatile uintptr_t *PUP_PDN = NULL;
static volatile uintptr_t *SET = NULL;
static volatile uintptr_t *CLR = NULL;
static volatile uintptr_t *LEV = NULL;
static volatile uintptr_t *EDS = NULL;

int setupGpioDriver(void) {

    const MAPPER_STATUS mapStatus = mapBaseRegister(MEMORY_FILE_NAME, BLOCK_SIZE, GPIO_BASE_ADDRESS, &gpioBase);
    if (mapStatus != MAPPER_SUCCESS) {
        return GPIO_STATUS_CONFIG_ERROR;
    }

    FSEL = ((uintptr_t *) gpioBase) + FSEL_OFFSET;
    REN = ((uintptr_t *) gpioBase) + REN_OFFSET;
    FEN = ((uintptr_t *) gpioBase) + FEN_OFFSET;
    HEN = ((uintptr_t *) gpioBase) + HEN_OFFSET;
    LEN = ((uintptr_t *) gpioBase) + LEN_OFFSET;
    AREN = ((uintptr_t *) gpioBase) + AREN_OFFSET;
    AFEN = ((uintptr_t *) gpioBase) + AFEN_OFFSET;
    PUP_PDN = ((uintptr_t *) gpioBase) + PUP_PDN_OFFSET;
    SET = ((uintptr_t *) gpioBase + SET_OFFSET);
    CLR = ((uintptr_t *) gpioBase + CLR_OFFSET);
    LEV = ((uintptr_t *) gpioBase + LEV_OFFSET);
    EDS = ((uintptr_t *) gpioBase + EDS_OFFSET);

    return GPIO_STATUS_SUCCESS;

}

int shutdownGpioDriver(void) {

    const MAPPER_STATUS unmapStatus = unmapBaseRegister(&gpioBase, BLOCK_SIZE);
    if (unmapStatus != MAPPER_SUCCESS) {
        return GPIO_STATUS_CONFIG_ERROR;
    }

    FSEL = NULL;
    REN = NULL;
    FEN = NULL;
    HEN = NULL;
    LEN = NULL;
    AREN = NULL;
    AFEN = NULL;
    PUP_PDN = NULL;
    SET = NULL;
    CLR = NULL;
    LEV = NULL;
    EDS = NULL;

    return GPIO_STATUS_SUCCESS;
}

static void setPinFunction(const uint8_t pinNumber, const uint8_t pinFunction) {

    const uint8_t registerSelector = pinNumber / GPIO_PIN_FUNCTION_MOD_DIV;
    const uint32_t clearValue = ~(GPIO_PIN_FUNCTION_MASK
            << ((pinNumber % GPIO_PIN_FUNCTION_MOD_DIV) * GPIO_PIN_FUNCTION_MUL));
    const uint32_t setValue = pinFunction << ((pinNumber % GPIO_PIN_FUNCTION_MOD_DIV) * GPIO_PIN_FUNCTION_MUL);
    FSEL[registerSelector] &= clearValue;
    FSEL[registerSelector] |= setValue;

}

static uint8_t readPinFunction(const uint8_t pinNumber) {

    const uint8_t registerSelector = pinNumber / GPIO_PIN_FUNCTION_MOD_DIV;
    const uint32_t registerLine = FSEL[registerSelector];
    const uint32_t maskValue =
            GPIO_PIN_FUNCTION_MASK << ((pinNumber % GPIO_PIN_FUNCTION_MOD_DIV) * GPIO_PIN_FUNCTION_MUL);
    uint32_t pinFunction = registerLine & maskValue;
    pinFunction >>= ((pinNumber % GPIO_PIN_FUNCTION_MOD_DIV) * GPIO_PIN_FUNCTION_MUL);
    return pinFunction;

}

static void setPinPullUpDown(const uint8_t pinNumber, const uint8_t pullUpDown) {

    const uint8_t registerSelector = pinNumber / GPIO_PIN_PUD_MOD_DIV;
    const uint32_t clearValue = ~(GPIO_PIN_PUD_MASK << ((pinNumber % GPIO_PIN_PUD_MOD_DIV) * GPIO_PIN_PUD_MUL));
    const uint32_t setValue = (pullUpDown << ((pinNumber % GPIO_PIN_PUD_MOD_DIV) * GPIO_PIN_PUD_MUL));
    PUP_PDN[registerSelector] &= clearValue;
    PUP_PDN[registerSelector] |= setValue;

}

static uint8_t readPinPullUpDown(const uint8_t pinNumber) {

    const uint8_t registerSelector = pinNumber / GPIO_PIN_PUD_MOD_DIV;
    const uint32_t registerLine = PUP_PDN[registerSelector];
    const uint32_t maskValue = (GPIO_PIN_PUD_MASK << ((pinNumber % GPIO_PIN_PUD_MOD_DIV) * GPIO_PIN_PUD_MUL));
    uint32_t pullUpDown = registerLine & maskValue;
    pullUpDown >>= ((pinNumber % GPIO_PIN_PUD_MOD_DIV) * GPIO_PIN_PUD_MUL);
    return pullUpDown;

}

static void setPinEvent(const uint8_t pinNumber, const uint8_t pinEvent) {

    const uint8_t registerSelector = pinNumber / GPIO_PIN_EVENT_MOD_DIV;
    const uint32_t clearValue = ~(GPIO_PIN_EVENT_MASK << ((pinNumber % GPIO_PIN_EVENT_MOD_DIV) * GPIO_PIN_EVENT_MUL));
    const uint32_t setValue = (GPIO_PIN_EVENT_SET << ((pinNumber % GPIO_PIN_EVENT_MOD_DIV) * GPIO_PIN_EVENT_MUL));

    *REN &= clearValue;
    *FEN &= clearValue;
    *HEN &= clearValue;
    *LEN &= clearValue;
    *AREN &= clearValue;
    *AFEN &= clearValue;
    *EDS |= setValue;

    switch (pinEvent) {
        case GPIO_PIN_EVENT_RISING: {
            *REN |= setValue;
            return;
        }
        case GPIO_PIN_EVENT_FALLING: {
            *FEN |= setValue;
            return;
        }
        default: {
            *REN |= setValue;
            *FEN |= setValue;
            return;
        }
    }

}

static uint8_t readPinEvent(const uint8_t pinNumber) {

    const uint8_t registerSelector = pinNumber / GPIO_PIN_EVENT_MOD_DIV;
    const uint32_t registerLineREN = REN[registerSelector];
    const uint32_t registerLineFEN = FEN[registerSelector];
    const uint32_t mask = (GPIO_PIN_EVENT_MASK << ((pinNumber % GPIO_PIN_EVENT_MOD_DIV) * GPIO_PIN_EVENT_MUL));
    uint32_t eventRising = registerLineREN & mask;
    eventRising >>= ((pinNumber % GPIO_PIN_EVENT_MOD_DIV) * GPIO_PIN_EVENT_MUL);
    uint32_t eventFalling = registerLineFEN & mask;
    eventFalling >>= ((pinNumber % GPIO_PIN_EVENT_MOD_DIV) * GPIO_PIN_EVENT_MUL);
    if ((eventRising & eventFalling) == TRUE) {
        return GPIO_PIN_EVENT_BOTH;
    } else if (eventRising == TRUE) {
        return GPIO_PIN_EVENT_RISING;
    } else {
        return GPIO_PIN_EVENT_FALLING;
    }

}

static uint32_t readPinLevel(const uint32_t pinReference) {

    uint32_t registerLine = *LEV;
    registerLine &= pinReference;

    return registerLine;

}

int openOutputPin(struct output_pin_t *const outputPin) {

    if (outputPin->status == GPIO_PIN_OPENED) {
        return GPIO_STATUS_CONFIG_ERROR;
    }

    setPinFunction(outputPin->number, GPIO_PIN_FUNCTION_OUTPUT);
    const uint8_t _pinFunction = readPinFunction(outputPin->number);
    if (_pinFunction != GPIO_PIN_FUNCTION_OUTPUT) {
        return GPIO_STATUS_CONFIG_ERROR;
    }

    outputPin->reference = 0b1 << ((outputPin->number % 32) * 1);
    setOutputPinLow(outputPin);

    outputPin->status = GPIO_PIN_OPENED;

    return GPIO_STATUS_SUCCESS;

}

int setOutputPinHigh(struct output_pin_t *const outputPin) {

    if (outputPin->status == GPIO_PIN_CLOSED) {
        return GPIO_STATUS_CONFIG_ERROR;
    }

    *SET = outputPin->reference;

    return GPIO_STATUS_SUCCESS;

}

int readOutputPinLevel(struct output_pin_t *const outputPin) {

    if (outputPin->status == GPIO_PIN_CLOSED) {
        return GPIO_STATUS_CONFIG_ERROR;
    }

    const uint32_t pinLevel = readPinLevel(outputPin->reference);

    if (pinLevel > 0) {
        outputPin->level = GPIO_PIN_LEVEL_HIGH;
    } else {
        outputPin->level = GPIO_PIN_LEVEL_LOW;
    }

    return GPIO_STATUS_SUCCESS;
}

int setOutputPinLow(struct output_pin_t *const outputPin) {

    if (outputPin->status == GPIO_PIN_CLOSED) {
        return GPIO_STATUS_CONFIG_ERROR;
    }

    *CLR = outputPin->reference;

    return GPIO_STATUS_SUCCESS;

}

void closeOutputPin(struct output_pin_t *const outputPin) {

    setOutputPinLow(outputPin);
    setPinFunction(outputPin->number, GPIO_PIN_FUNCTION_INPUT);
    setPinPullUpDown(outputPin->number, GPIO_PIN_PUD_PULL_DOWN);

    outputPin->status = GPIO_PIN_CLOSED;

}

int openInputPin(struct input_pin_t *const inputPin) {

    if (inputPin->status == GPIO_PIN_OPENED) {
        return GPIO_STATUS_CONFIG_ERROR;
    }

    setPinFunction(inputPin->number, GPIO_PIN_FUNCTION_INPUT);
    const uint8_t _pinFunction = readPinFunction(inputPin->number);
    if (_pinFunction != GPIO_PIN_FUNCTION_INPUT) {
        return GPIO_STATUS_CONFIG_ERROR;
    }

    setPinPullUpDown(inputPin->number, inputPin->pullUpDown);
    const uint8_t _pinPullUpDown = readPinPullUpDown(inputPin->number);
    if (_pinPullUpDown != inputPin->pullUpDown) {
        return GPIO_STATUS_CONFIG_ERROR;
    }

    inputPin->reference = 0b1 << ((inputPin->number % 32) * 1);

    inputPin->status = GPIO_PIN_OPENED;

    return GPIO_STATUS_SUCCESS;

}

int updateInputPin(struct input_pin_t *const inputPin) {

    if (inputPin->status == GPIO_PIN_CLOSED) {
        return GPIO_STATUS_CONFIG_ERROR;
    }

    closeInputPin(inputPin);

    return openInputPin(inputPin);

}

int readInputPinLevel(struct input_pin_t *const inputPin) {

    if (inputPin->status == GPIO_PIN_CLOSED) {
        return GPIO_STATUS_CONFIG_ERROR;
    }

    const uint32_t pinLevel = readPinLevel(inputPin->reference);

    if (pinLevel > 0) {
        inputPin->level = GPIO_PIN_LEVEL_HIGH;
    } else {
        inputPin->level = GPIO_PIN_LEVEL_LOW;
    }

    return GPIO_STATUS_SUCCESS;

}

void closeInputPin(struct input_pin_t *const inputPin) {

    setPinPullUpDown(inputPin->number, GPIO_PIN_PUD_PULL_DOWN);

    inputPin->status = GPIO_PIN_CLOSED;

}

int openListenerPin(struct listener_pin_t *const listenerPin) {

    if (listenerPin->status == GPIO_PIN_OPENED) {
        return GPIO_STATUS_CONFIG_ERROR;
    }

    const int fd = open(GPIO_CHIP, O_RDONLY);
    if (fd < 0) {
        return GPIO_STATUS_CONFIG_ERROR;
    }

    struct gpioevent_request rq;
    rq.lineoffset = listenerPin->number;
    rq.handleflags = GPIOHANDLE_REQUEST_INPUT;
    switch (listenerPin->cevent) {
        case GPIO_PIN_EVENT_RISING: {
            rq.eventflags = GPIOEVENT_EVENT_RISING_EDGE;
            break;
        }
        case GPIO_PIN_EVENT_FALLING: {
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
        return GPIO_STATUS_CONFIG_ERROR;
    }

    const uint8_t _pinFunction = readPinFunction(listenerPin->number);
    if (_pinFunction != GPIO_PIN_FUNCTION_INPUT) {
        return GPIO_STATUS_CONFIG_ERROR;
    }

    const uint8_t _pinEvent = readPinEvent(listenerPin->number);
    if (_pinEvent != listenerPin->cevent) {
        return GPIO_STATUS_CONFIG_ERROR;
    }

    listenerPin->reference = rq.fd;

    listenerPin->status = GPIO_PIN_OPENED;

    return GPIO_STATUS_SUCCESS;

}

int updateListenerPin(struct listener_pin_t *const listenerPin) {

    if (listenerPin->status == GPIO_PIN_CLOSED) {
        return GPIO_STATUS_CONFIG_ERROR;
    }

    closeListenerPin(listenerPin);

    return openListenerPin(listenerPin);

}

int readListenerPinEvent(struct listener_pin_t *const listenerPin) {

    if (listenerPin->status == GPIO_PIN_CLOSED) {
        return GPIO_STATUS_CONFIG_ERROR;
    }

    struct gpioevent_data data;
    struct pollfd pfd;

    pfd.fd = listenerPin->reference;
    pfd.events = POLLIN | POLLPRI;

    const int rv = poll(&pfd, 1, listenerPin->timeoutInMilSec);
    switch (rv) {
        case -1: {
            return GPIO_STATUS_POLL_IO_ERROR;
        }
        case 0: {
            return GPIO_STATUS_POLL_TIMEOUT_ERROR;
        }
        default: {
            const ssize_t rd = read(pfd.fd, &data, sizeof(data));
            if (rd <= 0) {
                return GPIO_STATUS_FILE_IO_ERROR;
            } else {
                if (data.id == GPIOEVENT_REQUEST_RISING_EDGE) {
                    listenerPin->revent = GPIO_PIN_EVENT_RISING;
                } else {
                    listenerPin->revent = GPIO_PIN_EVENT_FALLING;
                }
                listenerPin->timeStamp = data.timestamp;
                return GPIO_STATUS_SUCCESS;
            }
        }
    }

}

void closeListenerPin(struct listener_pin_t *const listenerPin) {

    close(listenerPin->reference);
    setPinPullUpDown(listenerPin->number, GPIO_PIN_PUD_PULL_DOWN);

    listenerPin->status = GPIO_PIN_CLOSED;

}

int openAlternatePin(struct alternate_pin_t *const alternatePin) {

    if (alternatePin->status == GPIO_PIN_OPENED) {
        return GPIO_STATUS_CONFIG_ERROR;
    }

    setPinFunction(alternatePin->number, alternatePin->function);
    const uint8_t _pinFunction = readPinFunction(alternatePin->number);
    if (_pinFunction != alternatePin->function) {
        return GPIO_STATUS_CONFIG_ERROR;
    }

    alternatePin->status = GPIO_PIN_OPENED;

    return GPIO_STATUS_SUCCESS;

}

int updateAlternatePin(struct alternate_pin_t *const alternatePin) {

    if (alternatePin->status == GPIO_PIN_CLOSED) {
        return GPIO_STATUS_CONFIG_ERROR;
    }

    closeAlternatePin(alternatePin);

    return openAlternatePin(alternatePin);

}

void closeAlternatePin(struct alternate_pin_t *const alternatePin) {

    setPinFunction(alternatePin->number, GPIO_PIN_FUNCTION_INPUT);

    alternatePin->status = GPIO_PIN_CLOSED;

}