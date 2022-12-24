//
// Created by sondahi on 17.12.22.
//

#ifndef GEMBEDDED_C_DEVICECONTEXTLOCK_H
#define GEMBEDDED_C_DEVICECONTEXTLOCK_H

#include "devicecontextstatus.h"

DEVICE_CONTEXT_STATUS lockDeviceContext(void);

DEVICE_CONTEXT_STATUS unlockDeviceContext(void);

// InContextLock
uint8_t getDeviceStatus(void );

#endif //GEMBEDDED_C_DEVICECONTEXTLOCK_H
