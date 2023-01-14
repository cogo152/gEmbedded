//
// Created by sondahi on 12.01.23.
//

#ifndef GEMBEDDED_C_GPIODRIVER_H
#define GEMBEDDED_C_GPIODRIVER_H
#ifdef __cplusplus
extern "C" {
#endif

#include "common.h"

#define PIN_FUNCTION_INPUT  (0b000U)
#define PIN_FUNCTION_OUTPUT (0b001U)
#define PIN_FUNCTION_ALT0   (0b100U)
#define PIN_FUNCTION_ALT1   (0b101U)
#define PIN_FUNCTION_ALT2   (0b110U)
#define PIN_FUNCTION_ALT3   (0b111U)
#define PIN_FUNCTION_ALT4   (0b011U)
#define PIN_FUNCTION_ALT5   (0b010U)

#define PIN_LEVEL_HIGH      (0b1U)
#define PIN_LEVEL_LOW       (0b0U)

typedef enum {
    GPIO_CONFIG_SUCCESS = 0,
    GPIO_CONFIG_ERROR = 1
} GPIO_CONFIG_STATUS;

typedef enum {
    GPIO_IO_SUCCESS = 2,
    GPIO_IO_ERROR = 3
} GPIO_IO_STATUS;

typedef struct gpio_driver_t {
    GPIO_CONFIG_STATUS  (*setupGpioDriver)(void);
    GPIO_CONFIG_STATUS  (*shutdownGpioDriver)(void);
    GPIO_CONFIG_STATUS  (*openOutputPin)(uint8_t pinNumber);
    GPIO_CONFIG_STATUS  (*registerOutputPin)(uint8_t pinNumber, uint8_t *pinReference);
    GPIO_IO_STATUS      (*setHighOutputPin)(uint8_t pinReference);
    GPIO_IO_STATUS      (*readOutputPin)(uint8_t pinReference, uint8_t *pinLevel);
    GPIO_IO_STATUS      (*setLowOutputPin)(uint8_t pinReference);
    GPIO_CONFIG_STATUS  (*closeOutputPin)(uint8_t pinReference);
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
