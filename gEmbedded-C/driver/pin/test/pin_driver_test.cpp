//
// Created by sondahi on 25.02.23.
//

#include <chrono>
#include <thread>

#include "gtest/gtest.h"
#include "pin_test.h"

extern "C" {
#include "pin_driver.h"
#include "peripheral.h"
}

TEST(PinDriverTest, testInitDestroyPinDriver) {

    volatile PIN_DRIVER_ERROR status;

    status = initPinDriver();
    ASSERT_EQ(status, PIN_DRIVER_ERROR_NO);
    ASSERT_EQ(isPinDriverInitialized(), PIN_DRIVER_TRUE);

    status = destroyPinDriver();
    ASSERT_EQ(status, PIN_DRIVER_ERROR_NO);
    ASSERT_EQ(isPinDriverInitialized(), PIN_DRIVER_FALSE);

}

TEST(PinDriverTest, testPinFunction) {

    const uint8_t pinNumber = PIN_NUMBER_SELF;
    uint8_t pinFunctionToSet, pinFunctionToRead;

    initPinDriver();

    pinFunctionToSet = PIN_CONFIG_FUNCTION_OUTPUT;
    setPinFunction(pinNumber, pinFunctionToSet);
    pinFunctionToRead = readPinFunction(pinNumber);
    ASSERT_EQ(pinFunctionToRead, pinFunctionToSet);

    pinFunctionToSet = PIN_CONFIG_FUNCTION_ALT0;
    setPinFunction(pinNumber, pinFunctionToSet);
    pinFunctionToRead = readPinFunction(pinNumber);
    ASSERT_EQ(pinFunctionToRead, pinFunctionToSet);

    pinFunctionToSet = PIN_CONFIG_FUNCTION_ALT1;
    setPinFunction(pinNumber, pinFunctionToSet);
    pinFunctionToRead = readPinFunction(pinNumber);
    ASSERT_EQ(pinFunctionToRead, pinFunctionToSet);

    pinFunctionToSet = PIN_CONFIG_FUNCTION_ALT2;
    setPinFunction(pinNumber, pinFunctionToSet);
    pinFunctionToRead = readPinFunction(pinNumber);
    ASSERT_EQ(pinFunctionToRead, pinFunctionToSet);

    pinFunctionToSet = PIN_CONFIG_FUNCTION_ALT3;
    setPinFunction(pinNumber, pinFunctionToSet);
    pinFunctionToRead = readPinFunction(pinNumber);
    ASSERT_EQ(pinFunctionToRead, pinFunctionToSet);

    pinFunctionToSet = PIN_CONFIG_FUNCTION_ALT4;
    setPinFunction(pinNumber, pinFunctionToSet);
    pinFunctionToRead = readPinFunction(pinNumber);
    ASSERT_EQ(pinFunctionToRead, pinFunctionToSet);

    pinFunctionToSet = PIN_CONFIG_FUNCTION_ALT5;
    setPinFunction(pinNumber, pinFunctionToSet);
    pinFunctionToRead = readPinFunction(pinNumber);
    ASSERT_EQ(pinFunctionToRead, pinFunctionToSet);

    pinFunctionToSet = PIN_CONFIG_FUNCTION_INPUT;
    setPinFunction(pinNumber, pinFunctionToSet);
    pinFunctionToRead = readPinFunction(pinNumber);
    ASSERT_EQ(pinFunctionToRead, pinFunctionToSet);

    destroyPinDriver();

}

TEST(PinDriverTest, testPinPullUpdown) {

    const uint8_t pinNumber = PIN_NUMBER_SELF;
    uint8_t pinPullUpDownToSet, pinPullUpDownToRead;

    initPinDriver();

    setPinFunction(pinNumber, PIN_CONFIG_FUNCTION_INPUT);

    pinPullUpDownToSet = PIN_CONFIG_PUD_PULL_UP;
    setPinPullUpDown(pinNumber, pinPullUpDownToSet);
    pinPullUpDownToRead = readPinPullUpDown(pinNumber);
    ASSERT_EQ(pinPullUpDownToRead, pinPullUpDownToSet);

    pinPullUpDownToSet = PIN_CONFIG_PUD_PULL_DOWN;
    setPinPullUpDown(pinNumber, pinPullUpDownToSet);
    pinPullUpDownToRead = readPinPullUpDown(pinNumber);
    ASSERT_EQ(pinPullUpDownToRead, pinPullUpDownToSet);

    pinPullUpDownToSet = PIN_CONFIG_PUD_NO_RESISTOR;
    setPinPullUpDown(pinNumber, pinPullUpDownToSet);
    pinPullUpDownToRead = readPinPullUpDown(pinNumber);
    ASSERT_EQ(pinPullUpDownToRead, pinPullUpDownToSet);

    destroyPinDriver();

}

