//
// Created by sondahi on 26.01.23.
//

#ifndef GEMBEDDED_C_PIN_DRIVER_H
#define GEMBEDDED_C_PIN_DRIVER_H

#include "pin.h"

#define PIN_DRIVER_EXCEPTION_NO_EXCEPTION       (0)
#define PIN_DRIVER_EXCEPTION_SETUP_ERROR        (-1)
#define PIN_DRIVER_EXCEPTION_SHUTDOWN_ERROR     (-2)
#define PIN_CONFIG_EXCEPTION_NO_EXCEPTION       (-3)
#define PIN_CONFIG_EXCEPTION_FUNCTION_ERROR     (-4)
#define PIN_CONFIG_EXCEPTION_PULLUPDOWN_ERROR   (-5)
#define PIN_CONFIG_EXCEPTION_FILE_ERROR         (-6)
#define PIN_CONFIG_EXCEPTION_IOCTL_ERROR        (-7)
#define PIN_CONFIG_EXCEPTION_EVENT_ERROR        (-8)
#define PIN_IO_EXCEPTION_NO_EXCEPTION           (-9)
#define PIN_IO_EXCEPTION_POLL_IO_ERROR          (-10)
#define PIN_IO_EXCEPTION_POLL_TIMEOUT_ERROR     (-11)
#define PIN_IO_EXCEPTION_FILE_ERROR             (-12)

#define PIN_IO_LEVEL_HIGH                       (1)
#define PIN_IO_LEVEL_LOW                        (0)
#define PIN_IO_EVENT_RISING                     (1)
#define PIN_IO_EVENT_FALLING                    (0)

int setupPinDriver(void);

int shutdownPinDriver(void);

int openOutputPin(output_pin_t *outputPin);

void setOutputPinHigh(output_pin_t *outputPin);

void readOutputPinLevel(output_pin_t *outputPin);

void setOutputPinLow(output_pin_t *outputPin);

void closeOutputPin(output_pin_t *outputPin);

int openInputPin(input_pin_t *inputPin);

int updateInputPin(input_pin_t *inputPin);

void readInputPinLevel(input_pin_t *inputPin);

void closeInputPin(input_pin_t *inputPin);

int openListenerPin(listener_pin_t *listenerPin);

int updateListenerPin(listener_pin_t *listenerPin);

int readListenerPinEvent(listener_pin_t *listenerPin);

void closeListenerPin(listener_pin_t *listenerPin);

#endif //GEMBEDDED_C_PIN_DRIVER_H
