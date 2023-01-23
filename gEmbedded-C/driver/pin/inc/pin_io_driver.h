//
// Created by sondahi on 23.01.23.
//

#ifndef GEMBEDDED_C_PIN_IO_DRIVER_H
#define GEMBEDDED_C_PIN_IO_DRIVER_H

#include "pin.h"

#define PIN_IO_EXCEPTION_SUCCESS            (0)
#define PIN_IO_EXCEPTION_PERIPHERAL_ERROR   (-1)
#define PIN_IO_EXCEPTION_POLL_IO_ERROR      (-2)
#define PIN_IO_EXCEPTION_POLL_TIMEOUT_ERROR (-3)
#define PIN_IO_EXCEPTION_FILE_ERROR         (-4)


#define PIN_IO_LEVEL_HIGH                   (1)
#define PIN_IO_LEVEL_LOW                    (0)

#define PIN_IO_EVENT_RISING                 (1)
#define PIN_IO_EVENT_FALLING                (0)

int openPinIODriver(void);

int closePinIODriver(void);

void setOutputPinHigh(struct output_pin_t *outputPin);

void readOutputPinLevel(struct output_pin_t *outputPin);

void setOutputPinLow(struct output_pin_t *outputPin);

void readInputPinLevel(struct input_pin_t *inputPin);

int readListenerPinEvent(struct listener_pin_t *listenerPin);

#endif //GEMBEDDED_C_PIN_IO_DRIVER_H
