//
// Created by sondahi on 26.01.23.
//

#ifndef GEMBEDDED_C_I2C_SLAVE_H
#define GEMBEDDED_C_I2C_SLAVE_H

#include "common.h"

typedef struct i2c_slave {
    uint32_t inputLength;
    uint32_t *inputBuffer;
    uint32_t outputLength;
    uint8_t *outputBuffer;
    uint8_t address;
    uint16_t clockDivider;
    uint32_t clockSpeedInHz;
    uint32_t dataDelay;
    uint16_t fallingDelay;
    uint16_t risingDelay;
    uint16_t clockStretchTimeout;
    volatile uint16_t status;
} i2c_slave_t;

#endif //GEMBEDDED_C_I2C_SLAVE_H
