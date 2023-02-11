//
// Created by sondahi on 28.01.23.
//

#ifndef GEMBEDDED_C_PIN_VALIDATOR_H
#define GEMBEDDED_C_PIN_VALIDATOR_H

#include "pin.h"

#define PIN_VALIDATOR_ERROR_NO                  (0)
#define PIN_VALIDATOR_ERROR_PIN_TYPE            (-1)
#define PIN_VALIDATOR_ERROR_PIN_NUMBER          (-2)
#define PIN_VALIDATOR_ERROR_PIN_FUNCTION        (-3)
#define PIN_VALIDATOR_ERROR_PIN_PULLUPDOWN      (-4)
#define PIN_VALIDATOR_ERROR_PIN_EVENT           (-5)
#define PIN_VALIDATOR_ERROR_PIN_EVENT_TIMEOUT   (-6)

int validateOutputPin(pin_t *pin);

int validateInputPin(pin_t *pin);

int validateListenerPin(pin_t *pin);

#endif //GEMBEDDED_C_PIN_VALIDATOR_H