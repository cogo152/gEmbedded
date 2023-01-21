//
// Created by sondahi on 21.01.23.
//

#ifndef GEMBEDDED_C_DRIVER_CONTEXT_H
#define GEMBEDDED_C_DRIVER_CONTEXT_H
#ifdef __cplusplus
extern "C" {
#endif

#include "driver_exception.h"

int setupDrivers(void);
int shutdownDrivers(void );

#ifdef __cplusplus
}
#endif
#endif //GEMBEDDED_C_DRIVER_CONTEXT_H
