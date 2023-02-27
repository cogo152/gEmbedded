//
// Created by sondahi on 28.01.23.
//

#include "gtest/gtest.h"
#include "pin_test.h"

extern "C" {
#include "pin_validator.h"
#include "peripheral.h"
}

TEST(PinValidatorTest, testOutputPin) {

    PIN_VALIDATOR_ERROR error;

    uint8_t pinNumber = PIN_NUMBER_INVALID;

    error = validateOutputPin(pinNumber);
    ASSERT_EQ(error, PIN_VALIDATOR_ERROR_PIN_NUMBER);

    pinNumber = PIN_NUMBER_VALID;

    error = validateOutputPin(pinNumber);
    ASSERT_EQ(error, PIN_VALIDATOR_ERROR_NO);

}

TEST(PinValidatorTest, testInputPin) {

    PIN_VALIDATOR_ERROR error;

    uint8_t pinNumber = PIN_NUMBER_INVALID;
    uint8_t pinPullUpDown = PIN_PULLUPDOWN_INVALID;

    error = validateInputPin(pinNumber, pinPullUpDown);
    ASSERT_EQ(error, PIN_VALIDATOR_ERROR_PIN_NUMBER);

    pinNumber = PIN_NUMBER_VALID;

    error = validateInputPin(pinNumber, pinPullUpDown);
    ASSERT_EQ(error, PIN_VALIDATOR_ERROR_PIN_PULLUPDOWN);

    pinPullUpDown = PIN_CONFIG_PUD_NO_RESISTOR;

    error = validateInputPin(pinNumber, pinPullUpDown);
    ASSERT_EQ(error, PIN_VALIDATOR_ERROR_NO);

    pinPullUpDown = PIN_CONFIG_PUD_PULL_UP;

    error = validateInputPin(pinNumber, pinPullUpDown);
    ASSERT_EQ(error, PIN_VALIDATOR_ERROR_NO);

    pinPullUpDown = PIN_CONFIG_PUD_PULL_DOWN;

    error = validateInputPin(pinNumber, pinPullUpDown);
    ASSERT_EQ(error, PIN_VALIDATOR_ERROR_NO);

}

TEST(PinValidatorTest, testListenerPin) {

    PIN_VALIDATOR_ERROR error;

    uint8_t pinNumber = PIN_NUMBER_INVALID;
    uint8_t pinPullUpDown = PIN_PULLUPDOWN_INVALID;
    uint8_t pinEvent = PIN_EVENT_INVALID;
    uint8_t pinEventTimeOutInMilSec = PIN_EVENT_TIMEOUT_INVALID;

    error = validateListenerPin(pinNumber, pinPullUpDown, pinEvent, pinEventTimeOutInMilSec);
    ASSERT_EQ(error, PIN_VALIDATOR_ERROR_PIN_NUMBER);

    pinNumber = PIN_NUMBER_VALID;

    error = validateListenerPin(pinNumber, pinPullUpDown, pinEvent, pinEventTimeOutInMilSec);
    ASSERT_EQ(error, PIN_VALIDATOR_ERROR_PIN_PULLUPDOWN);

    pinPullUpDown = PIN_CONFIG_PUD_NO_RESISTOR;

    error = validateListenerPin(pinNumber, pinPullUpDown, pinEvent, pinEventTimeOutInMilSec);
    ASSERT_EQ(error, PIN_VALIDATOR_ERROR_PIN_EVENT);

    pinPullUpDown = PIN_CONFIG_PUD_PULL_UP;

    error = validateListenerPin(pinNumber, pinPullUpDown, pinEvent, pinEventTimeOutInMilSec);
    ASSERT_EQ(error, PIN_VALIDATOR_ERROR_PIN_EVENT);

    pinPullUpDown = PIN_CONFIG_PUD_PULL_DOWN;

    error = validateListenerPin(pinNumber, pinPullUpDown, pinEvent, pinEventTimeOutInMilSec);
    ASSERT_EQ(error, PIN_VALIDATOR_ERROR_PIN_EVENT);

    pinEvent = PIN_CONFIG_EVENT_RISING;

    error = validateListenerPin(pinNumber, pinPullUpDown, pinEvent, pinEventTimeOutInMilSec);
    ASSERT_EQ(error, PIN_VALIDATOR_ERROR_PIN_EVENT_TIMEOUT);

    pinEvent = PIN_CONFIG_EVENT_FALLING;

    error = validateListenerPin(pinNumber, pinPullUpDown, pinEvent, pinEventTimeOutInMilSec);
    ASSERT_EQ(error, PIN_VALIDATOR_ERROR_PIN_EVENT_TIMEOUT);

    pinEvent = PIN_CONFIG_EVENT_BOTH;

    error = validateListenerPin(pinNumber, pinPullUpDown, pinEvent, pinEventTimeOutInMilSec);
    ASSERT_EQ(error, PIN_VALIDATOR_ERROR_PIN_EVENT_TIMEOUT);

    pinEventTimeOutInMilSec = PIN_EVENT_TIMEOUT_VALID;

    error = validateListenerPin(pinNumber, pinPullUpDown, pinEvent, pinEventTimeOutInMilSec);
    ASSERT_EQ(error, PIN_VALIDATOR_ERROR_NO);

}