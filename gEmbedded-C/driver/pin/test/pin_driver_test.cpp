//
// Created by sondahi on 15.01.23.
//

#include <chrono>
#include <thread>

#include "gtest/gtest.h"
#include "pin_numbers_test.h"

extern "C" {
#include "pin_driver.h"
#include "peripheral.h"
extern void setPinFunction(pin_t *pin);
extern uint8_t getPinFunction(pin_t *pin);
extern void setPinPullUpDown(pin_t *pin);
extern uint8_t getPinPullUpDown(pin_t *pin);
extern int setPinEvent(pin_t *pin);
extern uint8_t getPinEvent(pin_t *pin);
}

#define PIN_SLEEP_IN_MILSEC                (100)

static int testInitPinDriver() {

    const volatile int status = initPinDriver();
    if (status != PIN_DRIVER_ERROR_NO) {
        return status;
    }

    return PIN_DRIVER_ERROR_NO;

}

static int testDestroyPinDriver() {

    const volatile int status = destroyPinDriver();
    if (status != PIN_DRIVER_ERROR_NO) {
        return status;
    }

    return PIN_DRIVER_ERROR_NO;

}

TEST(PinDriverTest, testInitDestroyPinDriver) {

    volatile int status;
    status = testInitPinDriver();
    ASSERT_EQ(status, PIN_DRIVER_ERROR_NO);

    status = testDestroyPinDriver();
    ASSERT_EQ(status, PIN_DRIVER_ERROR_NO);

}

TEST(PinDriverTest, testOutputPin) {

    volatile int status;
    pin_t outputPin_SELF = {
            .cNumber = PIN_OUTPUT_SELF,
            .cFunction = PIN_CONFIG_FUNCTION_OUTPUT
    };

    initPinDriver();

    status = initOutputPin(&outputPin_SELF);
    ASSERT_EQ(status, PIN_DRIVER_ERROR_NO);
    ASSERT_EQ(outputPin_SELF.ioReference, 1 << ((outputPin_SELF.cNumber % 32) * 1));
    ASSERT_EQ(outputPin_SELF.ioState, PIN_DRIVER_PIN_STATE_ELIGIBLE);

    status = setPin(&outputPin_SELF);
    ASSERT_EQ(status, PIN_DRIVER_ERROR_NO);
    status = readPin(&outputPin_SELF);
    ASSERT_EQ(status, PIN_DRIVER_ERROR_NO);
    ASSERT_EQ(outputPin_SELF.ioLevel, PIN_DRIVER_IO_LEVEL_HIGH);

    status = clearPin(&outputPin_SELF);
    ASSERT_EQ(status, PIN_DRIVER_ERROR_NO);
    status = readPin(&outputPin_SELF);
    ASSERT_EQ(status, PIN_DRIVER_ERROR_NO);
    ASSERT_EQ(outputPin_SELF.ioLevel, PIN_DRIVER_IO_LEVEL_LOW);

    status = destroyOutputPin(&outputPin_SELF);
    ASSERT_EQ(status, PIN_DRIVER_ERROR_NO);
    ASSERT_EQ(outputPin_SELF.ioState, PIN_DRIVER_PIN_STATE_INELIGIBLE);

    status = setPin(&outputPin_SELF);
    ASSERT_EQ(status, PIN_DRIVER_ERROR_IO_STATE);
    status = clearPin(&outputPin_SELF);
    ASSERT_EQ(status, PIN_DRIVER_ERROR_IO_STATE);
    status = readPin(&outputPin_SELF);
    ASSERT_EQ(status, PIN_DRIVER_ERROR_IO_STATE);

    destroyPinDriver();

}

