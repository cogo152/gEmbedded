//
// Created by sondahi on 26.01.23.
//

#ifndef GEMBEDDED_C_PIN_DRIVER_H
#define GEMBEDDED_C_PIN_DRIVER_H

#include "pin.h"

#define PIN_DRIVER_ERROR_NO                 (0)
#define PIN_DRIVER_ERROR_MAP                (-1)
#define PIN_DRIVER_ERROR_UNMAP              (-2)
#define PIN_DRIVER_ERROR_PIN_FUNCTION       (-3)
#define PIN_DRIVER_ERROR_PIN_PULLUPDOWN     (-4)
#define PIN_DRIVER_ERROR_PIN_EVENT          (-5)
#define PIN_DRIVER_ERROR_FILE               (-6)
#define PIN_DRIVER_ERROR_IOCTL              (-7)
#define PIN_DRIVER_ERROR_IO_STATE           (-8)
#define PIN_DRIVER_ERROR_IO_POLL            (-9)
#define PIN_DRIVER_ERROR_IO_POLL_TIMEOUT    (-10)
#define PIN_DRIVER_PIN_STATE_ELIGIBLE       (1)
#define PIN_DRIVER_PIN_STATE_INELIGIBLE     (0)
#define PIN_DRIVER_IO_LEVEL_HIGH            (1)
#define PIN_DRIVER_IO_LEVEL_LOW             (0)
#define PIN_DRIVER_IO_EVENT_RISING          (1)
#define PIN_DRIVER_IO_EVENT_FALLING         (0)

int initPinDriver(void);

int destroyPinDriver(void);

int initOutputPin(pin_t *pin);

int destroyOutputPin(pin_t *pin);

int initInputPin(pin_t *pin);

int updateInputPin(pin_t *pin);

int destroyInputPin(pin_t *pin);

int initListenerPin(pin_t *pin);

int updateListenerPin(pin_t *pin);

int destroyListenerPin(pin_t *pin);

int setPin(pin_t *pin);

int clearPin(pin_t *pin);

int readPin(pin_t *pin);

int pollPin(pin_t *pin);

#endif //GEMBEDDED_C_PIN_DRIVER_H
