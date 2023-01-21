//
// Created by sondahi on 21.01.23.
//

#ifndef GEMBEDDED_C_I2C_TEST_H
#define GEMBEDDED_C_I2C_TEST_H

#include "common_test.h"

#include "i2c_driver.h"
#include "driver_context.h"

#define I2C_SLAVE_ADDRESS               (0x4bU)
#define I2C_SLAVE_CHANNEL               (0b10000000U)

#define I2C_SLAVE_OUTPUT_LENGTH         (1)
#define I2C_SLAVE_INPUT_LENGTH          (1)
#define I2C_SLAVE_CLOCK_SPEED_IN_HZ     (3400000)
#define I2C_SLAVE_FALLING_DELAY         (0x0030)
#define I2C_SLAVE_RISING_DELAY          (0x0030)
#define I2C_SLAVE_CLOCK_STRETCH_TIMEOUT (0x0040)
#define I2C_DEL_DIV(fedl, redl)         (((fedl)<<16) | ((redl)<<0))

#define I2C_SLAVE_EXPECTED_MIN_DATA     (252)

typedef struct i2c_slave_t i2c_slave_t;

i2c_slave_t i2cSlave = {
        .inputLength = I2C_SLAVE_INPUT_LENGTH,
        .inputBuffer = new std::uint32_t [8],
        .outputLength = I2C_SLAVE_OUTPUT_LENGTH,
        .outputBuffer = new std::uint8_t [8] {I2C_SLAVE_CHANNEL},
        .address = I2C_SLAVE_ADDRESS,
        .clockSpeedInHz = I2C_SLAVE_CLOCK_SPEED_IN_HZ,
        .fallingDelay = I2C_SLAVE_FALLING_DELAY,
        .risingDelay = I2C_SLAVE_RISING_DELAY,
        .clockStretchTimeout = I2C_SLAVE_CLOCK_STRETCH_TIMEOUT,
        .status = I2C_SLAVE_CLOSED
};

#endif //GEMBEDDED_C_I2C_TEST_H
