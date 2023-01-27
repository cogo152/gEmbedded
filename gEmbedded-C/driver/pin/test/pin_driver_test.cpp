//
// Created by sondahi on 15.01.23.
//

#include <chrono>
#include <thread>

#include "gtest/gtest.h"
extern "C" {
#include "pin.h"
#include "pin_driver.h"
#include "peripheral.h"
}

#define PIN_OUTPUT_SELF                    (22)
#define PIN_OUTPUT_PULLDOWN                (17)
#define PIN_OUTPUT_PULLUP                  (20)
#define PIN_OUTPUT_LISTENER                (5)
#define PIN_INPUT_PULLDOWN                 (27)
#define PIN_INPUT_PULLUP                   (21)
#define PIN_LISTENER                       (6)

#define PIN_SLEEP_IN_MILSEC                (1000)

output_pin_t outputPin_SELF = {
        .number = PIN_OUTPUT_SELF
};

output_pin_t outputPin_PULLDOWN = {
        .number = PIN_OUTPUT_PULLDOWN
};

output_pin_t outputPin_PULLUP = {
        .number = PIN_OUTPUT_PULLUP
};

output_pin_t outputPin_LISTENER = {
        .number = PIN_OUTPUT_LISTENER,
};

input_pin_t inputPin_PULLDOWN = {
        .number = PIN_INPUT_PULLDOWN,
};

input_pin_t inputPin_PULLUP = {
        .number = PIN_INPUT_PULLUP,
};

listener_pin_t listenerPin = {
        .number = PIN_LISTENER,
        .timeoutInMilSec = PIN_SLEEP_IN_MILSEC
};

static int testSetupPinDriver() {

    const int status = setupPinDriver();
    if (status != PIN_DRIVER_EXCEPTION_NO_EXCEPTION) {
        return status;
    }

    return PIN_DRIVER_EXCEPTION_NO_EXCEPTION;

}

static int testShutdownPinDriver() {

    const int status = shutdownPinDriver();
    if (status != PIN_DRIVER_EXCEPTION_NO_EXCEPTION) {
        return status;
    }

    return PIN_DRIVER_EXCEPTION_NO_EXCEPTION;

}

TEST(PinDriverTest, testSetupShutdownPinDriver) {

    int status;
    status = testSetupPinDriver();
    ASSERT_EQ(status, PIN_DRIVER_EXCEPTION_NO_EXCEPTION);

    status = testShutdownPinDriver();
    ASSERT_EQ(status, PIN_DRIVER_EXCEPTION_NO_EXCEPTION);

}

TEST(PinDriverTest, testOutputPin) {

    int status;

    setupPinDriver();

    status = openOutputPin(&outputPin_SELF);
    ASSERT_EQ(status, PIN_CONFIG_EXCEPTION_NO_EXCEPTION);
    ASSERT_EQ(outputPin_SELF.reference, 1 << ((outputPin_SELF.number % 32) * 1));

    setOutputPinHigh(&outputPin_SELF);
    readOutputPinLevel(&outputPin_SELF);
    ASSERT_EQ(outputPin_SELF.level, PIN_IO_LEVEL_HIGH);

    setOutputPinLow(&outputPin_SELF);
    readOutputPinLevel(&outputPin_SELF);
    ASSERT_EQ(outputPin_SELF.level, PIN_IO_LEVEL_LOW);

    closeOutputPin(&outputPin_SELF);

    shutdownPinDriver();

}

