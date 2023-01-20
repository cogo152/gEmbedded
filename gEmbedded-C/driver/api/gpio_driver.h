//
// Created by sondahi on 15.01.23.
//

#ifndef GEMBEDDED_C_GPIO_DRIVER_H
#define GEMBEDDED_C_GPIO_DRIVER_H
#ifdef __cplusplus
extern "C" {
#endif

#include "common.h"

// config values

#define GPIO_PIN_FUNCTION_OUTPUT        (0b001U)
#define GPIO_PIN_FUNCTION_INPUT         (0b000U)
#define GPIO_PIN_FUNCTION_ALT0          (0b100U)
#define GPIO_PIN_FUNCTION_ALT1          (0b101U)
#define GPIO_PIN_FUNCTION_ALT2          (0b110U)
#define GPIO_PIN_FUNCTION_ALT3          (0b111U)
#define GPIO_PIN_FUNCTION_ALT4          (0b011U)
#define GPIO_PIN_FUNCTION_ALT5          (0b010U)
#define GPIO_PIN_FUNCTION_MOD_DIV       (10U)
#define GPIO_PIN_FUNCTION_MASK          (0b111U)
#define GPIO_PIN_FUNCTION_MUL           (3U)

#define GPIO_PIN_PUD_NO_RESISTOR        (0b00U)
#define GPIO_PIN_PUD_PULL_UP            (0b01U)
#define GPIO_PIN_PUD_PULL_DOWN          (0b10U)
#define GPIO_PIN_PUD_MOD_DIV            (16U)
#define GPIO_PIN_PUD_MASK               (0b11U)
#define GPIO_PIN_PUD_MUL                (2U)

#define GPIO_PIN_EVENT_RISING           (0b00U)
#define GPIO_PIN_EVENT_FALLING          (0b01U)
#define GPIO_PIN_EVENT_BOTH             (0b10U)
#define GPIO_PIN_EVENT_MOD_DIV          (32U)
#define GPIO_PIN_EVENT_MASK             (0b1U)
#define GPIO_PIN_EVENT_SET              (0b1U)
#define GPIO_PIN_EVENT_MUL              (1U)

// return values and exceptions

#define GPIO_CHIP                       ("/dev/gpiochip0")
#define GPIO_PIN_LEVEL_HIGH             (0b1U)
#define GPIO_PIN_LEVEL_LOW              (0b0U)

#define GPIO_STATUS_SUCCESS             (0)
#define GPIO_STATUS_CONFIG_ERROR        (-1)
#define GPIO_STATUS_POLL_IO_ERROR       (-2)
#define GPIO_STATUS_POLL_TIMEOUT_ERROR  (-3)
#define GPIO_STATUS_FILE_IO_ERROR       (-4)

// parameter values

struct output_pin_t {
    uint8_t number;
    uint8_t level;
    uint32_t reference;
};

struct input_pin_t {
    uint8_t number;
    uint8_t pullUpDown;
    uint8_t level;
    uint32_t reference;
};

struct listener_pin_t {
    uint8_t number;
    uint8_t cevent;
    uint8_t revent;
    int reference;
    int timeoutInMilSec;
    uint64_t timeStamp;
};

struct alternate_pin_t {
    uint8_t number;
    uint8_t function;
};

// returns GPIO_STATUS_CONFIG_ERROR if mapping fails
int setupGpioDriver(void);

// returns GPIO_STATUS_CONFIG_ERROR if unmapping fails
int shutdownGpioDriver(void);

// returns GPIO_STATUS_CONFIG_ERROR if pin function configuration fails
int openOutputPin(struct output_pin_t *outputPin);

void setOutputPinHigh(struct output_pin_t *outputPin);

void readOutputPinLevel(struct output_pin_t *outputPin);

void setOutputPinLow(struct output_pin_t *outputPin);

void closeOutputPin(struct output_pin_t *outputPin);

int openInputPin(struct input_pin_t *inputPin);

int updateInputPin(struct input_pin_t *inputPin);

void readInputPinLevel(struct input_pin_t *inputPin);

void closeInputPin(struct input_pin_t *inputPin);

// returns GPIO_STATUS_CONFIG_ERROR if timeout <=0 fails because we do not want endless blocking io
// returns GPIO_STATUS_CONFIG_ERROR if GPIO_DEV file open fails.
// returns GPIO_STATUS_CONFIG_ERROR if ioctl fails.
// returns GPIO_STATUS_CONFIG_ERROR if pin function configuration fails
// returns GPIO_STATUS_CONFIG_ERROR if pin event configuration fails
int openListenerPin(struct listener_pin_t *listenerPin);

// returns GPIO_STATUS_CONFIG_ERROR if timeout <=0 fails because we do not want endless blocking io
// returns GPIO_STATUS_CONFIG_ERROR if GPIO_DEV file open fails.
// returns GPIO_STATUS_CONFIG_ERROR if ioctl fails.
// returns GPIO_STATUS_CONFIG_ERROR if pin function configuration fails
// returns GPIO_STATUS_CONFIG_ERROR if pin event configuration fails
int updateListenerPin(struct listener_pin_t *listenerPin);

// returns GPIO_STATUS_POLL_IO_ERROR if polling fails.
// returns GPIO_STATUS_FILE_IO_ERROR if poll file open fails.
// returns GPIO_STATUS_POLL_TIMEOUT_ERROR if poll timeout occures.
int readListenerPinEvent(struct listener_pin_t *listenerPin);

void closeListenerPin(struct listener_pin_t *listenerPin);

// returns GPIO_STATUS_CONFIG_ERROR if pin function configuration fails
int openAlternatePin(struct alternate_pin_t *alternatePin);
int updateAlternatePin(struct alternate_pin_t *alternatePin);
void closeAlternatePin(struct alternate_pin_t *alternatePin);

#ifdef __cplusplus
}
#endif
#endif //GEMBEDDED_C_GPIO_DRIVER_H
