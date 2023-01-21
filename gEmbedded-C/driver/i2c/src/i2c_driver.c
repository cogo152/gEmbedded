//
// Created by sondahi on 21.01.23.
//

#include "i2c_peripheral.h"
#include "i2c_driver.h"
#include "gpio_driver.h"
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