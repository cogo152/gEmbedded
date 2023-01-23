//
// Created by sondahi on 21.01.23.
//

#include "i2c_peripheral.h"
#include "i2c_driver.h"
#include "gpio_driver.txt"
#include "memory_mapper.h"

static struct alternate_pin_t sdaPin;
static struct alternate_pin_t sclPin;

static void *i2cMasterBase = NULL;
static volatile uintptr_t *C = NULL;
static volatile uintptr_t *S = NULL;
static volatile uintptr_t *DLEN = NULL;
static volatile uintptr_t *A = NULL;
static volatile uintptr_t *FIFO = NULL;
static volatile uintptr_t *DIV = NULL;
static volatile uintptr_t *DEL = NULL;
static volatile uintptr_t *CLKT = NULL;

int setupI2cDriver(void) {

    const MAPPER_STATUS mapStatus = mapBaseRegister(MEMORY_FILE_NAME, BLOCK_SIZE, I2CMASTER_BASE_ADDRESS,
                                                    &i2cMasterBase);
    if (mapStatus != MAPPER_SUCCESS) {
        return I2C_STATUS_CONFIG_ERROR;
    }

    sdaPin.number = I2CMASTER_SDA_PIN;
    sdaPin.function = GPIO_PIN_FUNCTION_ALT0;

    sclPin.number = I2CMASTER_SCL_PIN;
    sclPin.function = GPIO_PIN_FUNCTION_ALT0;

    const int sdaPinStatus = openAlternatePin(&sdaPin);
    if (sdaPinStatus != GPIO_STATUS_SUCCESS) {
        return I2C_STATUS_CONFIG_ERROR;
    }

    const int sclPinStatus = openAlternatePin(&sclPin);
    if (sclPinStatus != GPIO_STATUS_SUCCESS) {
        return I2C_STATUS_CONFIG_ERROR;
    }

    C = ((uintptr_t *) i2cMasterBase) + I2C_C_OFFSET;
    S = ((uintptr_t *) i2cMasterBase) + I2C_S_OFFSET;
    DLEN = ((uintptr_t *) i2cMasterBase) + I2C_DLEN_OFFSET;
    A = ((uintptr_t *) i2cMasterBase) + I2C_A_OFFSET;
    FIFO = ((uintptr_t *) i2cMasterBase) + I2C_FIFO_OFFSET;
    DIV = ((uintptr_t *) i2cMasterBase) + I2C_DIV_OFFSET;
    DEL = ((uintptr_t *) i2cMasterBase) + I2C_DEL_OFFSET;
    CLKT = ((uintptr_t *) i2cMasterBase) + I2C_CLKT_OFFSET;

    return I2C_STATUS_SUCCESS;

}

int shutdownI2cDriver(void) {

    const MAPPER_STATUS unmapStatus = unmapBaseRegister(&i2cMasterBase, BLOCK_SIZE);
    if (unmapStatus != MAPPER_SUCCESS) {
        return I2C_STATUS_CONFIG_ERROR;
    }

    C = NULL;
    S = NULL;
    DLEN = NULL;
    A = NULL;
    FIFO = NULL;
    DIV = NULL;
    DEL = NULL;
    CLKT = NULL;

    closeAlternatePin(&sdaPin);
    closeAlternatePin(&sclPin);

    return I2C_STATUS_SUCCESS;

}

int openSlaveConnection(struct i2c_slave_t *const i2cSlave) {

    if (i2cSlave->status == I2C_SLAVE_OPENED) {
        return I2C_STATUS_CONFIG_ERROR;
    }

    i2cSlave->clockDivider = CORE_CLOCK_SPEED / i2cSlave->clockSpeedInHz;
    i2cSlave->dataDelay = I2C_DEL_DIV(i2cSlave->fallingDelay, i2cSlave->risingDelay);

    const uint32_t outputLength = i2cSlave->outputLength;
    const uint8_t data = i2cSlave->outputBuffer[0];
    const uint32_t inputLength = i2cSlave->inputLength;
    const uint16_t status = i2cSlave->status;

    i2cSlave->inputLength = 1;
    i2cSlave->outputLength = 1;
    i2cSlave->outputBuffer[0] = i2cSlave->address;
    i2cSlave->status = I2C_SLAVE_OPENED;

    const int sendStatus = sendToSlave(i2cSlave);
    const int receiveStatus = receiveFromSlave(i2cSlave);

    i2cSlave->inputLength = inputLength;
    i2cSlave->outputLength = outputLength;
    i2cSlave->outputBuffer[0] = data;
    i2cSlave->status = status;

    if (sendStatus != I2C_STATUS_SUCCESS) {
        return I2C_STATUS_CONFIG_ERROR;
    }

    if (receiveStatus != I2C_STATUS_SUCCESS) {
        return I2C_STATUS_CONFIG_ERROR;
    }

    i2cSlave->status = I2C_SLAVE_OPENED;

    return I2C_STATUS_SUCCESS;
}

int sendToSlave(struct i2c_slave_t *const i2cSlave) {

    if (i2cSlave->status == I2C_SLAVE_CLOSED) {
        return I2C_STATUS_CONFIG_ERROR;
    }

    volatile int count = 0;

    *DLEN = i2cSlave->outputLength;
    *A = i2cSlave->address;
    *DIV = i2cSlave->clockDivider;
    *DEL = i2cSlave->dataDelay;
    *CLKT = i2cSlave->clockStretchTimeout;
    *S = I2C_S_CLEAR;
    *C = I2C_C_SEND;

    while (!(*S & I2C_S_DONE)) {
        while (count < i2cSlave->outputLength && *S & I2C_S_TXD) {
            *FIFO = i2cSlave->outputBuffer[count++];
        }
    }

    const volatile uint32_t status = *S;

    if (status & I2C_S_ERR) {
        return I2C_STATUS_NO_ACKNOWLEDGE;
    } else if (status & I2C_S_CLKT) {
        return I2C_STATUS_CLOCK_STRETCH_TIMEOUT;
    } else if (count < i2cSlave->outputLength) {
        return I2C_STATUS_DATA_LOSS;
    } else {
        return I2C_STATUS_SUCCESS;
    }

}

int receiveFromSlave(struct i2c_slave_t *const i2cSlave) {

    if (i2cSlave->status == I2C_SLAVE_CLOSED) {
        return I2C_STATUS_CONFIG_ERROR;
    }

    volatile int count = 0;

    *DLEN = i2cSlave->inputLength;
    *A = i2cSlave->address;
    *DIV = i2cSlave->clockDivider;
    *DEL = i2cSlave->dataDelay;
    *CLKT = i2cSlave->clockStretchTimeout;
    *S = I2C_S_CLEAR;
    *C = I2C_C_RECEIVE;

    while (!(*S & I2C_S_DONE)) {
        while (count < i2cSlave->inputLength && *S & I2C_S_RXD) {
            i2cSlave->inputBuffer[count++] = (*FIFO & 0x000000ff);
        }
    }

    const volatile uint32_t status = *S;

    if (status & I2C_S_ERR) {
        return I2C_STATUS_NO_ACKNOWLEDGE;
    } else if (status & I2C_S_CLKT) {
        return I2C_STATUS_CLOCK_STRETCH_TIMEOUT;
    } else if (count < i2cSlave->outputLength) {
        return I2C_STATUS_DATA_LOSS;
    } else {
        return I2C_STATUS_SUCCESS;
    }

}

void closeSlaveConnection(struct i2c_slave_t *const i2cSlave) {

    i2cSlave->status = I2C_SLAVE_CLOSED;

}
