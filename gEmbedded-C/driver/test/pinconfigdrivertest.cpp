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

TEST(PinConfigDriver, testConfigureAndReadPinFunction) {

    const PIN validatedPin = PIN_4;
    PIN_FUNCTION pinFunctionToCheck;

    ASSERT_EQ(PIN_CONFIG_ERROR, configurePinFunction(validatedPin, PIN_FUNCTION_INPUT));
    ASSERT_EQ(PIN_CONFIG_ERROR, readPinFunction(validatedPin, &pinFunctionToCheck));

    setupPinConfigDriver();

    ASSERT_EQ(PIN_CONFIG_SUCCESS, configurePinFunction(validatedPin, PIN_FUNCTION_ALT_0));
    ASSERT_EQ(PIN_CONFIG_SUCCESS, readPinFunction(validatedPin, &pinFunctionToCheck));
    ASSERT_EQ(PIN_FUNCTION_ALT_0, pinFunctionToCheck);

    ASSERT_EQ(PIN_CONFIG_SUCCESS, configurePinFunction(validatedPin, PIN_FUNCTION_ALT_1));
    ASSERT_EQ(PIN_CONFIG_SUCCESS, readPinFunction(validatedPin, &pinFunctionToCheck));
    ASSERT_EQ(PIN_FUNCTION_ALT_1, pinFunctionToCheck);

    ASSERT_EQ(PIN_CONFIG_SUCCESS, configurePinFunction(validatedPin, PIN_FUNCTION_ALT_2));
    ASSERT_EQ(PIN_CONFIG_SUCCESS, readPinFunction(validatedPin, &pinFunctionToCheck));
    ASSERT_EQ(PIN_FUNCTION_ALT_2, pinFunctionToCheck);

    ASSERT_EQ(PIN_CONFIG_SUCCESS, configurePinFunction(validatedPin, PIN_FUNCTION_ALT_3));
    ASSERT_EQ(PIN_CONFIG_SUCCESS, readPinFunction(validatedPin, &pinFunctionToCheck));
    ASSERT_EQ(PIN_FUNCTION_ALT_3, pinFunctionToCheck);

    ASSERT_EQ(PIN_CONFIG_SUCCESS, configurePinFunction(validatedPin, PIN_FUNCTION_ALT_4));
    ASSERT_EQ(PIN_CONFIG_SUCCESS, readPinFunction(validatedPin, &pinFunctionToCheck));
    ASSERT_EQ(PIN_FUNCTION_ALT_4, pinFunctionToCheck);

    ASSERT_EQ(PIN_CONFIG_SUCCESS, configurePinFunction(validatedPin, PIN_FUNCTION_ALT_5));
    ASSERT_EQ(PIN_CONFIG_SUCCESS, readPinFunction(validatedPin, &pinFunctionToCheck));
    ASSERT_EQ(PIN_FUNCTION_ALT_5, pinFunctionToCheck);

    ASSERT_EQ(PIN_CONFIG_SUCCESS, configurePinFunction(validatedPin, PIN_FUNCTION_OUTPUT));
    ASSERT_EQ(PIN_CONFIG_SUCCESS, readPinFunction(validatedPin, &pinFunctionToCheck));
    ASSERT_EQ(PIN_FUNCTION_OUTPUT, pinFunctionToCheck);

    ASSERT_EQ(PIN_CONFIG_SUCCESS, configurePinFunction(validatedPin, PIN_FUNCTION_INPUT));
    ASSERT_EQ(PIN_CONFIG_SUCCESS, readPinFunction(validatedPin, &pinFunctionToCheck));
    ASSERT_EQ(PIN_FUNCTION_INPUT, pinFunctionToCheck);

    shutdownPinConfigDriver();

    ASSERT_EQ(PIN_CONFIG_ERROR, configurePinFunction(validatedPin, PIN_FUNCTION_INPUT));
    ASSERT_EQ(PIN_CONFIG_ERROR, readPinFunction(validatedPin, &pinFunctionToCheck));

}

TEST(PinConfigDriver, testConfigureAndReadPinPullUpDown) {

    const PIN validatedPin = PIN_4;
    PULL_UP_DOWN pullUpDownToCheck;

    ASSERT_EQ(PIN_CONFIG_ERROR, configurePinPullUpDown(validatedPin, PULL_UP_DOWN_NO_RESISTOR));
    ASSERT_EQ(PIN_CONFIG_ERROR, readPinPullUpDown(validatedPin, &pullUpDownToCheck));

    setupPinConfigDriver();

    ASSERT_EQ(PIN_CONFIG_SUCCESS, configurePinPullUpDown(validatedPin, PULL_UP_DOWN_PULL_UP));
    ASSERT_EQ(PIN_CONFIG_SUCCESS, readPinPullUpDown(validatedPin, &pullUpDownToCheck));
    ASSERT_EQ(PULL_UP_DOWN_PULL_UP, pullUpDownToCheck);

    ASSERT_EQ(PIN_CONFIG_SUCCESS, configurePinPullUpDown(validatedPin, PULL_UP_DOWN_PULL_DOWN));
    ASSERT_EQ(PIN_CONFIG_SUCCESS, readPinPullUpDown(validatedPin, &pullUpDownToCheck));
    ASSERT_EQ(PULL_UP_DOWN_PULL_DOWN, pullUpDownToCheck);

    ASSERT_EQ(PIN_CONFIG_SUCCESS, configurePinPullUpDown(validatedPin, PULL_UP_DOWN_NO_RESISTOR));
    ASSERT_EQ(PIN_CONFIG_SUCCESS, readPinPullUpDown(validatedPin, &pullUpDownToCheck));
    ASSERT_EQ(PULL_UP_DOWN_NO_RESISTOR, pullUpDownToCheck);

    shutdownPinConfigDriver();

    ASSERT_EQ(PIN_CONFIG_ERROR, configurePinPullUpDown(validatedPin, PULL_UP_DOWN_NO_RESISTOR));
    ASSERT_EQ(PIN_CONFIG_ERROR, readPinPullUpDown(validatedPin, &pullUpDownToCheck));

}

