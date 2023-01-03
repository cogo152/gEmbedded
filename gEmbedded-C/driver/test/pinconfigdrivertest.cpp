//
// Created by sondahi on 30.12.22.
//

#include "gtest/gtest.h"

extern "C" {
#include "pinconfigdriver.h"
}

TEST(PinConfigDriver, testSetupPinConfigDriver) {

    PIN_CONFIG_STATUS status;

    status = setupPinConfigDriver();
    ASSERT_EQ(PIN_CONFIG_SUCCESS, status);

    status = setupPinConfigDriver();
    ASSERT_EQ(PIN_CONFIG_ERROR, status);

}

TEST(PinConfigDriver, testShutdownPinConfigDriver) {

    PIN_CONFIG_STATUS status;

    status = shutdownPinConfigDriver();
    ASSERT_EQ(PIN_CONFIG_SUCCESS, status);

    status = shutdownPinConfigDriver();
    ASSERT_EQ(PIN_CONFIG_ERROR, status);

}

TEST(PinConfigDriver, testValidatePin) {

    ASSERT_EQ(PIN_CONFIG_ERROR, validatePin(PIN_TYPE_GPIO, PIN_4));

    setupPinConfigDriver();

    ASSERT_EQ(PIN_CONFIG_ERROR, validatePin((PIN_TYPE) 6, PIN_1));
    ASSERT_EQ(PIN_CONFIG_ERROR, validatePin(PIN_TYPE_GPIO, PIN_1));
    ASSERT_EQ(PIN_CONFIG_ERROR, validatePin(PIN_TYPE_CLOCK, PIN_5));
    ASSERT_EQ(PIN_CONFIG_ERROR, validatePin(PIN_TYPE_PWM, PIN_17));
    ASSERT_EQ(PIN_CONFIG_ERROR, validatePin(PIN_TYPE_I2C, PIN_4));
    ASSERT_EQ(PIN_CONFIG_ERROR, validatePin(PIN_TYPE_SPI, PIN_12));
    ASSERT_EQ(PIN_CONFIG_ERROR, validatePin(PIN_TYPE_UART, PIN_16));

    ASSERT_EQ(PIN_CONFIG_SUCCESS, validatePin(PIN_TYPE_GPIO, PIN_4));
    ASSERT_EQ(PIN_CONFIG_SUCCESS, validatePin(PIN_TYPE_CLOCK, PIN_4));
    ASSERT_EQ(PIN_CONFIG_SUCCESS, validatePin(PIN_TYPE_PWM, PIN_18));
    ASSERT_EQ(PIN_CONFIG_SUCCESS, validatePin(PIN_TYPE_I2C, PIN_2));
    ASSERT_EQ(PIN_CONFIG_SUCCESS, validatePin(PIN_TYPE_SPI, PIN_9));
    ASSERT_EQ(PIN_CONFIG_SUCCESS, validatePin(PIN_TYPE_UART, PIN_15));

    shutdownPinConfigDriver();

    ASSERT_EQ(PIN_CONFIG_ERROR, validatePin(PIN_TYPE_GPIO, PIN_4));

}

TEST(PinConfigDriver, testConfigureAndReadPinFunction) {

    const PIN validatedPin = PIN_4;
    const PIN_FUNCTION pinFunctionToConfigure = PIN_FUNCTION_INPUT;
    PIN_FUNCTION pinFunctionToCheck;

    ASSERT_EQ(PIN_CONFIG_ERROR, configurePinFunction(validatedPin, pinFunctionToConfigure));
    ASSERT_EQ(PIN_CONFIG_ERROR, readPinFunction(validatedPin, &pinFunctionToCheck));

    setupPinConfigDriver();

    ASSERT_EQ(PIN_CONFIG_SUCCESS, configurePinFunction(validatedPin, pinFunctionToConfigure));
    ASSERT_EQ(PIN_CONFIG_SUCCESS, readPinFunction(validatedPin, &pinFunctionToCheck));

    ASSERT_EQ(pinFunctionToConfigure, pinFunctionToCheck);

    shutdownPinConfigDriver();

    ASSERT_EQ(PIN_CONFIG_ERROR, configurePinFunction(validatedPin, pinFunctionToConfigure));
    ASSERT_EQ(PIN_CONFIG_ERROR, readPinFunction(validatedPin, &pinFunctionToCheck));

}