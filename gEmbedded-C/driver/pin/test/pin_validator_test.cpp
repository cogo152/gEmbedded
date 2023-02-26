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

    int status;

    uint8_t pinNumber = PIN_NUMBER_INVALID;

    status = validateOutputPin(pinNumber);
    ASSERT_EQ(status, PIN_VALIDATOR_ERROR_PIN_NUMBER);

    pinNumber = PIN_NUMBER_VALID;

    status = validateOutputPin(pinNumber);
    ASSERT_EQ(status, PIN_VALIDATOR_ERROR_NO);

}

TEST(PinValidatorTest, testInputPin) {

    int status;

    uint8_t pinNumber = PIN_NUMBER_INVALID;
    uint8_t pinPullUpDown = PIN_PULLUPDOWN_INVALID;

    status = validateInputPin(pinNumber, pinPullUpDown);
    ASSERT_EQ(status, PIN_VALIDATOR_ERROR_PIN_NUMBER);

    pinNumber = PIN_NUMBER_VALID;

    status = validateInputPin(pinNumber, pinPullUpDown);
    ASSERT_EQ(status, PIN_VALIDATOR_ERROR_PIN_PULLUPDOWN);

    pinPullUpDown = PIN_CONFIG_PUD_NO_RESISTOR;
    status = validateInputPin(pinNumber, pinPullUpDown);
    ASSERT_EQ(status, PIN_VALIDATOR_ERROR_NO);

    pinPullUpDown = PIN_CONFIG_PUD_PULL_UP;
    status = validateInputPin(pinNumber, pinPullUpDown);
    ASSERT_EQ(status, PIN_VALIDATOR_ERROR_NO);

    pinPullUpDown = PIN_CONFIG_PUD_PULL_DOWN;
    status = validateInputPin(pinNumber, pinPullUpDown);
    ASSERT_EQ(status, PIN_VALIDATOR_ERROR_NO);

}

TEST(PinValidatorTest, testListenerPin) {

    int status;

    uint8_t pinNumber = PIN_NUMBER_INVALID;
    uint8_t pinEvent = PIN_EVENT_INVALID;
    uint8_t pinEventTimeOutInMilSec = PIN_EVENT_TIMEOUT_INVALID;

    status = validateListenerPin(pinNumber, pinEvent, pinEventTimeOutInMilSec);
    ASSERT_EQ(status, PIN_VALIDATOR_ERROR_PIN_NUMBER);

    pinNumber = PIN_NUMBER_VALID;
    status = validateListenerPin(pinNumber, pinEvent, pinEventTimeOutInMilSec);
    ASSERT_EQ(status, PIN_VALIDATOR_ERROR_PIN_EVENT);

    pinEvent = PIN_CONFIG_EVENT_RISING;
    status = validateListenerPin(pinNumber, pinEvent, pinEventTimeOutInMilSec);
    ASSERT_EQ(status, PIN_VALIDATOR_ERROR_PIN_EVENT_TIMEOUT);

    pinEvent = PIN_CONFIG_EVENT_FALLING;
    status = validateListenerPin(pinNumber, pinEvent, pinEventTimeOutInMilSec);
    ASSERT_EQ(status, PIN_VALIDATOR_ERROR_PIN_EVENT_TIMEOUT);

    pinEvent = PIN_CONFIG_EVENT_BOTH;
    status = validateListenerPin(pinNumber, pinEvent, pinEventTimeOutInMilSec);
    ASSERT_EQ(status, PIN_VALIDATOR_ERROR_PIN_EVENT_TIMEOUT);

    pinEventTimeOutInMilSec = PIN_EVENT_TIMEOUT_VALID;
    status = validateListenerPin(pinNumber, pinEvent, pinEventTimeOutInMilSec);
    ASSERT_EQ(status, PIN_VALIDATOR_ERROR_NO);

}