TEST(PinDriverTest, testInputPin) {
    int status;

    setupPinDriver();
    openOutputPin(&outputPin_PULLDOWN);
    openOutputPin(&outputPin_PULLUP);

    inputPin_PULLDOWN.pullUpDown = PIN_CONFIG_PUD_NO_RESISTOR;
    status = openInputPin(&inputPin_PULLDOWN);
    ASSERT_EQ(status, PIN_CONFIG_EXCEPTION_NO_EXCEPTION);
    ASSERT_EQ(inputPin_PULLDOWN.reference, 1 << ((inputPin_PULLDOWN.number % 32) * 1));

    setOutputPinHigh(&outputPin_PULLDOWN);
    std::this_thread::sleep_for(std::chrono::milliseconds(PIN_SLEEP_IN_MILSEC));
    readInputPinLevel(&inputPin_PULLDOWN);
    ASSERT_EQ(inputPin_PULLDOWN.level, PIN_IO_LEVEL_HIGH);
    setOutputPinLow(&outputPin_PULLDOWN);
    std::this_thread::sleep_for(std::chrono::milliseconds(PIN_SLEEP_IN_MILSEC));
    readInputPinLevel(&inputPin_PULLDOWN);
    ASSERT_EQ(inputPin_PULLDOWN.level, PIN_IO_LEVEL_LOW);

    inputPin_PULLDOWN.pullUpDown = PIN_CONFIG_PUD_PULL_DOWN;
    status = updateInputPin(&inputPin_PULLDOWN);
    ASSERT_EQ(status, PIN_CONFIG_EXCEPTION_NO_EXCEPTION);

    setOutputPinHigh(&outputPin_PULLDOWN);
    std::this_thread::sleep_for(std::chrono::milliseconds(PIN_SLEEP_IN_MILSEC));
    readInputPinLevel(&inputPin_PULLDOWN);
    ASSERT_EQ(inputPin_PULLDOWN.level, PIN_IO_LEVEL_HIGH);
    setOutputPinLow(&outputPin_PULLDOWN);
    std::this_thread::sleep_for(std::chrono::milliseconds(PIN_SLEEP_IN_MILSEC));
    readInputPinLevel(&inputPin_PULLDOWN);
    ASSERT_EQ(inputPin_PULLDOWN.level, PIN_IO_LEVEL_LOW);

    inputPin_PULLUP.pullUpDown = PIN_CONFIG_PUD_NO_RESISTOR;
    status = openInputPin(&inputPin_PULLUP);
    ASSERT_EQ(status, PIN_CONFIG_EXCEPTION_NO_EXCEPTION);
    ASSERT_EQ(inputPin_PULLUP.reference, 1 << ((inputPin_PULLUP.number % 32) * 1));

    setOutputPinHigh(&outputPin_PULLUP);
    std::this_thread::sleep_for(std::chrono::milliseconds(PIN_SLEEP_IN_MILSEC));
    readInputPinLevel(&inputPin_PULLUP);
    ASSERT_EQ(inputPin_PULLUP.level, PIN_IO_LEVEL_LOW);
    setOutputPinLow(&outputPin_PULLUP);
    std::this_thread::sleep_for(std::chrono::milliseconds(PIN_SLEEP_IN_MILSEC));
    readInputPinLevel(&inputPin_PULLUP);
    ASSERT_EQ(inputPin_PULLUP.level, PIN_IO_LEVEL_HIGH);

    inputPin_PULLUP.pullUpDown = PIN_CONFIG_PUD_PULL_UP;
    status = updateInputPin(&inputPin_PULLUP);
    ASSERT_EQ(status, PIN_CONFIG_EXCEPTION_NO_EXCEPTION);

    setOutputPinHigh(&outputPin_PULLUP);
    std::this_thread::sleep_for(std::chrono::milliseconds(PIN_SLEEP_IN_MILSEC));
    readInputPinLevel(&inputPin_PULLUP);
    ASSERT_EQ(inputPin_PULLUP.level, PIN_IO_LEVEL_LOW);
    setOutputPinLow(&outputPin_PULLUP);
    std::this_thread::sleep_for(std::chrono::milliseconds(PIN_SLEEP_IN_MILSEC));
    readInputPinLevel(&inputPin_PULLUP);
    ASSERT_EQ(inputPin_PULLUP.level, PIN_IO_LEVEL_HIGH);

    closeOutputPin(&outputPin_PULLDOWN);
    closeOutputPin(&outputPin_PULLUP);

    closeInputPin(&inputPin_PULLDOWN);
    closeInputPin(&inputPin_PULLUP);

    shutdownPinDriver();

}

static void invokeRising(output_pin_t *const outputPin) {
    std::this_thread::sleep_for(std::chrono::milliseconds(PIN_SLEEP_IN_MILSEC / 2));
    setOutputPinHigh(outputPin);
}

static void invokeFalling(output_pin_t *const outputPin) {
    std::this_thread::sleep_for(std::chrono::milliseconds(PIN_SLEEP_IN_MILSEC / 2));
    setOutputPinLow(outputPin);
}

