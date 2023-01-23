//
// Created by sondahi on 23.01.23.
//

#ifndef GEMBEDDED_C_PERIPHERAL_H
#define GEMBEDDED_C_PERIPHERAL_H

#include "memory_mapper.h"
#include "peripheral_bcm2711.h"

#define PERIPHERAL_EXCEPTION_SUCCESS (0)
#define PERIPHERAL_EXCEPTION_ERROR   (-1)

int requestPinConfigRegs(struct PinConfigRegs **);

int releasePinConfigRegs(struct PinConfigRegs **);

int requestPinIORegs(struct PinIORegs **);

int releasePinIORegs(struct PinIORegs **);

#endif //GEMBEDDED_C_PERIPHERAL_H
