//
// Created by sondahi on 23.01.23.
//

#include <linux/gpio.h>
#include <sys/ioctl.h>

#include "pin_config_driver.h"

static struct PinConfigRegs *registers = NULL;

int openPinConfigDriver(void) {

    const int status = requestPinConfigRegs(&registers);
    if (status != PERIPHERAL_EXCEPTION_SUCCESS) {
        return PIN_CONFIG_EXCEPTION_PERIPHERAL_ERROR;
    }

    return PIN_CONFIG_EXCEPTION_SUCCESS;

}

int closePinConfigDriver(void) {

    const int status = releasePinConfigRegs(&registers);
    if (status != PERIPHERAL_EXCEPTION_SUCCESS) {
        return PIN_CONFIG_EXCEPTION_PERIPHERAL_ERROR;
    }

    return PIN_CONFIG_EXCEPTION_SUCCESS;

}

static void setPinFunction(const uint8_t pinNumber, const uint8_t pinFunction) {

    const uint8_t registerSelector = pinNumber / PIN_CONFIG_FUNCTION_MOD_DIV;
    const uint32_t clearValue = ~(PIN_CONFIG_FUNCTION_MASK
            << ((pinNumber % PIN_CONFIG_FUNCTION_MOD_DIV) * PIN_CONFIG_FUNCTION_MUL));
    const uint32_t setValue = pinFunction << ((pinNumber % PIN_CONFIG_FUNCTION_MOD_DIV) * PIN_CONFIG_FUNCTION_MUL);
    registers->FSEL[registerSelector] &= clearValue;
    registers->FSEL[registerSelector] |= setValue;

}

static uint8_t readPinFunction(const uint8_t pinNumber) {

    const uint8_t registerSelector = pinNumber / PIN_CONFIG_FUNCTION_MOD_DIV;
    const uint32_t registerLine = registers->FSEL[registerSelector];
    const uint32_t maskValue =
            PIN_CONFIG_FUNCTION_MASK << ((pinNumber % PIN_CONFIG_FUNCTION_MOD_DIV) * PIN_CONFIG_FUNCTION_MUL);
    uint32_t pinFunction = registerLine & maskValue;
    pinFunction >>= ((pinNumber % PIN_CONFIG_FUNCTION_MOD_DIV) * PIN_CONFIG_FUNCTION_MUL);
    return pinFunction;

}

static void setPinPullUpDown(const uint8_t pinNumber, const uint8_t pullUpDown) {

    const uint8_t registerSelector = pinNumber / PIN_CONFIG_PUD_MOD_DIV;
    const uint32_t clearValue = ~(PIN_CONFIG_PUD_MASK << ((pinNumber % PIN_CONFIG_PUD_MOD_DIV) * PIN_CONFIG_PUD_MUL));
    const uint32_t setValue = (pullUpDown << ((pinNumber % PIN_CONFIG_PUD_MOD_DIV) * PIN_CONFIG_PUD_MUL));
    registers->PUP_PDN[registerSelector] &= clearValue;
    registers->PUP_PDN[registerSelector] |= setValue;

}

static uint8_t readPinPullUpDown(const uint8_t pinNumber) {

    const uint8_t registerSelector = pinNumber / PIN_CONFIG_PUD_MOD_DIV;
    const uint32_t registerLine = registers->PUP_PDN[registerSelector];
    const uint32_t maskValue = (PIN_CONFIG_PUD_MASK << ((pinNumber % PIN_CONFIG_PUD_MOD_DIV) * PIN_CONFIG_PUD_MUL));
    uint32_t pullUpDown = registerLine & maskValue;
    pullUpDown >>= ((pinNumber % PIN_CONFIG_PUD_MOD_DIV) * PIN_CONFIG_PUD_MUL);
    return pullUpDown;

}

static void setPinEvent(const uint8_t pinNumber, const uint8_t pinEvent) {

    const uint8_t registerSelector = pinNumber / PIN_CONFIG_EVENT_MOD_DIV;
    const uint32_t clearValue = ~(PIN_CONFIG_EVENT_MASK
            << ((pinNumber % PIN_CONFIG_EVENT_MOD_DIV) * PIN_CONFIG_EVENT_MUL));
    const uint32_t setValue = (PIN_CONFIG_EVENT_SET << ((pinNumber % PIN_CONFIG_EVENT_MOD_DIV) * PIN_CONFIG_EVENT_MUL));

    registers->REN[registerSelector] &= clearValue;
    registers->FEN[registerSelector] &= clearValue;
    registers->HEN[registerSelector] &= clearValue;
    registers->LEN[registerSelector] &= clearValue;
    registers->AREN[registerSelector] &= clearValue;
    registers->AFEN[registerSelector] &= clearValue;
    registers->EDS[registerSelector] |= setValue;

    switch (pinEvent) {
        case PIN_CONFIG_EVENT_RISING: {
            registers->REN[registerSelector] |= setValue;
            return;
        }
        case PIN_CONFIG_EVENT_FALLING: {
            registers->FEN[registerSelector] |= setValue;
            return;
        }
        default: {
            registers->REN[registerSelector] |= setValue;
            registers->FEN[registerSelector] |= setValue;
            return;
        }
    }

}

