//
// Created by sondahi on 03.01.23.
//

#ifndef GEMBEDDED_C_PIN_H
#define GEMBEDDED_C_PIN_H

typedef enum {
    PIN_TYPE_GPIO = 0,
    PIN_TYPE_CLOCK = 1,
    PIN_TYPE_PWM = 2,
    PIN_TYPE_I2C = 3,
    PIN_TYPE_SPI = 4,
    PIN_TYPE_UART = 5
} PIN_TYPE;

typedef enum {
    PIN_0 = 0,
    PIN_1 = 1,
    PIN_2 = 2,
    PIN_3 = 3,
    PIN_4 = 4,
    PIN_5 = 5,
    PIN_6 = 6,
    PIN_7 = 7,
    PIN_8 = 8,
    PIN_9 = 9,
    PIN_10 = 10,
    PIN_11 = 11,
    PIN_12 = 12,
    PIN_13 = 13,
    PIN_14 = 14,
    PIN_15 = 15,
    PIN_16 = 16,
    PIN_17 = 17,
    PIN_18 = 18,
    PIN_19 = 19,
    PIN_20 = 20,
    PIN_21 = 21,
    PIN_22 = 22,
    PIN_23 = 23,
    PIN_24 = 24,
    PIN_25 = 25,
    PIN_26 = 26,
    PIN_27 = 27,
    PIN_28 = 28,
    PIN_29 = 29,
    PIN_30 = 30,
    PIN_31 = 31,
    PIN_32 = 32
} PIN;

typedef enum {
    PIN_FUNCTION_INPUT = 0b000,
    PIN_FUNCTION_OUTPUT = 0b001,
    PIN_FUNCTION_ALT_0 = 0b100,
    PIN_FUNCTION_ALT_1 = 0b101,
    PIN_FUNCTION_ALT_2 = 0b110,
    PIN_FUNCTION_ALT_3 = 0b111,
    PIN_FUNCTION_ALT_4 = 0b011,
    PIN_FUNCTION_ALT_5 = 0b010,
} PIN_FUNCTION;

typedef enum {
    PULL_UP_DOWN_NO_RESISTOR = 0b00,
    PULL_UP_DOWN_PULL_UP = 0b01,
    PULL_UP_DOWN_PULL_DOWN = 0b10,
    PULL_UP_DOWN_RESERVED = 0b11,
} PULL_UP_DOWN;

typedef enum {
    PIN_EVENT_NO_EVENT = 0b00,
    PIN_EVENT_RISING = 0b01,
    PIN_EVENT_FALLING = 0b10,
    PIN_EVENT_BOTH = 0b11
} PIN_EVENT;

#endif //GEMBEDDED_C_PIN_H
