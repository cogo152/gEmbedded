//
// Created by sondahi on 12.01.23.
//

#ifndef GEMBEDDED_C_GPIODRIVER_H
#define GEMBEDDED_C_GPIODRIVER_H
#ifdef __cplusplus
extern "C" {
#endif

#include "common.h"

typedef enum {
    GPIO_SUCCESS = 0,
    GPIO_ERROR = 1
} GPIO_STATUS;

typedef struct gpio_driver_t {
    GPIO_STATUS (*setupGpioDriver)(void);
    GPIO_STATUS (*shutdownGpioDriver)(void);
    GPIO_STATUS (*openOutputPin)(uint8_t pinNumber, uint8_t *pinReference);
    GPIO_STATUS (*setOutputPin)(uint8_t pinReference);
    GPIO_STATUS (*readOutputPin)(uint8_t pinReference);
    GPIO_STATUS (*clearOutputPin)(uint8_t pinReference);
    GPIO_STATUS (*closeOutputPin)(uint8_t pinReference);
    GPIO_STATUS (*openInputPin)(uint8_t pinNumber, uint8_t pullUpDown, uint8_t *pinReference);
    GPIO_STATUS (*readInputPin)(uint8_t pinReference, uint8_t *valueToRead);
    GPIO_STATUS (*closeInputPin)(uint8_t pinReference);
    GPIO_STATUS (*openListenerPin)(uint8_t pinNumber, uint8_t event, uint8_t *pinReference);
    GPIO_STATUS (*readListenerPin)(uint8_t pinReference);
    GPIO_STATUS (*closeListenerPin)(uint8_t pinReference);
    GPIO_STATUS (*openAlternatePin)(uint8_t pinNumber, uint8_t alternate, uint8_t *pinReference);
    GPIO_STATUS (*closeAlternatePin)(uint8_t pinReference);
} GpioDriver;

extern GpioDriver gpioDriver;

void bindGpioMM(void);

void unbindGpioMM(void);

void bindGpioLFS(void);

void unbindGpioLFS(void);


#ifdef __cplusplus
}
#endif
#endif //GEMBEDDED_C_GPIODRIVER_H
