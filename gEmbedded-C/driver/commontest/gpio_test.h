//
// Created by sondahi on 15.01.23.
//

#include "gpio_driver.h"

#ifndef GEMBEDDED_C_GPIO_TEST_H
#define GEMBEDDED_C_GPIO_TEST_H

#include "gpio_driver.h"

#define GPIO_OUTPUT_SELF                    (22)
#define GPIO_OUTPUT_PULLDOWN                (17)
#define GPIO_OUTPUT_PULLUP                  (20)
#define GPIO_OUTPUT_LISTENER                (5)
#define GPIO_INPUT_PULLDOWN                 (27)
#define GPIO_INPUT_PULLUP                   (21)
#define GPIO_LISTENER                       (6)
#define GPIO_ALTERNATE_SELF                 (2)

#define GPIO_SLEEP_IN_MILSEC                (1000)


typedef struct output_pin_t output_pin_t;
typedef struct input_pin_t input_pin_t;
typedef struct listener_pin_t listener_pin_t;
typedef struct alternate_pin_t alternate_pin_t;

output_pin_t outputPin_SELF = {
        .number = GPIO_OUTPUT_SELF,
        .status = GPIO_PIN_CLOSED
};

output_pin_t outputPin_PULLDOWN = {
        .number = GPIO_OUTPUT_PULLDOWN,
        .status = GPIO_PIN_CLOSED
};

output_pin_t outputPin_PULLUP = {
        .number = GPIO_OUTPUT_PULLUP,
        .status = GPIO_PIN_CLOSED
};

output_pin_t outputPin_LISTENER = {
        .number = GPIO_OUTPUT_LISTENER,
        .status = GPIO_PIN_CLOSED
};

input_pin_t inputPin_PULLDOWN = {
        .number = GPIO_INPUT_PULLDOWN,
        .status = GPIO_PIN_CLOSED
};

input_pin_t inputPin_PULLUP = {
        .number = GPIO_INPUT_PULLUP,
        .status = GPIO_PIN_CLOSED
};

listener_pin_t listenerPin = {
        .number = GPIO_LISTENER,
        .status = GPIO_PIN_CLOSED,
        .timeoutInMilSec = GPIO_SLEEP_IN_MILSEC
};

alternate_pin_t alternatePin = {
        .number = GPIO_ALTERNATE_SELF,
        .status = GPIO_PIN_CLOSED
};

#endif //GEMBEDDED_C_GPIO_TEST_H
