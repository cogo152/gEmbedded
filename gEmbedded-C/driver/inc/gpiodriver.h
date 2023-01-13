//
// Created by sondahi on 12.01.23.
//

#ifndef GEMBEDDED_C_GPIODRIVER_H
#define GEMBEDDED_C_GPIODRIVER_H
#ifdef __cplusplus
extern "C" {
#endif

#include "common.h"

#define PIN_FUNCTION_INPUT  (0b000)
#define PIN_FUNCTION_OUTPUT (0b001)
#define PIN_FUNCTION_ALT0   (0b100)
#define PIN_FUNCTION_ALT1   (0b101)
#define PIN_FUNCTION_ALT2   (0b110)
#define PIN_FUNCTION_ALT3   (0b111)
#define PIN_FUNCTION_ALT4   (0b011)
#define PIN_FUNCTION_ALT5   (0b010)

#define PIN_LEVEL_HIGH      (0b1)
#define PIN_LEVEL_LOW       (0b0)

typedef enum {
    GPIO_SUCCESS = 0,
    GPIO_ERROR = 1
} GPIO_STATUS;

typedef struct gpio_driver_t {
    GPIO_STATUS (*setupGpioDriver)(void);
    GPIO_STATUS (*shutdownGpioDriver)(void);
    GPIO_STATUS (*openOutputPin)(uint8_t pinNumber, uint8_t *pinReference);
    GPIO_STATUS (*setOutputPin)(uint8_t pinReference);
    GPIO_STATUS (*readOutputPin)(uint8_t pinReference, uint8_t *pinLevel);
    GPIO_STATUS (*clearOutputPin)(uint8_t pinReference);
    GPIO_STATUS (*closeOutputPin)(uint8_t pinReference);
    GPIO_STATUS (*openInputPin)(uint8_t pinNumber, uint8_t pullUpDown, uint8_t *pinReference);
    GPIO_STATUS (*readInputPin)(uint8_t pinReference, uint8_t *pinLevel);
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