static uint8_t readPinEvent(const uint8_t pinNumber) {

    const uint8_t registerSelector = pinNumber / PIN_CONFIG_EVENT_MOD_DIV;
    const uint32_t registerLineREN = registers->REN[registerSelector];
    const uint32_t registerLineFEN = registers->FEN[registerSelector];
    const uint32_t mask = (PIN_CONFIG_EVENT_MASK << ((pinNumber % PIN_CONFIG_EVENT_MOD_DIV) * PIN_CONFIG_EVENT_MUL));
    uint32_t eventRising = registerLineREN & mask;
    eventRising >>= ((pinNumber % PIN_CONFIG_EVENT_MOD_DIV) * PIN_CONFIG_EVENT_MUL);
    uint32_t eventFalling = registerLineFEN & mask;
    eventFalling >>= ((pinNumber % PIN_CONFIG_EVENT_MOD_DIV) * PIN_CONFIG_EVENT_MUL);
    if ((eventRising & eventFalling) == TRUE) {
        return PIN_CONFIG_EVENT_BOTH;
    } else if (eventRising == TRUE) {
        return PIN_CONFIG_EVENT_RISING;
    } else {
        return PIN_CONFIG_EVENT_FALLING;
    }

}

int openOutputPin(struct output_pin_t *outputPin) {

    setPinFunction(outputPin->number, PIN_CONFIG_FUNCTION_OUTPUT);
    const uint8_t _pinFunction = readPinFunction(outputPin->number);
    if (_pinFunction != PIN_CONFIG_FUNCTION_OUTPUT) {
        return PIN_CONFIG_EXCEPTION_FUNCTION_ERROR;
    }

    outputPin->reference = 1 << ((outputPin->number % 32) * 1);

    outputPin->status = PIN_CONFIG_STATUS_OPENED;

    return PIN_CONFIG_EXCEPTION_SUCCESS;

}

void closeOutputPin(struct output_pin_t *outputPin) {

    setPinFunction(outputPin->number, PIN_CONFIG_FUNCTION_INPUT);
    setPinPullUpDown(outputPin->number, PIN_CONFIG_PUD_PULL_DOWN);

    outputPin->status = PIN_CONFIG_STATUS_CLOSED;

}

int openInputPin(struct input_pin_t *inputPin) {

    setPinFunction(inputPin->number, PIN_CONFIG_FUNCTION_INPUT);
    const uint8_t _pinFunction = readPinFunction(inputPin->number);
    if (_pinFunction != PIN_CONFIG_FUNCTION_INPUT) {
        return PIN_CONFIG_EXCEPTION_FUNCTION_ERROR;
    }

    setPinPullUpDown(inputPin->number, inputPin->pullUpDown);
    const uint8_t _pinPullUpDown = readPinPullUpDown(inputPin->number);
    if (_pinPullUpDown != inputPin->pullUpDown) {
        return PIN_CONFIG_EXCEPTION_PULLUPDOWN_ERROR;
    }

    inputPin->reference = 1 << ((inputPin->number % 32) * 1);

    inputPin->status = PIN_CONFIG_STATUS_OPENED;

    return PIN_CONFIG_EXCEPTION_SUCCESS;

}

int updateInputPin(struct input_pin_t *inputPin) {

    closeInputPin(inputPin);

    return openInputPin(inputPin);

}

void closeInputPin(struct input_pin_t *inputPin) {

    setPinPullUpDown(inputPin->number, PIN_CONFIG_PUD_PULL_DOWN);

    inputPin->status = PIN_CONFIG_STATUS_CLOSED;

}

int openListenerPin(struct listener_pin_t *listenerPin) {

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

    const uint8_t _pinFunction = readPinFunction(listenerPin->number);
    if (_pinFunction != PIN_CONFIG_FUNCTION_INPUT) {
        return PIN_CONFIG_EXCEPTION_FUNCTION_ERROR;
    }

    const uint8_t _pinEvent = readPinEvent(listenerPin->number);
    if (_pinEvent != listenerPin->cevent) {
        return PIN_CONFIG_EXCEPTION_EVENT_ERROR;
    }

    listenerPin->reference = rq.fd;

    listenerPin->status = PIN_CONFIG_STATUS_OPENED;

    return PIN_CONFIG_EXCEPTION_SUCCESS;

}

int updateListenerPin(struct listener_pin_t *listenerPin) {

    closeListenerPin(listenerPin);

    return openListenerPin(listenerPin);

}

void closeListenerPin(struct listener_pin_t *listenerPin) {

    close(listenerPin->reference);
    setPinPullUpDown(listenerPin->number, PIN_CONFIG_PUD_PULL_DOWN);

    listenerPin->status = PIN_CONFIG_STATUS_CLOSED;

}

int openAlternatePin(struct alternate_pin_t *const alternatePin) {

    setPinFunction(alternatePin->number, alternatePin->function);
    const uint8_t _pinFunction = readPinFunction(alternatePin->number);
    if (_pinFunction != alternatePin->function) {
        return PIN_CONFIG_EXCEPTION_FUNCTION_ERROR;
    }

    alternatePin->status = PIN_CONFIG_STATUS_OPENED;

    return PIN_CONFIG_EXCEPTION_SUCCESS;

}

int updateAlternatePin(struct alternate_pin_t *const alternatePin) {

    closeAlternatePin(alternatePin);

    return openAlternatePin(alternatePin);

}

void closeAlternatePin(struct alternate_pin_t *const alternatePin) {

    setPinFunction(alternatePin->number, PIN_CONFIG_FUNCTION_INPUT);

    alternatePin->status = PIN_CONFIG_STATUS_CLOSED;

}