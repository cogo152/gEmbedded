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

#define I2C_SLAVE_OPENED    (1)
#define I2C_SLAVE_CLOSED    (0)

// config values
struct i2c_slave_t {
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
};

int setupI2cDriver(void);

int shutdownI2cDriver(void);

int openSlaveConnection(struct i2c_slave_t *i2cSlave);

int sendToSlave(struct i2c_slave_t *i2cSlave);

int receiveFromSlave(struct i2c_slave_t *i2cSlave);

void closeSlaveConnection(struct i2c_slave_t *i2cSlave);

#ifdef __cplusplus
}
#endif
#endif //GEMBEDDED_C_I2C_DRIVER_H