TEST(PinDriverTest, testPinEvent) {

    const uint8_t pinNumber = PIN_NUMBER_SELF;
    uint8_t pinEventToSet, pinEventToRead;
    int fd = -1;

    initPinDriver();

    pinEventToSet = PIN_CONFIG_EVENT_RISING;
    setPinEvent(pinNumber, pinEventToSet, &fd);
    ASSERT_GT(fd, 0);
    pinEventToRead = readPinEvent(pinNumber);
    ASSERT_EQ(pinEventToRead, pinEventToSet);
    closePinEvent(fd);
    fd = -1;

    pinEventToSet = PIN_CONFIG_EVENT_FALLING;
    setPinEvent(pinNumber, pinEventToSet, &fd);
    ASSERT_GT(fd, 0);
    pinEventToRead = readPinEvent(pinNumber);
    ASSERT_EQ(pinEventToRead, pinEventToSet);
    closePinEvent(fd);
    fd = -1;

    pinEventToSet = PIN_CONFIG_EVENT_BOTH;
    setPinEvent(pinNumber, pinEventToSet, &fd);
    ASSERT_GT(fd, 0);
    pinEventToRead = readPinEvent(pinNumber);
    ASSERT_EQ(pinEventToRead, pinEventToSet);
    closePinEvent(fd);
    fd = -1;

    destroyPinDriver();

}

TEST(PinDriverTest, testGetBitField) {

    const uint8_t pinNumber = PIN_NUMBER_SELF;
    const uint32_t bitField = 1 << ((pinNumber % 32) * 1);

    ASSERT_EQ(getPinBitField(pinNumber), bitField);

}

TEST(PinDriverTest, testSetReadClearPin) {

    const uint8_t pinNumber = PIN_NUMBER_SELF;
    uint32_t bitField;
    uint32_t pinLevel;

    initPinDriver();

    setPinFunction(pinNumber, PIN_CONFIG_FUNCTION_OUTPUT);
    bitField = getPinBitField(pinNumber);

    setPin(bitField);
    pinLevel = readPin(bitField);
    ASSERT_GT(pinLevel, 0);

    clearPin(bitField);
    pinLevel = readPin(bitField);
    ASSERT_EQ(pinLevel, 0);

    setPinFunction(pinNumber, PIN_CONFIG_FUNCTION_INPUT);

    destroyPinDriver();

}

static void invokeRising(const uint32_t pinBitField) {
    std::this_thread::sleep_for(std::chrono::milliseconds(PIN_SLEEP_IN_MILSEC / 2));
    setPin(pinBitField);
}

static void invokeFalling(const uint32_t pinBitField) {
    std::this_thread::sleep_for(std::chrono::milliseconds(PIN_SLEEP_IN_MILSEC / 2));
    clearPin(pinBitField);
}

TEST(PinDriverTest, testPollPin) {

    const uint8_t outputPin = PIN_NUMBER_OUTPUT_LISTENER;
    const uint8_t outputPinFunction = PIN_CONFIG_FUNCTION_OUTPUT;
    uint32_t outputPinBitField;

    const uint8_t listenerPin = PIN_NUMBER_LISTENER;
    const uint8_t listenerPinConfigEvent = PIN_CONFIG_EVENT_BOTH;
    int listenerPinFd;
    const int listenerPinTimeout = PIN_SLEEP_IN_MILSEC;
    struct gpioevent_data listenerPinEventData = {
            .timestamp = 0,
            .id = 0
    };

    PIN_DRIVER_ERROR status;

    initPinDriver();

    setPinFunction(outputPin, outputPinFunction);
    outputPinBitField = getPinBitField(outputPin);
    clearPin(outputPinBitField);

    setPinEvent(listenerPin, listenerPinConfigEvent, &listenerPinFd);

    status = pollPin(listenerPinFd, listenerPinTimeout, &listenerPinEventData);
    ASSERT_EQ(status, PIN_DRIVER_ERROR_IO_POLL_TIMEOUT);
    ASSERT_EQ(listenerPinEventData.timestamp, 0);
    ASSERT_EQ(listenerPinEventData.id, 0);

    std::thread risingSuccessOnBoth(invokeRising, outputPinBitField);
    status = pollPin(listenerPinFd, listenerPinTimeout, &listenerPinEventData);
    risingSuccessOnBoth.join();
    ASSERT_EQ(status, PIN_DRIVER_ERROR_NO);
    ASSERT_GT(listenerPinEventData.timestamp, 0);
    ASSERT_EQ(listenerPinEventData.id, GPIOEVENT_EVENT_RISING_EDGE);
    listenerPinEventData.timestamp = 0;
    listenerPinEventData.id = 0;

    std::thread fallingSuccessOnBoth(invokeFalling, outputPinBitField);
    status = pollPin(listenerPinFd, listenerPinTimeout, &listenerPinEventData);
    fallingSuccessOnBoth.join();
    ASSERT_EQ(status, PIN_DRIVER_ERROR_NO);
    ASSERT_GT(listenerPinEventData.timestamp, 0);
    ASSERT_EQ(listenerPinEventData.id, GPIOEVENT_EVENT_FALLING_EDGE);

    closePinEvent(listenerPinFd);

    destroyPinDriver();

}