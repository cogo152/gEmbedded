//
// Created by sondahi on 21.01.23.
//

#include "i2c_driver.h"
#include "peripheral.h"
#include "memory_mapper.h"

static void *gpioBase = NULL;
static void *bscBase = NULL;

static volatile uintptr_t *GPFSEL = NULL;
static i2c_registers_t registers = {
        .C = NULL,
        .S = NULL,
        .DLEN = NULL,
        .A = NULL,
        .FIFO = NULL,
        .DIV = NULL,
        .DEL = NULL,
        .CLKT = NULL
};

static int openBSCPins();

static void closeBSCPins();


int setupI2cDriver(void) {

    const int gpioBaseStatus = mapBaseRegister(MEMORY_FILE_NAME, BLOCK_SIZE, GPIO_BASE_ADDRESS, &gpioBase);
    if (gpioBaseStatus != MAPPER_EXCEPTION_NO_EXCEPTION) {
        return I2C_DRIVER_EXCEPTION_SETUP_ERROR;
    }

    const int bscBaseStatus = mapBaseRegister(MEMORY_FILE_NAME, BLOCK_SIZE, BSC1_BASE_ADDRESS, &bscBase);
    if (bscBaseStatus != MAPPER_EXCEPTION_NO_EXCEPTION) {
        return I2C_DRIVER_EXCEPTION_SETUP_ERROR;
    }

    const volatile uintptr_t gpioOffset = (uintptr_t) gpioBase;
    GPFSEL = (uintptr_t *) (gpioOffset + GPIO_GPFSEL_OFFSET);

    const volatile uintptr_t i2cOffset = (uintptr_t) bscBase;
    registers.C = (uintptr_t *) (i2cOffset + I2C_C_OFFSET);
    registers.S = (uintptr_t *) (i2cOffset + I2C_S_OFFSET);
    registers.DLEN = (uintptr_t *) (i2cOffset + I2C_DLEN_OFFSET);
    registers.A = (uintptr_t *) (i2cOffset + I2C_A_OFFSET);
    registers.FIFO = (uintptr_t *) (i2cOffset + I2C_FIFO_OFFSET);
    registers.DIV = (uintptr_t *) (i2cOffset + I2C_DIV_OFFSET);
    registers.DEL = (uintptr_t *) (i2cOffset + I2C_DEL_OFFSET);
    registers.CLKT = (uintptr_t *) (i2cOffset + I2C_CLKT_OFFSET);

    const int bscPinsStatus = openBSCPins();
    if (bscPinsStatus != 0) {
        return I2C_DRIVER_EXCEPTION_SETUP_ERROR;
    }

    return I2C_DRIVER_EXCEPTION_NO_EXCEPTION;

}

int shutdownI2cDriver(void) {

    closeBSCPins();

    const int gpioBaseStatus = unmapBaseRegister(&gpioBase, BLOCK_SIZE);
    if (gpioBaseStatus != MAPPER_EXCEPTION_NO_EXCEPTION) {
        return I2C_DRIVER_EXCEPTION_SHUTDOWN_ERROR;
    }

    const int bscBaseStatus = unmapBaseRegister(&bscBase, BLOCK_SIZE);
    if (bscBaseStatus != MAPPER_EXCEPTION_NO_EXCEPTION) {
        return I2C_DRIVER_EXCEPTION_SHUTDOWN_ERROR;
    }

    GPFSEL = NULL;

    registers.C = NULL;
    registers.S = NULL;
    registers.DLEN = NULL;
    registers.A = NULL;
    registers.FIFO = NULL;
    registers.DIV = NULL;
    registers.DEL = NULL;
    registers.CLKT = NULL;

    return I2C_DRIVER_EXCEPTION_NO_EXCEPTION;

}

static int openBSCPins(void) {

    setPinFunction(GPFSEL, BSC1_SDA_PIN, PIN_CONFIG_FUNCTION_ALT0);
    const uint8_t sdaPinFunction = readPinFunction(GPFSEL, BSC1_SDA_PIN);
    if (sdaPinFunction != PIN_CONFIG_FUNCTION_ALT0) {
        return -1;
    }

    setPinFunction(GPFSEL, BSC1_SCL_PIN, PIN_CONFIG_FUNCTION_ALT0);
    const uint8_t sclPinFunction = readPinFunction(GPFSEL, BSC1_SCL_PIN);
    if (sclPinFunction != PIN_CONFIG_FUNCTION_ALT0) {
        return -2;
    }

    return 0;

}

