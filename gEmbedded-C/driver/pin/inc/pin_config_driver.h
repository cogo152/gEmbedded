//
// Created by sondahi on 23.01.23.
//

#ifndef GEMBEDDED_C_PIN_CONFIG_DRIVER_H
#define GEMBEDDED_C_PIN_CONFIG_DRIVER_H

#include "pin.h"
#include "peripheral.h"

#define PIN_CONFIG_EXCEPTION_SUCCESS            (0)
#define PIN_CONFIG_EXCEPTION_PERIPHERAL_ERROR   (-1)
#define PIN_CONFIG_EXCEPTION_FUNCTION_ERROR     (-2)
#define PIN_CONFIG_EXCEPTION_PULLUPDOWN_ERROR   (-3)
#define PIN_CONFIG_EXCEPTION_FILE_ERROR         (-4)
#define PIN_CONFIG_EXCEPTION_IOCTL_ERROR        (-5)
#define PIN_CONFIG_EXCEPTION_EVENT_ERROR        (-6)

#define PIN_CONFIG_STATUS_OPENED                (1)
#define PIN_CONFIG_STATUS_CLOSED                (0)

int openPinConfigDriver(void );

int closePinConfigDriver(void );

int openOutputPin(struct output_pin_t *outputPin);

void closeOutputPin(struct output_pin_t *outputPin);

int openInputPin(struct input_pin_t *inputPin);

int updateInputPin(struct input_pin_t *inputPin);

void closeInputPin(struct input_pin_t *inputPin);

int openListenerPin(struct listener_pin_t *listenerPin);

int updateListenerPin(struct listener_pin_t *listenerPin);

void closeListenerPin(struct listener_pin_t *listenerPin);

int openAlternatePin(struct alternate_pin_t *alternatePin);

int updateAlternatePin(struct alternate_pin_t *alternatePin);

void closeAlternatePin(struct alternate_pin_t *alternatePin);

#endif //GEMBEDDED_C_PIN_CONFIG_DRIVER_H
