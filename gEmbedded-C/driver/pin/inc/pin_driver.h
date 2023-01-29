//
// Created by sondahi on 26.01.23.
//

#ifndef GEMBEDDED_C_PIN_DRIVER_H
#define GEMBEDDED_C_PIN_DRIVER_H

#include "pin.h"
#include "pin_exception.h"

#define PIN_IO_LEVEL_HIGH                       (1)
#define PIN_IO_LEVEL_LOW                        (0)
#define PIN_IO_EVENT_RISING                     (1)
#define PIN_IO_EVENT_FALLING                    (0)

int setupPinDriver(void);

int shutdownPinDriver(void);

int openOutputPin(output_pin_t *outputPin);

//void setOutputPinHigh(output_pin_t *outputPin);
void setOutputPinHigh(int reference);

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
