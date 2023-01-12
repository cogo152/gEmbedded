//
// Created by sondahi on 12.01.23.
//

#include "gpiodriver.h"

static GPIO_STATUS setupGpioDriver(void ){

    printf("setup in lfs\n");

    return GPIO_SUCCESS;
}

static GPIO_STATUS shutdownGpioDriver(void ){

    printf("shutdown in lfs\n");

    return GPIO_SUCCESS;
}



void bindGpioLFS(void ){
    gpioDriver.setupGpioDriver = setupGpioDriver;
    gpioDriver.shutdownGpioDriver = shutdownGpioDriver;
}

void unbindGpioLFS(void ){
    gpioDriver.setupGpioDriver = NULL;
    gpioDriver.shutdownGpioDriver = NULL;
}