TEST(PinDriverTest, testInputPin) {

    volatile int status;
    pin_t outputPin_PULLDOWN = {
            .cNumber = PIN_OUTPUT_PULLDOWN,
            .cFunction = PIN_CONFIG_FUNCTION_OUTPUT
    };
    pin_t outputPin_PULLUP = {
            .cNumber = PIN_OUTPUT_PULLUP,
            .cFunction = PIN_CONFIG_FUNCTION_OUTPUT

    };
    pin_t inputPin_PULLDOWN = {
            .cNumber = PIN_INPUT_PULLDOWN,
            .cFunction = PIN_CONFIG_FUNCTION_INPUT,
            .cPullUpDown = PIN_CONFIG_PUD_NO_RESISTOR

    };
    pin_t inputPin_PULLUP = {
            .cNumber = PIN_INPUT_PULLUP,
            .cFunction = PIN_CONFIG_FUNCTION_INPUT,
            .cPullUpDown = PIN_CONFIG_PUD_NO_RESISTOR
    };

    initPinDriver();

    initOutputPin(&outputPin_PULLDOWN);
    clearPin(&outputPin_PULLDOWN);
    initOutputPin(&outputPin_PULLUP);
    clearPin(&outputPin_PULLUP);

    status = initInputPin(&inputPin_PULLDOWN);
    ASSERT_EQ(status, PIN_DRIVER_ERROR_NO);
    ASSERT_EQ(inputPin_PULLDOWN.ioReference, 1 << ((inputPin_PULLDOWN.cNumber % 32) * 1));
    ASSERT_EQ(inputPin_PULLDOWN.ioState, PIN_DRIVER_PIN_STATE_ELIGIBLE);

    setPin(&outputPin_PULLDOWN);
    std::this_thread::sleep_for(std::chrono::milliseconds(PIN_SLEEP_IN_MILSEC));
    status = readPin(&inputPin_PULLDOWN);
    ASSERT_EQ(status, PIN_DRIVER_ERROR_NO);
    ASSERT_EQ(inputPin_PULLDOWN.ioLevel, PIN_DRIVER_IO_LEVEL_HIGH);
    clearPin(&outputPin_PULLDOWN);
    std::this_thread::sleep_for(std::chrono::milliseconds(PIN_SLEEP_IN_MILSEC));
    status = readPin(&inputPin_PULLDOWN);
    ASSERT_EQ(status, PIN_DRIVER_ERROR_NO);
    ASSERT_EQ(inputPin_PULLDOWN.ioLevel, PIN_DRIVER_IO_LEVEL_LOW);

    inputPin_PULLDOWN.cPullUpDown = PIN_CONFIG_PUD_PULL_DOWN;
    status = updateInputPin(&inputPin_PULLDOWN);
    ASSERT_NE(inputPin_PULLDOWN.ioState, PIN_DRIVER_PIN_STATE_INELIGIBLE);
    ASSERT_EQ(status, PIN_DRIVER_ERROR_NO);

    setPin(&outputPin_PULLDOWN);
    std::this_thread::sleep_for(std::chrono::milliseconds(PIN_SLEEP_IN_MILSEC));
    status = readPin(&inputPin_PULLDOWN);
    ASSERT_EQ(status, PIN_DRIVER_ERROR_NO);
    ASSERT_EQ(inputPin_PULLDOWN.ioLevel, PIN_DRIVER_IO_LEVEL_HIGH);
    clearPin(&outputPin_PULLDOWN);
    std::this_thread::sleep_for(std::chrono::milliseconds(PIN_SLEEP_IN_MILSEC));
    status = readPin(&inputPin_PULLDOWN);
    ASSERT_EQ(status, PIN_DRIVER_ERROR_NO);
    ASSERT_EQ(inputPin_PULLDOWN.ioLevel, PIN_DRIVER_IO_LEVEL_LOW);

    status = initInputPin(&inputPin_PULLUP);
    ASSERT_EQ(status, PIN_DRIVER_ERROR_NO);
    ASSERT_EQ(inputPin_PULLUP.ioReference, 1 << ((inputPin_PULLUP.cNumber % 32) * 1));
    ASSERT_EQ(inputPin_PULLUP.ioState, PIN_DRIVER_PIN_STATE_ELIGIBLE);

    setPin(&outputPin_PULLUP);
    std::this_thread::sleep_for(std::chrono::milliseconds(PIN_SLEEP_IN_MILSEC));
    status = readPin(&inputPin_PULLUP);
    ASSERT_EQ(status, PIN_DRIVER_ERROR_NO);
    ASSERT_EQ(inputPin_PULLUP.ioLevel, PIN_DRIVER_IO_LEVEL_LOW);
    clearPin(&outputPin_PULLUP);
    std::this_thread::sleep_for(std::chrono::milliseconds(PIN_SLEEP_IN_MILSEC));
    status = readPin(&inputPin_PULLUP);
    ASSERT_EQ(status, PIN_DRIVER_ERROR_NO);
    ASSERT_EQ(inputPin_PULLUP.ioLevel, PIN_DRIVER_IO_LEVEL_HIGH);

    inputPin_PULLUP.cPullUpDown = PIN_CONFIG_PUD_PULL_UP;
    status = updateInputPin(&inputPin_PULLUP);
    ASSERT_NE(inputPin_PULLUP.ioState, PIN_DRIVER_PIN_STATE_INELIGIBLE);
    ASSERT_EQ(status, PIN_DRIVER_ERROR_NO);

    setPin(&outputPin_PULLUP);
    std::this_thread::sleep_for(std::chrono::milliseconds(PIN_SLEEP_IN_MILSEC));
    status = readPin(&inputPin_PULLUP);
    ASSERT_EQ(status, PIN_DRIVER_ERROR_NO);
    ASSERT_EQ(inputPin_PULLUP.ioLevel, PIN_DRIVER_IO_LEVEL_LOW);
    clearPin(&outputPin_PULLUP);
    std::this_thread::sleep_for(std::chrono::milliseconds(PIN_SLEEP_IN_MILSEC));
    status = readPin(&inputPin_PULLUP);
    ASSERT_EQ(status, PIN_DRIVER_ERROR_NO);
    ASSERT_EQ(inputPin_PULLUP.ioLevel, PIN_DRIVER_IO_LEVEL_HIGH);

    destroyOutputPin(&outputPin_PULLDOWN);
    destroyOutputPin(&outputPin_PULLUP);

    status = destroyInputPin(&inputPin_PULLDOWN);
    ASSERT_EQ(status, PIN_DRIVER_ERROR_NO);
    ASSERT_EQ(inputPin_PULLDOWN.ioState, PIN_DRIVER_PIN_STATE_INELIGIBLE);
    status = readPin(&inputPin_PULLDOWN);
    ASSERT_EQ(status, PIN_DRIVER_ERROR_IO_STATE);

    status = destroyInputPin(&inputPin_PULLUP);
    ASSERT_EQ(status, PIN_DRIVER_ERROR_NO);
    ASSERT_EQ(inputPin_PULLUP.ioState, PIN_DRIVER_PIN_STATE_INELIGIBLE);
    status = readPin(&inputPin_PULLUP);
    ASSERT_EQ(status, PIN_DRIVER_ERROR_IO_STATE);

    destroyPinDriver();

}

