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
    PIN_FUNCTION pinFunctionToSet;
    PIN_FUNCTION pinFunctionToCheck;

    setupPinConfigDriver();

    pinFunctionToSet = PIN_FUNCTION_ALT_0;
    configurePinFunction(validatedPin,pinFunctionToSet);
    pinFunctionToCheck = readPinFunction(validatedPin);
    ASSERT_EQ(pinFunctionToCheck,pinFunctionToSet);

    pinFunctionToSet = PIN_FUNCTION_ALT_1;
    configurePinFunction(validatedPin,pinFunctionToSet);
    pinFunctionToCheck = readPinFunction(validatedPin);
    ASSERT_EQ(pinFunctionToCheck,pinFunctionToSet);

    pinFunctionToSet = PIN_FUNCTION_ALT_2;
    configurePinFunction(validatedPin,pinFunctionToSet);
    pinFunctionToCheck = readPinFunction(validatedPin);
    ASSERT_EQ(pinFunctionToCheck,pinFunctionToSet);

    pinFunctionToSet = PIN_FUNCTION_ALT_3;
    configurePinFunction(validatedPin,pinFunctionToSet);
    pinFunctionToCheck = readPinFunction(validatedPin);
    ASSERT_EQ(pinFunctionToCheck,pinFunctionToSet);

    pinFunctionToSet = PIN_FUNCTION_ALT_4;
    configurePinFunction(validatedPin,pinFunctionToSet);
    pinFunctionToCheck = readPinFunction(validatedPin);
    ASSERT_EQ(pinFunctionToCheck,pinFunctionToSet);

    pinFunctionToSet = PIN_FUNCTION_ALT_5;
    configurePinFunction(validatedPin,pinFunctionToSet);
    pinFunctionToCheck = readPinFunction(validatedPin);
    ASSERT_EQ(pinFunctionToCheck,pinFunctionToSet);

    pinFunctionToSet = PIN_FUNCTION_OUTPUT;
    configurePinFunction(validatedPin,pinFunctionToSet);
    pinFunctionToCheck = readPinFunction(validatedPin);
    ASSERT_EQ(pinFunctionToCheck,pinFunctionToSet);

    pinFunctionToSet = PIN_FUNCTION_INPUT;
    configurePinFunction(validatedPin,pinFunctionToSet);
    pinFunctionToCheck = readPinFunction(validatedPin);
    ASSERT_EQ(pinFunctionToCheck,pinFunctionToSet);

    shutdownPinConfigDriver();

}

TEST(PinConfigDriver, testConfigureAndReadPinPullUpDown) {

    const PIN validatedPin = PIN_4;
    PULL_UP_DOWN pinPullUpDownToSet;
    PULL_UP_DOWN pinPullUpDownToCheck;

    setupPinConfigDriver();

    configurePinFunction(validatedPin,PIN_FUNCTION_INPUT);

    pinPullUpDownToSet = PULL_UP_DOWN_PULL_UP;
    configurePinPullUpDown(validatedPin,pinPullUpDownToSet);
    pinPullUpDownToCheck = readPinPullUpDown(validatedPin);
    ASSERT_EQ(pinPullUpDownToCheck,pinPullUpDownToSet);

    pinPullUpDownToSet = PULL_UP_DOWN_PULL_DOWN;
    configurePinPullUpDown(validatedPin,pinPullUpDownToSet);
    pinPullUpDownToCheck = readPinPullUpDown(validatedPin);
    ASSERT_EQ(pinPullUpDownToCheck,pinPullUpDownToSet);

    pinPullUpDownToSet = PULL_UP_DOWN_RESERVED;
    configurePinPullUpDown(validatedPin,pinPullUpDownToSet);
    pinPullUpDownToCheck = readPinPullUpDown(validatedPin);
    ASSERT_EQ(pinPullUpDownToCheck,pinPullUpDownToSet);

    pinPullUpDownToSet = PULL_UP_DOWN_NO_RESISTOR;
    configurePinPullUpDown(validatedPin,pinPullUpDownToSet);
    pinPullUpDownToCheck = readPinPullUpDown(validatedPin);
    ASSERT_EQ(pinPullUpDownToCheck,pinPullUpDownToSet);

    shutdownPinConfigDriver();

}

TEST(PinConfigDriver, testConfigureAndReadAndReleasePinEvent) {

    const PIN validatedPin = PIN_4;
    PIN_FUNCTION pinFunctionToCheck;
    PIN_EVENT pinEventToSet;
    PIN_EVENT pinEventToCheck;
    int fileDescriptor = -1;

    setupPinConfigDriver();

    pinEventToSet = PIN_EVENT_RISING;
    configurePinEventLFS(validatedPin, pinEventToSet, &fileDescriptor);
    pinFunctionToCheck = readPinFunction(validatedPin);
    pinEventToCheck = readPinEvent(validatedPin);
    ASSERT_EQ(pinFunctionToCheck, PIN_FUNCTION_INPUT);
    ASSERT_EQ(pinEventToCheck,pinEventToSet);
    ASSERT_GT(fileDescriptor, 0);
    releasePinEvent(fileDescriptor);
    fileDescriptor = -1;

    pinEventToSet = PIN_EVENT_FALLING;
    configurePinEventLFS(validatedPin, pinEventToSet, &fileDescriptor);
    pinFunctionToCheck = readPinFunction(validatedPin);
    pinEventToCheck = readPinEvent(validatedPin);
    ASSERT_EQ(pinFunctionToCheck, PIN_FUNCTION_INPUT);
    ASSERT_EQ(pinEventToCheck,pinEventToSet);
    ASSERT_GT(fileDescriptor, 0);
    releasePinEvent(fileDescriptor);
    fileDescriptor = -1;

    pinEventToSet = PIN_EVENT_BOTH;
    configurePinEventLFS(validatedPin, pinEventToSet, &fileDescriptor);
    pinFunctionToCheck = readPinFunction(validatedPin);
    pinEventToCheck = readPinEvent(validatedPin);
    ASSERT_EQ(pinFunctionToCheck, PIN_FUNCTION_INPUT);
    ASSERT_EQ(pinEventToCheck,pinEventToSet);
    ASSERT_GT(fileDescriptor, 0);
    releasePinEvent(fileDescriptor);
    fileDescriptor = -1;

    pinEventToSet = PIN_EVENT_NO_EVENT;
    configurePinEventLFS(validatedPin, pinEventToSet, &fileDescriptor);
    pinFunctionToCheck = readPinFunction(validatedPin);
    pinEventToCheck = readPinEvent(validatedPin);
    ASSERT_EQ(pinFunctionToCheck, PIN_FUNCTION_INPUT);
    ASSERT_EQ(pinEventToCheck,pinEventToSet);
    ASSERT_EQ(fileDescriptor, 0);
    releasePinEvent(fileDescriptor);
    fileDescriptor = -1;

    shutdownPinConfigDriver();

}