TEST(PinDriverTest, testListenerPin) {

    int status;

    setupPinDriver();
    openOutputPin(&outputPin_LISTENER);

    // set pinevent both
    listenerPin.cevent = PIN_CONFIG_EVENT_BOTH;
    status = openListenerPin(&listenerPin);
    ASSERT_EQ(status, PIN_CONFIG_EXCEPTION_NO_EXCEPTION);
    ASSERT_GT(listenerPin.reference, 0);

    // no trigger timeout
    status = readListenerPinEvent(&listenerPin);
    ASSERT_EQ(status, PIN_IO_EXCEPTION_POLL_TIMEOUT_ERROR);

    // trig rising and success
    listenerPin.timeStamp = 0;
    std::thread risingSuccessOnBoth(invokeRising, &outputPin_LISTENER);
    status = readListenerPinEvent(&listenerPin);
    risingSuccessOnBoth.join();
    ASSERT_EQ(status, PIN_IO_EXCEPTION_NO_EXCEPTION);
    ASSERT_EQ(listenerPin.revent, PIN_IO_EVENT_RISING);
    ASSERT_GT(listenerPin.timeStamp, 0);

    // trig falling and success
    listenerPin.timeStamp = 0;
    std::thread fallingSuccessOnBoth(invokeFalling, &outputPin_LISTENER);
    status = readListenerPinEvent(&listenerPin);
    fallingSuccessOnBoth.join();
    ASSERT_EQ(status, PIN_IO_EXCEPTION_NO_EXCEPTION);
    ASSERT_EQ(listenerPin.revent, PIN_IO_EVENT_FALLING);
    ASSERT_GT(listenerPin.timeStamp, 0);

    // prepare falling fails on rising
    setOutputPinHigh(&outputPin_LISTENER);
    // update event rising success
    listenerPin.cevent = PIN_CONFIG_EVENT_RISING;
    status = updateListenerPin(&listenerPin);
    ASSERT_EQ(status, PIN_CONFIG_EXCEPTION_NO_EXCEPTION);

    // trig falling fail timeout on rising
    std::thread fallingFailOnRising(invokeFalling, &outputPin_LISTENER);
    status = readListenerPinEvent(&listenerPin);
    fallingFailOnRising.join();
    ASSERT_EQ(status, PIN_IO_EXCEPTION_POLL_TIMEOUT_ERROR);

    // trig rising success on rising
    listenerPin.timeStamp = 0;
    std::thread risingSuccessOnRising(invokeRising, &outputPin_LISTENER);
    status = readListenerPinEvent(&listenerPin);
    risingSuccessOnRising.join();
    ASSERT_EQ(status, PIN_IO_EXCEPTION_NO_EXCEPTION);
    ASSERT_EQ(listenerPin.revent, PIN_IO_EVENT_RISING);
    ASSERT_GT(listenerPin.timeStamp, 0);

    // prepare rising fails on falling
    setOutputPinLow(&outputPin_LISTENER);
    // update event falling success
    listenerPin.cevent = PIN_CONFIG_EVENT_FALLING;
    status = updateListenerPin(&listenerPin);
    ASSERT_EQ(status, PIN_CONFIG_EXCEPTION_NO_EXCEPTION);

    // trig rising fail timeout on falling
    std::thread risingFailOnFalling(invokeRising, &outputPin_LISTENER);
    status = readListenerPinEvent(&listenerPin);
    risingFailOnFalling.join();
    ASSERT_EQ(status, PIN_IO_EXCEPTION_POLL_TIMEOUT_ERROR);

    // trig falling success on falling
    listenerPin.timeStamp = 0;
    std::thread fallingSuccessOnFalling(invokeFalling, &outputPin_LISTENER);
    status = readListenerPinEvent(&listenerPin);
    fallingSuccessOnFalling.join();
    ASSERT_EQ(status, PIN_IO_EXCEPTION_NO_EXCEPTION);
    ASSERT_EQ(listenerPin.revent, PIN_IO_EVENT_FALLING);
    ASSERT_GT(listenerPin.timeStamp, 0);

    closeOutputPin(&outputPin_LISTENER);

    closeListenerPin(&listenerPin);

    shutdownPinDriver();

}