TEST(PinConfigDriver, testConfigureAndReadAndReleasePinEvent) {

    const PIN validatedPin = PIN_4;
    PIN_EVENT pinEventToCheck;
    PIN_FUNCTION pinFunctionToCheck;
    int fileDescriptor = -1;

    ASSERT_EQ(PIN_CONFIG_ERROR, configurePinEventLFS(validatedPin, PIN_EVENT_NO_EVENT, &fileDescriptor));
    ASSERT_EQ(PIN_CONFIG_ERROR, readPinEvent(validatedPin, &pinEventToCheck));
    ASSERT_EQ(PIN_CONFIG_ERROR, releasePinEvent(5));

    setupPinConfigDriver();

    ASSERT_EQ(PIN_CONFIG_SUCCESS, configurePinEventLFS(validatedPin, PIN_EVENT_RISING, &fileDescriptor));
    ASSERT_EQ(PIN_CONFIG_SUCCESS, readPinEvent(validatedPin, &pinEventToCheck));
    ASSERT_EQ(PIN_EVENT_RISING, pinEventToCheck);
    ASSERT_EQ(PIN_CONFIG_SUCCESS, readPinFunction(validatedPin, &pinFunctionToCheck));
    ASSERT_EQ(PIN_FUNCTION_INPUT, pinFunctionToCheck);
    ASSERT_GT(fileDescriptor, 0);
    ASSERT_EQ(PIN_CONFIG_SUCCESS, releasePinEvent(fileDescriptor));

    fileDescriptor = -1;

    ASSERT_EQ(PIN_CONFIG_SUCCESS, configurePinEventLFS(validatedPin, PIN_EVENT_FALLING, &fileDescriptor));
    ASSERT_EQ(PIN_CONFIG_SUCCESS, readPinEvent(validatedPin, &pinEventToCheck));
    ASSERT_EQ(PIN_EVENT_FALLING, pinEventToCheck);
    ASSERT_EQ(PIN_CONFIG_SUCCESS, readPinFunction(validatedPin, &pinFunctionToCheck));
    ASSERT_EQ(PIN_FUNCTION_INPUT, pinFunctionToCheck);
    ASSERT_GT(fileDescriptor, 0);
    ASSERT_EQ(PIN_CONFIG_SUCCESS, releasePinEvent(fileDescriptor));

    fileDescriptor = -1;

    ASSERT_EQ(PIN_CONFIG_SUCCESS, configurePinEventLFS(validatedPin, PIN_EVENT_BOTH, &fileDescriptor));
    ASSERT_EQ(PIN_CONFIG_SUCCESS, readPinEvent(validatedPin, &pinEventToCheck));
    ASSERT_EQ(PIN_EVENT_BOTH, pinEventToCheck);
    ASSERT_EQ(PIN_CONFIG_SUCCESS, readPinFunction(validatedPin, &pinFunctionToCheck));
    ASSERT_EQ(PIN_FUNCTION_INPUT, pinFunctionToCheck);
    ASSERT_GT(fileDescriptor, 0);
    ASSERT_EQ(PIN_CONFIG_SUCCESS, releasePinEvent(fileDescriptor));

    fileDescriptor = -1;

    ASSERT_EQ(PIN_CONFIG_SUCCESS, configurePinEventLFS(validatedPin, PIN_EVENT_NO_EVENT, &fileDescriptor));
    ASSERT_EQ(PIN_CONFIG_SUCCESS, readPinEvent(validatedPin, &pinEventToCheck));
    ASSERT_EQ(PIN_EVENT_NO_EVENT, pinEventToCheck);
    ASSERT_EQ(PIN_CONFIG_SUCCESS, readPinFunction(validatedPin, &pinFunctionToCheck));
    ASSERT_EQ(PIN_FUNCTION_INPUT, pinFunctionToCheck);
    ASSERT_EQ(fileDescriptor, 0);
    ASSERT_EQ(PIN_CONFIG_SUCCESS, releasePinEvent(fileDescriptor));

    shutdownPinConfigDriver();

    ASSERT_EQ(PIN_CONFIG_ERROR, configurePinEventLFS(validatedPin, PIN_EVENT_NO_EVENT, &fileDescriptor));
    ASSERT_EQ(PIN_CONFIG_ERROR, readPinEvent(validatedPin, &pinEventToCheck));
    ASSERT_EQ(PIN_CONFIG_ERROR, releasePinEvent(5));

}