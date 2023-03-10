//
// Created by sondahi on 26.01.23.
//

#ifndef GEMBEDDED_C_PIN_DRIVER_H
#define GEMBEDDED_C_PIN_DRIVER_H

#include <linux/gpio.h>

#include "common.h"

typedef enum {
    PIN_DRIVER_ERROR_NO = 0,
    PIN_DRIVER_ERROR_MAP = 1300,
    PIN_DRIVER_ERROR_UNMAP = 1301,
    PIN_DRIVER_ERROR_FILE = 1302,
    PIN_DRIVER_ERROR_IOCTL = 1303,
    PIN_DRIVER_ERROR_IO_POLL = 1304,
    PIN_DRIVER_ERROR_IO_POLL_TIMEOUT = 1305
} PIN_DRIVER_ERROR;

PIN_DRIVER_ERROR initPinDriver(void);

PIN_DRIVER_ERROR destroyPinDriver(void);

void setPinFunction(uint8_t pinNumber, uint8_t pinFunction);

uint8_t readPinFunction(uint8_t pinNumber);

void setPinPullUpDown(uint8_t pinNumber, uint8_t pinPullUpDown);

uint8_t readPinPullUpDown(uint8_t pinNumber);

PIN_DRIVER_ERROR setPinEvent(uint8_t pinNumber, uint8_t pinPullUpDown, uint8_t pinEvent, int *fileDescriptor);

uint8_t readPinEvent(uint8_t pinNumber);

void closePinEvent(int fileDescriptor);

uint32_t getPinBitField(uint8_t pinNumber);

void setPin(uint32_t pinBitField);

void clearPin(uint32_t pinBitField);

uint32_t readPin(uint32_t pinBitField);

PIN_DRIVER_ERROR pollPin(int fileDescriptor, int timeoutInMilSec, struct gpioevent_data *eventData);

#endif //GEMBEDDED_C_PIN_DRIVER_H
