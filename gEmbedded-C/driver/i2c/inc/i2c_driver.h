//
// Created by sondahi on 21.01.23.
//

#ifndef GEMBEDDED_C_I2C_DRIVER_H
#define GEMBEDDED_C_I2C_DRIVER_H

#include "i2c_slave.h"

#define I2C_DRIVER_EXCEPTION_NO_EXCEPTION   (0)
#define I2C_DRIVER_EXCEPTION_SETUP_ERROR    (-1)
#define I2C_DRIVER_EXCEPTION_SHUTDOWN_ERROR (-2)
#define I2C_CONFIG_EXCEPTION_NO_EXCEPTION   (-3)
#define I2C_CONFIG_EXCEPTION_NO_SLAVE_ERROR (-4)
#define I2C_IO_EXCEPTION_NO_EXCEPTION       (-5)
#define I2C_IO_EXCEPTION_ACKNOWLEDGE_ERROR  (-6)
#define I2C_IO_EXCEPTION_TIMEOUT_ERROR      (-7)
#define I2C_IO_EXCEPTION_DATA_ERROR         (-8)

int setupI2cDriver(void);

int shutdownI2cDriver(void);

int openSlaveConnection(i2c_slave_t *i2cSlave);

int sendToSlave(i2c_slave_t *i2cSlave);

int receiveFromSlave(i2c_slave_t *i2cSlave);

void closeSlaveConnection(i2c_slave_t *i2cSlave);

#endif //GEMBEDDED_C_I2C_DRIVER_H
