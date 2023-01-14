//
// Created by sondahi on 12.01.23.
//

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/gpio.h>
#include <string.h>

#include "gpiodriver.h"
#include "lfs_gpio.h"

static volatile uint8_t initialized = FALSE;

static int *pins;

static GPIO_CONFIG_STATUS setupGpioDriver(void) {

    if (initialized == TRUE) {
        return GPIO_CONFIG_ERROR;
    }

    int fd = open(GPIO_DEV, O_RDWR);
    if (fd < 0) {
        return GPIO_CONFIG_ERROR;
    } else {
        close(fd);
    }

    pins = (int *) malloc(SIZE * sizeof(int));
    if (pins == NULL) {
        return GPIO_CONFIG_ERROR;
    }

    initialized = TRUE;

    return GPIO_CONFIG_SUCCESS;

}

static GPIO_CONFIG_STATUS shutdownGpioDriver(void) {

    if (initialized == FALSE) {
        return GPIO_CONFIG_ERROR;
    }

    free((void *) pins);

    initialized = FALSE;

    return GPIO_CONFIG_SUCCESS;
}


static GPIO_CONFIG_STATUS openOutputPin(uint8_t pinNumber) {

    if (initialized == FALSE) {
        return GPIO_CONFIG_ERROR;
    }

    const int fd = open(GPIO_DEV, O_RDWR);
    if (fd < 0) {
        return GPIO_CONFIG_ERROR;
    }

    struct gpiohandle_request req;

    req.flags = GPIOHANDLE_REQUEST_OUTPUT;
    req.lines = 1;
    req.lineoffsets[0] = pinNumber;
    req.default_values[0] = PIN_LEVEL_LOW;

    const int rv = ioctl(fd, GPIO_GET_LINEHANDLE_IOCTL, &req);
    close(fd);

    if (rv < 0) {
        return GPIO_CONFIG_ERROR;
    }

    pins[pinNumber] = req.fd;

    return GPIO_CONFIG_SUCCESS;

}

static GPIO_CONFIG_STATUS registerOutputPin(uint8_t pinNumber, uint8_t *pinReference) {

    if (initialized == FALSE) {
        return GPIO_CONFIG_ERROR;
    }

    *pinReference = pinNumber;

    return GPIO_CONFIG_SUCCESS;
}

static GPIO_IO_STATUS setHighOutputPin(uint8_t pinReference) {

    if (initialized == FALSE) {
        return GPIO_IO_ERROR;
    }

    struct gpiohandle_data data;

    data.values[0] = PIN_LEVEL_HIGH;

    const int rv = ioctl(pins[pinReference], GPIOHANDLE_SET_LINE_VALUES_IOCTL, &data);
    if (rv < 0) {
        return GPIO_IO_ERROR;
    }

    return GPIO_IO_SUCCESS;
}

static GPIO_IO_STATUS readOutputPin(uint8_t pinReference, uint8_t *pinLevel) {

    if (initialized == FALSE) {
        return GPIO_IO_ERROR;
    }

    struct gpiohandle_data data;
    const int rv = ioctl(pins[pinReference], GPIOHANDLE_GET_LINE_VALUES_IOCTL,&data);
    if (rv < 0) {
        return GPIO_IO_ERROR;
    }

    if(data.values[0] == PIN_LEVEL_HIGH){
        *pinLevel = PIN_LEVEL_HIGH;
    } else {
        *pinLevel = PIN_LEVEL_LOW;
    }

    return GPIO_IO_SUCCESS;
}

static GPIO_IO_STATUS setLowOutputPin(uint8_t pinReference) {

    if (initialized == FALSE) {
        return GPIO_IO_ERROR;
    }

    struct gpiohandle_data data;
    data.values[0] = PIN_LEVEL_LOW;

    const int rv = ioctl(pins[pinReference], GPIOHANDLE_SET_LINE_VALUES_IOCTL, &data);
    if (rv < 0) {
        return GPIO_IO_ERROR;
    }

    return GPIO_IO_SUCCESS;

}

static GPIO_CONFIG_STATUS closeOutputPin(uint8_t pinReference) {

    if (initialized == FALSE) {
        return GPIO_CONFIG_ERROR;
    }

    close(pins[pinReference]);

    return GPIO_CONFIG_SUCCESS;
}

void bindGpioLFS(void) {

    gpioDriver.setupGpioDriver = setupGpioDriver;
    gpioDriver.shutdownGpioDriver = shutdownGpioDriver;
    gpioDriver.openOutputPin = openOutputPin;
    gpioDriver.registerOutputPin = registerOutputPin;
    gpioDriver.setHighOutputPin = setHighOutputPin;
    gpioDriver.readOutputPin = readOutputPin;
    gpioDriver.setLowOutputPin = setLowOutputPin;
    gpioDriver.closeOutputPin = closeOutputPin;

}

void unbindGpioLFS(void) {

    gpioDriver.setupGpioDriver = NULL;
    gpioDriver.shutdownGpioDriver = NULL;
    gpioDriver.openOutputPin = NULL;
    gpioDriver.registerOutputPin = NULL;
    gpioDriver.setHighOutputPin = NULL;
    gpioDriver.readOutputPin = NULL;
    gpioDriver.setLowOutputPin = NULL;
    gpioDriver.closeOutputPin = NULL;

}