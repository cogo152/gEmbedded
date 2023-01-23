//
// Created by sondahi on 21.01.23.
//

#include "driver_context.h"
#include "pin_config_driver.h"
#include "pin_io_driver.h"
#include "i2c_driver.h"

int setupDrivers(void) {

    const int gpioStatus = setupGpioDriver();
    if (gpioStatus != GPIO_STATUS_SUCCESS) {
        return gpioStatus;
    }

    const int i2cStatus = setupI2cDriver();
    if (i2cStatus != I2C_STATUS_SUCCESS) {
        return i2cStatus;
    }

    return DRIVER_CONTEXT_STATUS_SUCCESS;

}

int shutdownDrivers(void) {

    const int i2cStatus = shutdownI2cDriver();
    if (i2cStatus != I2C_STATUS_SUCCESS) {
        return i2cStatus;
    }

    const int gpioStatus = shutdownGpioDriver();
    if (gpioStatus != GPIO_STATUS_SUCCESS) {
        return gpioStatus;
    }

    return DRIVER_CONTEXT_STATUS_SUCCESS;

}