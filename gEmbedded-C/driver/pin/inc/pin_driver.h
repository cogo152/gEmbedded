//
// Created by sondahi on 26.01.23.
//

#ifndef GEMBEDDED_C_PIN_DRIVER_H
#define GEMBEDDED_C_PIN_DRIVER_H

#include "pin.h"
#include "pin_status.h"

int initPinDriver(void);

int destroyPinDriver(void);

int initOutputPin(pin_t *pin);

void destroyOutputPin(pin_t *pin);

int initInputPin(pin_t *pin);

int updateInputPin(pin_t *pin);

void destroyInputPin(pin_t *pin);

int initListenerPin(pin_t *pin);

int updateListenerPin(pin_t *pin);

void destroyListenerPin(pin_t *pin);

void setPin(pin_t *pin);

void clearPin(pin_t *pin);

void readPin(pin_t *pin);

int pollPin(pin_t *pin);

#endif //GEMBEDDED_C_PIN_DRIVER_H
