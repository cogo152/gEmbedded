//
// Created by sondahi on 12.01.23.
//

#include "gpiodriver.h"

static GPIO_STATUS setupGpioDriver(void ){

    return GPIO_SUCCESS;
}

static GPIO_STATUS shutdownGpioDriver(void ){


    return GPIO_SUCCESS;
}

void bindGpioBCM2711(void ){
    gpioDriver.setupGpioDriver = setupGpioDriver;
    gpioDriver.shutdownGpioDriver = shutdownGpioDriver;
}

void unbindGpioBCM2711(void ){
    gpioDriver.setupGpioDriver = NULL;
    gpioDriver.shutdownGpioDriver = NULL;
}