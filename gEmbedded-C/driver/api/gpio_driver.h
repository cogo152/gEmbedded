//
// Created by sondahi on 15.01.23.
//

#ifndef GEMBEDDED_C_GPIO_DRIVER_H
#define GEMBEDDED_C_GPIO_DRIVER_H
#ifdef __cplusplus
extern "C" {
#endif

#include "common.h"

#define GPIO_PIN_FUNCTION_OUTPUT        (0b001U)
#define GPIO_PIN_FUNCTION_INPUT         (0b000U)
#define GPIO_PIN_FUNCTION_ALT0          (0b100U)
#define GPIO_PIN_FUNCTION_ALT1          (0b101U)
#define GPIO_PIN_FUNCTION_ALT2          (0b110U)
#define GPIO_PIN_FUNCTION_ALT3          (0b111U)
#define GPIO_PIN_FUNCTION_ALT4          (0b011U)
#define GPIO_PIN_FUNCTION_ALT5          (0b010U)

#define GPIO_PIN_PUD_NO_RESISTOR        (0b00U)
#define GPIO_PIN_PUD_PULL_UP            (0b01U)
#define GPIO_PIN_PUD_PULL_DOWN          (0b10U)
#define GPIO_PIN_PUD_RESERVED           (0b11U)

#define GPIO_PIN_EVENT_RISING           (0b0U)
#define GPIO_PIN_EVENT_FALLING          (0b1U)

#define GPIO_CHIP                       ("/dev/gpiochip0")
#define GPIO_PIN_LEVEL_HIGH             (0b1U)
#define GPIO_PIN_LEVEL_LOW              (0b0U)

#define GPIO_PIN_ARRAY_LENGTH           (2U)
#define GPIO_PIN_ARRAY_LENGTH_MAX       (32U)

#define GPIO_STATUS_SUCCESS             (0)
#define GPIO_STATUS_CONFIG_ERROR        (-1)
#define GPIO_STATUS_POLL_IO_ERROR       (-2)
#define GPIO_STATUS_POLL_TIMEOUT_ERROR  (-3)
#define GPIO_STATUS_FILE_IO_ERROR       (-4)

struct gpio_pin_event_t {
    uint8_t event;
    uint64_t timeStamp;
};

int setupGpioDriver(void);

int shutdownGpioDriver(void);

int openOutputPin(uint8_t pinNumber, uint32_t *pinReference);

void setOutputPinHigh(uint32_t pinReference);

uint8_t readOutputPinLevel(uint32_t pinReference);

void setOutputPinLow(uint32_t pinReference);

void closeOutputPin(uint32_t *pinReference);

int openInputPin(uint8_t pinNumber, uint8_t pinPullUpDown, uint32_t *pinReference);

int updateInputPin(uint8_t pinNumber, uint8_t pinPullUpDown);

uint8_t readInputPinLevel(uint32_t pinReference);

void closeInputPin(uint32_t *pinReference);

int openListenerPin(uint8_t pinNumber, uint8_t pinEvent, uint32_t *pinReference);

int updateListenerPin(uint8_t pinNumber, uint8_t pinEvent, uint32_t *pinReference);

int readListenerPinEvent(uint32_t pinReference, int timeoutInMilSec, struct gpio_pin_event_t *pinEvent);

void closeListenerPin(uint32_t *pinReference);

#ifdef __cplusplus
}
#endif
#endif //GEMBEDDED_C_GPIO_DRIVER_H
