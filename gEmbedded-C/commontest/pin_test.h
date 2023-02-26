//
// Created by sondahi on 02.02.23.
//

#ifndef GEMBEDDED_C_PIN_TEST_H
#define GEMBEDDED_C_PIN_TEST_H

#include "common.h"

#define PIN_NUMBER_SELF                           (16)
#define PIN_NUMBER_OUTPUT_LED                     (22)
#define PIN_NUMBER_OUTPUT_PULLDOWN                (17)
#define PIN_NUMBER_OUTPUT_PULLUP                  (23)
#define PIN_NUMBER_OUTPUT_LISTENER                (5)
#define PIN_NUMBER_INPUT_PULLDOWN                 (27)
#define PIN_NUMBER_INPUT_PULLUP                   (24)
#define PIN_NUMBER_LISTENER                       (6)

#define PIN_NUMBER_INVALID                        (45)
#define PIN_NUMBER_VALID                          (PIN_NUMBER_SELF)
#define PIN_PULLUPDOWN_INVALID                    (0b11U)
#define PIN_PULLUPDOWN_VALID                      (0b00U)
#define PIN_EVENT_INVALID                         (0b00U)
#define PIN_EVENT_VALID                           (0b01U)
#define PIN_EVENT_TIMEOUT_INVALID                 (0)
#define PIN_EVENT_TIMEOUT_VALID                   (1)

#define PIN_SLEEP_IN_MILSEC                       (200)

#endif //GEMBEDDED_C_PIN_TEST_H
