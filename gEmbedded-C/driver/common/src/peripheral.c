//
// Created by sondahi on 23.01.23.
//

#include "peripheral.h"

int requestPinConfigRegs(struct PinConfigRegs **const pPinConfigRegs) {

    if (pPinConfigRegs == NULL) {
        return PERIPHERAL_EXCEPTION_ERROR;
    }

    void *base;

    const MAPPER_STATUS status = mapBaseRegister(MEMORY_FILE_NAME, BLOCK_SIZE, GPIO_BASE_ADDRESS, &base);
    if (status != MAPPER_SUCCESS) {
        return PERIPHERAL_EXCEPTION_ERROR;
    }

    *pPinConfigRegs = (struct PinConfigRegs *) base;

    return PERIPHERAL_EXCEPTION_SUCCESS;

}

int releasePinConfigRegs(struct PinConfigRegs **const pPinConfigRegs) {

    if (pPinConfigRegs == NULL) {
        return PERIPHERAL_EXCEPTION_ERROR;
    }

    void *base = (void *) *pPinConfigRegs;

    const MAPPER_STATUS status = unmapBaseRegister(&base, BLOCK_SIZE);
    if (status != MAPPER_SUCCESS) {
        return PERIPHERAL_EXCEPTION_ERROR;
    }

    return PERIPHERAL_EXCEPTION_SUCCESS;

}

int requestPinIORegs(struct PinIORegs **const pPinIoRegs) {

    if (pPinIoRegs == NULL) {
        return PERIPHERAL_EXCEPTION_ERROR;
    }

    void *base;

    const MAPPER_STATUS status = mapBaseRegister(MEMORY_FILE_NAME, BLOCK_SIZE, GPIO_BASE_ADDRESS, &base);
    if (status != MAPPER_SUCCESS) {
        return PERIPHERAL_EXCEPTION_ERROR;
    }

    *pPinIoRegs = (struct PinIORegs *) base;

    return PERIPHERAL_EXCEPTION_SUCCESS;

}

int releasePinIORegs(struct PinIORegs **const pPinIoRegs) {

    if (pPinIoRegs == NULL) {
        return PERIPHERAL_EXCEPTION_ERROR;
    }

    void *base = (void *) *pPinIoRegs;

    const MAPPER_STATUS status = unmapBaseRegister(&base, BLOCK_SIZE);
    if (status != MAPPER_SUCCESS) {
        return PERIPHERAL_EXCEPTION_ERROR;
    }

    return PERIPHERAL_EXCEPTION_SUCCESS;

}