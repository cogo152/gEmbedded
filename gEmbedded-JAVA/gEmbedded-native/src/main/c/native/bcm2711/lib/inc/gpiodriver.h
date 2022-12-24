#ifndef GPIODRIVER_H
#define GPIODRIVER_H

#include "common.h"

typedef enum {
    PIN_SUCCESS = 0,
    PIN_ERROR = 1
} PIN_STATUS;

typedef enum {
    PIN_FUNCTION_INPUT = 0b000,
    PIN_FUNCTION_OUTPUT = 0b001,
    PIN_FUNCTION_ALT_0 = 0b100,
    PIN_FUNCTION_ALT_1 = 0b101,
    PIN_FUNCTION_ALT_2 = 0b110,
    PIN_FUNCTION_ALT_3 = 0b111,
    PIN_FUNCTION_ALT_4 = 0b011,
    PIN_FUNCTION_ALT_5 = 0b010,
} PIN_FUNCTION;

typedef enum {
    PIN_FUNCTION_SUPPORTED = 0,
    PIN_FUNCTION_NOT_SUPPORTED = 1
} PIN_FUNCTION_VALIDATION;

#define LISTENERCALLBACK_CLASS              ("com/comert/gEmbedded/api/device/gpio/ListenerCallBack")
#define ON_RISING_METHOD_NAME               ("onRising")
#define ON_RISING_METHOD_SIGNATURE          ("(J)V")
#define ON_FALLING_METHOD_NAME              ("onFalling")
#define ON_FALLING_METHOD_SIGNATURE         ("(J)V")
#define ON_TIMEOUT_METHOD_NAME              ("onTimeout")
#define ON_TIMEOUT_METHOD_SIGNATURE         ("()V")
#define ON_ERROR_METHOD_NAME                ("onError")
#define ON_ERROR_METHOD_SIGNATURE           ("()V")

PIN_FUNCTION_VALIDATION validatePinFunctionAndConvert (uint8_t _pin, uint8_t _pinFunction, uint8_t *convertedPinFunction);
PIN_STATUS configurePinFunction (uint8_t _pin, uint8_t convertedPinFunction);

#endif //GPIODRIVER_H
