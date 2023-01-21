//
// Created by sondahi on 21.01.23.
//

#ifndef GEMBEDDED_C_DRIVER_EXCEPTION_H
#define GEMBEDDED_C_DRIVER_EXCEPTION_H

#define DRIVER_CONTEXT_STATUS_SUCCESS       (0)

#define GPIO_STATUS_SUCCESS                 (-1)
#define GPIO_STATUS_CONFIG_ERROR            (-2)
#define GPIO_STATUS_POLL_IO_ERROR           (-3)
#define GPIO_STATUS_POLL_TIMEOUT_ERROR      (-4)
#define GPIO_STATUS_FILE_IO_ERROR           (-5)

#define I2C_STATUS_SUCCESS                  (-6)
#define I2C_STATUS_CONFIG_ERROR             (-7)
#define I2C_STATUS_NO_ACKNOWLEDGE           (-8)
#define I2C_STATUS_CLOCK_STRETCH_TIMEOUT    (-9)
#define I2C_STATUS_DATA_LOSS                (-10)

#endif //GEMBEDDED_C_DRIVER_EXCEPTION_H
