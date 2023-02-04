//
// Created by sondahi on 28.01.23.
//

#include "gtest/gtest.h"
#include "pin_numbers_test.h"
extern "C" {
#include "pin_validator.h"
#include "peripheral.h"
}

TEST(PinValidatorTest, testOutputPin) {

    int status;
    pin_t pin;

    pin.type = PIN_TYPE_INPUT;
    pin.cNumber = PIN_INVALID;
    pin.cFunction=PIN_CONFIG_FUNCTION_INPUT;

    status = validateOutputPin(&pin);
    ASSERT_EQ(status, PIN_VALIDATOR_EXCEPTION_TYPE_ERROR);

    pin.type = PIN_TYPE_OUTPUT;
    status = validateOutputPin(&pin);
    ASSERT_EQ(status, PIN_VALIDATOR_EXCEPTION_NUMBER_ERROR);

    pin.cNumber = PIN_VALID;
    status = validateOutputPin(&pin);
    ASSERT_EQ(status, PIN_VALIDATOR_EXCEPTION_FUNCTION_ERROR);

    pin.cFunction = PIN_CONFIG_FUNCTION_OUTPUT;
    status = validateOutputPin(&pin);
    ASSERT_EQ(status, PIN_VALIDATOR_EXCEPTION_NO_ERROR);

}

TEST(PinValidatorTest, testInputPin) {

    int status;
    pin_t pin;

    pin.type = PIN_TYPE_OUTPUT;
    pin.cNumber = PIN_INVALID;
    pin.cFunction=PIN_CONFIG_FUNCTION_OUTPUT;
    pin.cPullUpDown = 0b11;

    status = validateInputPin(&pin);
    ASSERT_EQ(status, PIN_VALIDATOR_EXCEPTION_TYPE_ERROR);

    pin.type = PIN_TYPE_INPUT;
    status = validateInputPin(&pin);
    ASSERT_EQ(status, PIN_VALIDATOR_EXCEPTION_NUMBER_ERROR);

    pin.cNumber = PIN_VALID;
    status = validateInputPin(&pin);
    ASSERT_EQ(status, PIN_VALIDATOR_EXCEPTION_FUNCTION_ERROR);

    pin.cFunction = PIN_CONFIG_FUNCTION_INPUT;
    status = validateInputPin(&pin);
    ASSERT_EQ(status, PIN_VALIDATOR_EXCEPTION_PUD_ERROR);

    pin.cPullUpDown = PIN_CONFIG_PUD_PULL_UP;
    status = validateInputPin(&pin);
    ASSERT_EQ(status, PIN_VALIDATOR_EXCEPTION_NO_ERROR);

}

TEST(PinValidatorTest, testListenerPin) {

    int status;
    pin_t pin;

    pin.type = PIN_TYPE_OUTPUT;
    pin.cNumber = PIN_INVALID;
    pin.cFunction=PIN_CONFIG_FUNCTION_OUTPUT;
    pin.cEvent = 0b11;
    pin.cEventTimeout = 0;

    status = validateListenerPin(&pin);
    ASSERT_EQ(status, PIN_VALIDATOR_EXCEPTION_TYPE_ERROR);

    pin.type = PIN_TYPE_LISTENER;
    status = validateListenerPin(&pin);
    ASSERT_EQ(status, PIN_VALIDATOR_EXCEPTION_NUMBER_ERROR);

    pin.cNumber = PIN_VALID;
    status = validateListenerPin(&pin);
    ASSERT_EQ(status, PIN_VALIDATOR_EXCEPTION_FUNCTION_ERROR);

    pin.cFunction = PIN_CONFIG_FUNCTION_INPUT;
    status = validateListenerPin(&pin);
    ASSERT_EQ(status, PIN_VALIDATOR_EXCEPTION_EVENT_ERROR);

    pin.cEvent = PIN_CONFIG_EVENT_BOTH;
    status = validateListenerPin(&pin);
    ASSERT_EQ(status, PIN_VALIDATOR_EXCEPTION_EVENT_TIMEOUT_ERROR);

    pin.cEventTimeout = 1;
    status = validateListenerPin(&pin);
    ASSERT_EQ(status, PIN_VALIDATOR_EXCEPTION_NO_ERROR);

}