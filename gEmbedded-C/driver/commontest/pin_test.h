//
// Created by sondahi on 15.01.23.
//

#ifndef GEMBEDDED_C_PIN_TEST_H
#define GEMBEDDED_C_PIN_TEST_H

#include "common_test.h"

extern "C" {
#include "pin_config_driver.h"
#include "pin_io_driver.h"
}

#define PIN_OUTPUT_SELF                    (22)
#define PIN_OUTPUT_PULLDOWN                (17)
#define PIN_OUTPUT_PULLUP                  (20)
#define PIN_OUTPUT_LISTENER                (5)
#define PIN_INPUT_PULLDOWN                 (27)
#define PIN_INPUT_PULLUP                   (21)
#define PIN_LISTENER                       (6)
#define PIN_ALTERNATE_SELF                 (2)

#define PIN_SLEEP_IN_MILSEC                (1000)

typedef struct output_pin_t output_pin_t;
typedef struct input_pin_t input_pin_t;
typedef struct listener_pin_t listener_pin_t;
typedef struct alternate_pin_t alternate_pin_t;

output_pin_t outputPin_SELF = {
        .number = PIN_OUTPUT_SELF
};

output_pin_t outputPin_PULLDOWN = {
        .number = PIN_OUTPUT_PULLDOWN
};

output_pin_t outputPin_PULLUP = {
        .number = PIN_OUTPUT_PULLUP
};

output_pin_t outputPin_LISTENER = {
        .number = PIN_OUTPUT_LISTENER,
};

input_pin_t inputPin_PULLDOWN = {
        .number = PIN_INPUT_PULLDOWN,
};

input_pin_t inputPin_PULLUP = {
        .number = PIN_INPUT_PULLUP,
};

listener_pin_t listenerPin = {
        .number = PIN_LISTENER,
        .timeoutInMilSec = PIN_SLEEP_IN_MILSEC
};

alternate_pin_t alternatePin = {
        .number = PIN_ALTERNATE_SELF,
};

#endif //GEMBEDDED_C_PIN_TEST_H