void closeBSCPins(void) {

    setPinFunction(GPFSEL, BSC1_SDA_PIN, PIN_CONFIG_FUNCTION_INPUT);
    setPinFunction(GPFSEL, BSC1_SCL_PIN, PIN_CONFIG_FUNCTION_INPUT);

}

int openSlaveConnection(i2c_slave_t *const i2cSlave) {

    i2cSlave->clockDivider = CORE_CLOCK_SPEED / i2cSlave->clockSpeedInHz;
    i2cSlave->dataDelay = I2C_DEL_DIV(i2cSlave->fallingDelay, i2cSlave->risingDelay);

    const uint32_t outputLength = i2cSlave->outputLength;
    const uint8_t data = i2cSlave->outputBuffer[0];
    const uint32_t inputLength = i2cSlave->inputLength;
    const uint16_t status = i2cSlave->status;

    i2cSlave->inputLength = 1;
    i2cSlave->outputLength = 1;
    i2cSlave->outputBuffer[0] = i2cSlave->address;

    const int sendStatus = sendToSlave(i2cSlave);
    const int receiveStatus = receiveFromSlave(i2cSlave);

    i2cSlave->inputLength = inputLength;
    i2cSlave->outputLength = outputLength;
    i2cSlave->outputBuffer[0] = data;
    i2cSlave->status = status;

    if (sendStatus != I2C_IO_EXCEPTION_NO_EXCEPTION) {
        return I2C_CONFIG_EXCEPTION_NO_SLAVE_ERROR;
    }

    if (receiveStatus != I2C_IO_EXCEPTION_NO_EXCEPTION) {
        return I2C_CONFIG_EXCEPTION_NO_SLAVE_ERROR;
    }

    return I2C_CONFIG_EXCEPTION_NO_EXCEPTION;
}

static void configureSlave(i2c_slave_t *const i2cSlave){

    *registers.A = i2cSlave->address;
    *registers.DIV = i2cSlave->clockDivider;
    *registers.DEL = i2cSlave->dataDelay;
    *registers.CLKT = i2cSlave->clockStretchTimeout;

}

int sendToSlave(i2c_slave_t *const i2cSlave) {

    configureSlave(i2cSlave);

    *registers.DLEN = i2cSlave->outputLength;

    volatile int count = 0;

    *registers.S = I2C_S_CLEAR;
    *registers.C = I2C_C_SEND;

    while (!(*registers.S & I2C_S_DONE)) {
        while (count < i2cSlave->outputLength && *registers.S & I2C_S_TXD) {
            *registers.FIFO = i2cSlave->outputBuffer[count++];
        }
    }

    const volatile uint32_t status = *registers.S;

    if (status & I2C_S_ERR) {
        return I2C_IO_EXCEPTION_ACKNOWLEDGE_ERROR;
    } else if (status & I2C_S_CLKT) {
        return I2C_IO_EXCEPTION_TIMEOUT_ERROR;
    } else if (count < i2cSlave->outputLength) {
        return I2C_IO_EXCEPTION_DATA_ERROR;
    } else {
        return I2C_IO_EXCEPTION_NO_EXCEPTION;
    }

}

int receiveFromSlave(i2c_slave_t *const i2cSlave) {

    configureSlave(i2cSlave);

    *registers.DLEN = i2cSlave->inputLength;

    volatile int count = 0;

    *registers.S = I2C_S_CLEAR;
    *registers.C = I2C_C_RECEIVE;

    while (!(*registers.S & I2C_S_DONE)) {
        while (count < i2cSlave->inputLength && *registers.S & I2C_S_RXD) {
            i2cSlave->inputBuffer[count++] = (*registers.FIFO & 0x000000ff);
        }
    }

    const volatile uint32_t status = *registers.S;

    if (status & I2C_S_ERR) {
        return I2C_IO_EXCEPTION_ACKNOWLEDGE_ERROR;
    } else if (status & I2C_S_CLKT) {
        return I2C_IO_EXCEPTION_TIMEOUT_ERROR;
    } else if (count < i2cSlave->outputLength) {
        return I2C_IO_EXCEPTION_DATA_ERROR;
    } else {
        return I2C_IO_EXCEPTION_NO_EXCEPTION;
    }

}

void closeSlaveConnection(i2c_slave_t *const i2cSlave) {


}
