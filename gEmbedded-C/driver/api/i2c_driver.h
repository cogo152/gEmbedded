//
// Created by sondahi on 21.01.23.
//

#ifndef GEMBEDDED_C_I2C_DRIVER_H
#define GEMBEDDED_C_I2C_DRIVER_H
#ifdef __cplusplus
extern "C" {
#endif

#include "common.h"
#include "driver_exception.h"

// config values

struct i2c_slave_t {
    uint8_t number;
    uint8_t level;
    uint32_t reference;
};

int setupI2cDriver(void);

int shutdownI2cDriver(void);

#ifdef __cplusplus
}
#endif
#endif //GEMBEDDED_C_I2C_DRIVER_H
