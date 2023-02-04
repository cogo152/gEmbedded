//
// Created by sondahi on 26.01.23.
//

#ifndef GEMBEDDED_C_PIN_DRIVER_H
#define GEMBEDDED_C_PIN_DRIVER_H

#include "pin.h"

#define PIN_DRIVER_EXCEPTION_NO_ERROR               (0)
#define PIN_DRIVER_EXCEPTION_INIT_ERROR             (-1)
#define PIN_DRIVER_EXCEPTION_DESTROY_ERROR          (-2)

#define PIN_CONFIG_EXCEPTION_NO_ERROR               (0)
#define PIN_CONFIG_EXCEPTION_FUNCTION_ERROR         (-1)
#define PIN_CONFIG_EXCEPTION_PULLUPDOWN_ERROR       (-2)
#define PIN_CONFIG_EXCEPTION_FILE_ERROR             (-3)
#define PIN_CONFIG_EXCEPTION_IOCTL_ERROR            (-4)
#define PIN_CONFIG_EXCEPTION_EVENT_ERROR            (-5)

#define PIN_IO_EXCEPTION_NO_ERROR                   (0)
#define PIN_IO_EXCEPTION_POLL_IO_ERROR              (-1)
#define PIN_IO_EXCEPTION_POLL_TIMEOUT_ERROR         (-2)
#define PIN_IO_EXCEPTION_FILE_ERROR                 (-3)

#define PIN_IO_LEVEL_HIGH                           (1)
#define PIN_IO_LEVEL_LOW                            (0)
#define PIN_IO_EVENT_RISING                         (1)
#define PIN_IO_EVENT_FALLING                        (0)

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
