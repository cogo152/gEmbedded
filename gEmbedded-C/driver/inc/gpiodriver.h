//
// Created by sondahi on 12.01.23.
//

#ifndef GEMBEDDED_C_GPIODRIVER_H
#define GEMBEDDED_C_GPIODRIVER_H
#ifdef __cplusplus
extern "C" {
#endif

#include "common.h"

typedef enum {
    GPIO_SUCCESS = 0,
    GPIO_ERROR = 1
} GPIO_STATUS;

typedef struct gpio_driver_t{
    GPIO_STATUS (*setupGpioDriver)(void );
    GPIO_STATUS (*shutdownGpioDriver)(void );
}GpioDriver;

extern GpioDriver gpioDriver;

void bindGpioLFS(void );
void unbindGpioLFS(void );
void bindGpioBCM2711(void );
void unbindGpioBCM2711(void );

#ifdef __cplusplus
}
#endif
#endif //GEMBEDDED_C_GPIODRIVER_H
