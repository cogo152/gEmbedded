//
// Created by sondahi on 21.01.23.
//

#ifndef GEMBEDDED_C_I2C_TEST_H
#define GEMBEDDED_C_I2C_TEST_H

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

#endif //GEMBEDDED_C_I2C_TEST_H