static void invokeRising(pin_t *const outputPin) {
    std::this_thread::sleep_for(std::chrono::milliseconds(PIN_SLEEP_IN_MILSEC / 2));
    setPin(outputPin);
}

static void invokeFalling(pin_t *const outputPin) {
    std::this_thread::sleep_for(std::chrono::milliseconds(PIN_SLEEP_IN_MILSEC / 2));
    clearPin(outputPin);
}

TEST(PinDriverTest, testListenerPin) {

    volatile int status;
    pin_t outputPin_LISTENER = {
            .cNumber = PIN_OUTPUT_LISTENER,
            .cFunction = PIN_CONFIG_FUNCTION_OUTPUT
    };
    pin_t listenerPin = {
            .cNumber = PIN_LISTENER,
            .cFunction = PIN_CONFIG_FUNCTION_INPUT,
            .cEvent = PIN_CONFIG_EVENT_BOTH,
            .cEventTimeout = PIN_SLEEP_IN_MILSEC
    };

    initPinDriver();
    initOutputPin(&outputPin_LISTENER);
    clearPin(&outputPin_LISTENER);

    // event both
    status = initListenerPin(&listenerPin);
    ASSERT_EQ(status, PIN_DRIVER_ERROR_NO);
    ASSERT_GT(listenerPin.ioReference, 0);
    ASSERT_EQ(listenerPin.ioState, PIN_DRIVER_PIN_STATE_ELIGIBLE);


    // no trigger timeout
    status = pollPin(&listenerPin);
    ASSERT_EQ(status, PIN_DRIVER_ERROR_IO_POLL_TIMEOUT);

    // trig rising and success
    listenerPin.ioTimeStamp = 0;
    listenerPin.ioEvent = PIN_DRIVER_IO_EVENT_FALLING;
    std::thread risingSuccessOnBoth(invokeRising, &outputPin_LISTENER);
    status = pollPin(&listenerPin);
    risingSuccessOnBoth.join();
    ASSERT_EQ(status, PIN_DRIVER_ERROR_NO);
    ASSERT_EQ(listenerPin.ioEvent, PIN_DRIVER_IO_EVENT_RISING);
    ASSERT_GT(listenerPin.ioTimeStamp, 0);

    // trig falling and success
    listenerPin.ioTimeStamp = 0;
    listenerPin.ioEvent = PIN_DRIVER_IO_EVENT_RISING;
    std::thread fallingSuccessOnBoth(invokeFalling, &outputPin_LISTENER);
    status = pollPin(&listenerPin);
    fallingSuccessOnBoth.join();
    ASSERT_EQ(status, PIN_DRIVER_ERROR_NO);
    ASSERT_EQ(listenerPin.ioEvent, PIN_DRIVER_IO_EVENT_FALLING);
    ASSERT_GT(listenerPin.ioTimeStamp, 0);

    // prepare falling fails on rising
    setPin(&outputPin_LISTENER);

    // update event rising success
    listenerPin.cEvent = PIN_CONFIG_EVENT_RISING;
    status = updateListenerPin(&listenerPin);
    ASSERT_NE(listenerPin.ioState, PIN_DRIVER_PIN_STATE_INELIGIBLE);
    ASSERT_EQ(status, PIN_DRIVER_ERROR_NO);

    // trig falling fail timeout on rising
    std::thread fallingFailOnRising(invokeFalling, &outputPin_LISTENER);
    status = pollPin(&listenerPin);
    fallingFailOnRising.join();
    ASSERT_EQ(status, PIN_DRIVER_ERROR_IO_POLL_TIMEOUT);

    // trig rising success on rising
    listenerPin.ioTimeStamp = 0;
    listenerPin.ioEvent = PIN_DRIVER_IO_EVENT_FALLING;
    std::thread risingSuccessOnRising(invokeRising, &outputPin_LISTENER);
    status = pollPin(&listenerPin);
    risingSuccessOnRising.join();
    ASSERT_EQ(status, PIN_DRIVER_ERROR_NO);
    ASSERT_EQ(listenerPin.ioEvent, PIN_DRIVER_IO_EVENT_RISING);
    ASSERT_GT(listenerPin.ioTimeStamp, 0);

    // prepare rising fails on falling
    clearPin(&outputPin_LISTENER);

    // update event falling success
    listenerPin.cEvent = PIN_CONFIG_EVENT_FALLING;
    status = updateListenerPin(&listenerPin);
    ASSERT_NE(listenerPin.ioState, PIN_DRIVER_PIN_STATE_INELIGIBLE);
    ASSERT_EQ(status, PIN_DRIVER_ERROR_NO);

    // trig rising fail timeout on falling
    std::thread risingFailOnFalling(invokeRising, &outputPin_LISTENER);
    status = pollPin(&listenerPin);
    risingFailOnFalling.join();
    ASSERT_EQ(status, PIN_DRIVER_ERROR_IO_POLL_TIMEOUT);

    // trig falling success on falling
    listenerPin.ioTimeStamp = 0;
    listenerPin.ioEvent = PIN_DRIVER_IO_EVENT_RISING;
    std::thread fallingSuccessOnFalling(invokeFalling, &outputPin_LISTENER);
    status = pollPin(&listenerPin);
    fallingSuccessOnFalling.join();
    ASSERT_EQ(status, PIN_DRIVER_ERROR_NO);
    ASSERT_EQ(listenerPin.ioEvent, PIN_DRIVER_IO_EVENT_FALLING);
    ASSERT_GT(listenerPin.ioTimeStamp, 0);

    destroyOutputPin(&outputPin_LISTENER);

    status = destroyListenerPin(&listenerPin);
    ASSERT_EQ(status, PIN_DRIVER_ERROR_NO);
    ASSERT_EQ(listenerPin.ioState, PIN_DRIVER_PIN_STATE_INELIGIBLE);
    status = pollPin(&listenerPin);
    ASSERT_EQ(status, PIN_DRIVER_ERROR_IO_STATE);

    destroyPinDriver();

}