//
// Created by sondahi on 06.12.22.
//

#ifndef GEMBEDDED_C_DEVICECONTEXT_H
#define GEMBEDDED_C_DEVICECONTEXT_H
#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

#include "common.h"
#include "devicecontextstatus.h"

// Thread safe
DEVICE_CONTEXT_STATUS setupDeviceContext(void);

// Thread safe
DEVICE_CONTEXT_STATUS shutdownDeviceContext(void);

// Not thread safe
const char *getDeviceName(void);

// Thread safe
uint8_t isDeviceInitialized(void);

#ifdef __cplusplus
}
#endif //__cplusplus
#endif //GEMBEDDED_C_DEVICECONTEXT_H
