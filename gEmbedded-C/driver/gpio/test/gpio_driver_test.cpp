//
// Created by sondahi on 15.01.23.
//

#include <chrono>
#include <thread>

#include "common_test.h"
#include "gpio_test.h"

#include "driver_context.h"
#include "gpio_driver.h"

TEST(GpioDriverTest, testOutputPin) {

    int status;
    struct output_pin_t outputPin;
    outputPin.number = GPIO_OUTPUT_SELF;

    setupDrivers();

    status = openOutputPin(&outputPin);
    ASSERT_EQ(status, GPIO_STATUS_SUCCESS);
    ASSERT_EQ(outputPin.reference, 0b1 << ((outputPin.number % 32) * 1));
    ASSERT_EQ(outputPin.status, GPIO_PIN_OPENED);

    status = openOutputPin(&outputPin);
    ASSERT_EQ(status, GPIO_STATUS_CONFIG_ERROR);

    status = setOutputPinHigh(&outputPin);
    ASSERT_EQ(status, GPIO_STATUS_SUCCESS);
    status = readOutputPinLevel(&outputPin);
    ASSERT_EQ(status, GPIO_STATUS_SUCCESS);
    ASSERT_EQ(outputPin.level, GPIO_PIN_LEVEL_HIGH);

    status = setOutputPinLow(&outputPin);
    ASSERT_EQ(status, GPIO_STATUS_SUCCESS);
    status = readOutputPinLevel(&outputPin);
    ASSERT_EQ(status, GPIO_STATUS_SUCCESS);
    ASSERT_EQ(outputPin.level, GPIO_PIN_LEVEL_LOW);

    closeOutputPin(&outputPin);
    ASSERT_EQ(outputPin.status, GPIO_PIN_CLOSED);

    status = setOutputPinHigh(&outputPin);
    ASSERT_EQ(status, GPIO_STATUS_CONFIG_ERROR);
    status = readOutputPinLevel(&outputPin);
    ASSERT_EQ(status, GPIO_STATUS_CONFIG_ERROR);

    shutdownDrivers();

}

TEST(GpioDriverTest, testInputPin) {
    int status;

    struct output_pin_t pullDown_OUTPUTPIN;
    struct input_pin_t pullDown_INPUTPIN;
    struct output_pin_t pullUp_OUTPUTPIN;
    struct input_pin_t pullUp_INPUTPIN;

    pullDown_OUTPUTPIN.number = GPIO_PULLDOWN_OUTPUT;
    pullDown_INPUTPIN.number = GPIO_PULLDOWN_INPUT;
    pullUp_OUTPUTPIN.number = GPIO_PULLUP_OUTPUT;
    pullUp_INPUTPIN.number = GPIO_PULLUP_INPUT;

    setupDrivers();
    openOutputPin(&pullDown_OUTPUTPIN);
    openOutputPin(&pullUp_OUTPUTPIN);

    pullDown_INPUTPIN.pullUpDown = GPIO_PIN_PUD_NO_RESISTOR;
    status = openInputPin(&pullDown_INPUTPIN);
    ASSERT_EQ(status, GPIO_STATUS_SUCCESS);
    ASSERT_EQ(pullDown_INPUTPIN.reference, 0b1 << ((pullDown_INPUTPIN.number % 32) * 1));
    ASSERT_EQ(pullDown_INPUTPIN.status, GPIO_PIN_OPENED);

    status = openInputPin(&pullDown_INPUTPIN);
    ASSERT_EQ(status, GPIO_STATUS_CONFIG_ERROR);

    setOutputPinHigh(&pullDown_OUTPUTPIN);
    std::this_thread::sleep_for(std::chrono::milliseconds(GPIO_SLEEP_IN_MILSEC));
    status = readInputPinLevel(&pullDown_INPUTPIN);
    ASSERT_EQ(status, GPIO_STATUS_SUCCESS);
    ASSERT_EQ(pullDown_INPUTPIN.level, GPIO_PIN_LEVEL_HIGH);
    setOutputPinLow(&pullDown_OUTPUTPIN);
    std::this_thread::sleep_for(std::chrono::milliseconds(GPIO_SLEEP_IN_MILSEC));
    status = readInputPinLevel(&pullDown_INPUTPIN);
    ASSERT_EQ(status, GPIO_STATUS_SUCCESS);
    ASSERT_EQ(pullDown_INPUTPIN.level, GPIO_PIN_LEVEL_LOW);

    pullDown_INPUTPIN.pullUpDown = GPIO_PIN_PUD_PULL_DOWN;
    status = updateInputPin(&pullDown_INPUTPIN);
    ASSERT_EQ(status, GPIO_STATUS_SUCCESS);

    setOutputPinHigh(&pullDown_OUTPUTPIN);
    std::this_thread::sleep_for(std::chrono::milliseconds(GPIO_SLEEP_IN_MILSEC));
    status = readInputPinLevel(&pullDown_INPUTPIN);
    ASSERT_EQ(status, GPIO_STATUS_SUCCESS);
    ASSERT_EQ(pullDown_INPUTPIN.level, GPIO_PIN_LEVEL_HIGH);
    setOutputPinLow(&pullDown_OUTPUTPIN);
    std::this_thread::sleep_for(std::chrono::milliseconds(GPIO_SLEEP_IN_MILSEC));
    status = readInputPinLevel(&pullDown_INPUTPIN);
    ASSERT_EQ(status, GPIO_STATUS_SUCCESS);
    ASSERT_EQ(pullDown_INPUTPIN.level, GPIO_PIN_LEVEL_LOW);

    pullUp_INPUTPIN.pullUpDown = GPIO_PIN_PUD_NO_RESISTOR;
    status = openInputPin(&pullUp_INPUTPIN);
    ASSERT_EQ(status, GPIO_STATUS_SUCCESS);
    ASSERT_EQ(pullUp_INPUTPIN.reference, 0b1 << ((pullUp_INPUTPIN.number % 32) * 1));
    ASSERT_EQ(pullUp_INPUTPIN.status, GPIO_PIN_OPENED);

    status = openInputPin(&pullUp_INPUTPIN);
    ASSERT_EQ(status, GPIO_STATUS_CONFIG_ERROR);

    setOutputPinHigh(&pullUp_OUTPUTPIN);
    std::this_thread::sleep_for(std::chrono::milliseconds(GPIO_SLEEP_IN_MILSEC));
    status = readInputPinLevel(&pullUp_INPUTPIN);
    ASSERT_EQ(status, GPIO_STATUS_SUCCESS);
    ASSERT_EQ(pullUp_INPUTPIN.level, GPIO_PIN_LEVEL_LOW);
    setOutputPinLow(&pullUp_OUTPUTPIN);
    std::this_thread::sleep_for(std::chrono::milliseconds(GPIO_SLEEP_IN_MILSEC));
    status = readInputPinLevel(&pullUp_INPUTPIN);
    ASSERT_EQ(status, GPIO_STATUS_SUCCESS);
    ASSERT_EQ(pullUp_INPUTPIN.level, GPIO_PIN_LEVEL_HIGH);

    pullUp_INPUTPIN.pullUpDown = GPIO_PIN_PUD_PULL_UP;
    status = updateInputPin(&pullUp_INPUTPIN);
    ASSERT_EQ(status, GPIO_STATUS_SUCCESS);

    setOutputPinHigh(&pullUp_OUTPUTPIN);
    std::this_thread::sleep_for(std::chrono::milliseconds(GPIO_SLEEP_IN_MILSEC));
    status = readInputPinLevel(&pullUp_INPUTPIN);
    ASSERT_EQ(status, GPIO_STATUS_SUCCESS);
    ASSERT_EQ(pullUp_INPUTPIN.level, GPIO_PIN_LEVEL_LOW);
    setOutputPinLow(&pullUp_OUTPUTPIN);
    std::this_thread::sleep_for(std::chrono::milliseconds(GPIO_SLEEP_IN_MILSEC));
    status = readInputPinLevel(&pullUp_INPUTPIN);
    ASSERT_EQ(status, GPIO_STATUS_SUCCESS);
    ASSERT_EQ(pullUp_INPUTPIN.level, GPIO_PIN_LEVEL_HIGH);

    closeOutputPin(&pullDown_OUTPUTPIN);
    closeOutputPin(&pullUp_OUTPUTPIN);

    closeInputPin(&pullDown_INPUTPIN);
    ASSERT_EQ(pullDown_INPUTPIN.status, GPIO_PIN_CLOSED);
    status = updateInputPin(&pullDown_INPUTPIN);
    ASSERT_EQ(status, GPIO_STATUS_CONFIG_ERROR);
    status = readInputPinLevel(&pullDown_INPUTPIN);
    ASSERT_EQ(status, GPIO_STATUS_CONFIG_ERROR);

    closeInputPin(&pullUp_INPUTPIN);
    ASSERT_EQ(pullUp_INPUTPIN.status, GPIO_PIN_CLOSED);
    status = updateInputPin(&pullUp_INPUTPIN);
    ASSERT_EQ(status, GPIO_STATUS_CONFIG_ERROR);
    status = readInputPinLevel(&pullUp_INPUTPIN);
    ASSERT_EQ(status, GPIO_STATUS_CONFIG_ERROR);

    shutdownDrivers();

}

static void invokeRising(struct output_pin_t *outputPin) {
    std::this_thread::sleep_for(std::chrono::milliseconds(GPIO_SLEEP_IN_MILSEC / 2));
    setOutputPinHigh(outputPin);
}

static void invokeFalling(struct output_pin_t *outputPin) {
    std::this_thread::sleep_for(std::chrono::milliseconds(GPIO_SLEEP_IN_MILSEC / 2));
    setOutputPinLow(outputPin);
}

TEST(GpioDriverTest, testListenerPin) {

    int status;
    struct output_pin_t outputPin;
    struct listener_pin_t listenerPin;

    outputPin.number = GPIO_LISTENER_OUTPUT;
    listenerPin.number = GPIO_LISTENER_INPUT;
    listenerPin.timeoutInMilSec = GPIO_SLEEP_IN_MILSEC;

    setupDrivers();
    openOutputPin(&outputPin);

    // set pinevent both
    listenerPin.cevent = GPIO_PIN_EVENT_BOTH;
    status = openListenerPin(&listenerPin);
    ASSERT_EQ(status, GPIO_STATUS_SUCCESS);
    ASSERT_GT(listenerPin.reference, 0);
    ASSERT_EQ(listenerPin.status, GPIO_PIN_OPENED);

    status = openListenerPin(&listenerPin);
    ASSERT_EQ(status, GPIO_STATUS_CONFIG_ERROR);

    // no trigger timeout
    status = readListenerPinEvent(&listenerPin);
    ASSERT_EQ(status, GPIO_STATUS_POLL_TIMEOUT_ERROR);

    // trig rising and success
    listenerPin.timeStamp = 0;
    std::thread risingSuccessOnBoth(invokeRising, &outputPin);
    status = readListenerPinEvent(&listenerPin);
    risingSuccessOnBoth.join();
    ASSERT_EQ(status, GPIO_STATUS_SUCCESS);
    ASSERT_EQ(listenerPin.revent, GPIO_PIN_EVENT_RISING);
    ASSERT_GT(listenerPin.timeStamp, 0);

    // trig falling and success
    listenerPin.timeStamp = 0;
    std::thread fallingSuccessOnBoth(invokeFalling, &outputPin);
    status = readListenerPinEvent(&listenerPin);
    fallingSuccessOnBoth.join();
    ASSERT_EQ(status, GPIO_STATUS_SUCCESS);
    ASSERT_EQ(listenerPin.revent, GPIO_PIN_EVENT_FALLING);
    ASSERT_GT(listenerPin.timeStamp, 0);

    // prepare falling fails on rising
    setOutputPinHigh(&outputPin);
    // update event rising success
    listenerPin.cevent = GPIO_PIN_EVENT_RISING;
    status = updateListenerPin(&listenerPin);
    ASSERT_EQ(status, GPIO_STATUS_SUCCESS);

    // trig falling fail timeout on rising
    std::thread fallingFailOnRising(invokeFalling, &outputPin);
    status = readListenerPinEvent(&listenerPin);
    fallingFailOnRising.join();
    ASSERT_EQ(status, GPIO_STATUS_POLL_TIMEOUT_ERROR);

    // trig rising success on rising
    listenerPin.timeStamp = 0;
    std::thread risingSuccessOnRising(invokeRising, &outputPin);
    status = readListenerPinEvent(&listenerPin);
    risingSuccessOnRising.join();
    ASSERT_EQ(status, GPIO_STATUS_SUCCESS);
    ASSERT_EQ(listenerPin.revent, GPIO_PIN_EVENT_RISING);
    ASSERT_GT(listenerPin.timeStamp, 0);

    // prepare rising fails on falling
    setOutputPinLow(&outputPin);
    // update event falling success
    listenerPin.cevent = GPIO_PIN_EVENT_FALLING;
    status = updateListenerPin(&listenerPin);
    ASSERT_EQ(status, GPIO_STATUS_SUCCESS);

    // trig rising fail timeout on falling
    std::thread risingFailOnFalling(invokeRising, &outputPin);
    status = readListenerPinEvent(&listenerPin);
    risingFailOnFalling.join();
    ASSERT_EQ(status, GPIO_STATUS_POLL_TIMEOUT_ERROR);

    // trig falling success on falling
    listenerPin.timeStamp = 0;
    std::thread fallingSuccessOnFalling(invokeFalling, &outputPin);
    status = readListenerPinEvent(&listenerPin);
    fallingSuccessOnFalling.join();
    ASSERT_EQ(status, GPIO_STATUS_SUCCESS);
    ASSERT_EQ(listenerPin.revent, GPIO_PIN_EVENT_FALLING);
    ASSERT_GT(listenerPin.timeStamp, 0);

    closeOutputPin(&outputPin);

    closeListenerPin(&listenerPin);
    ASSERT_EQ(listenerPin.status, GPIO_PIN_CLOSED);

    status = updateListenerPin(&listenerPin);
    ASSERT_EQ(status, GPIO_STATUS_CONFIG_ERROR);

    status = readListenerPinEvent(&listenerPin);
    ASSERT_EQ(status, GPIO_STATUS_CONFIG_ERROR);

    shutdownDrivers();

}


TEST(GpioDriverTest, testAlternatePin) {

    int status;
    struct alternate_pin_t alternatePin;
    alternatePin.number = GPIO_ALTERNATE_SELF;

    setupDrivers();

    alternatePin.function = GPIO_PIN_FUNCTION_ALT0;
    status = openAlternatePin(&alternatePin);
    ASSERT_EQ(status, GPIO_STATUS_SUCCESS);
    ASSERT_EQ(alternatePin.status, GPIO_PIN_OPENED);

    status = openAlternatePin(&alternatePin);
    ASSERT_EQ(status, GPIO_STATUS_CONFIG_ERROR);

    alternatePin.function = GPIO_PIN_FUNCTION_ALT1;
    status = updateAlternatePin(&alternatePin);
    ASSERT_EQ(status, GPIO_STATUS_SUCCESS);

    alternatePin.function = GPIO_PIN_FUNCTION_ALT2;
    status = updateAlternatePin(&alternatePin);
    ASSERT_EQ(status, GPIO_STATUS_SUCCESS);

    alternatePin.function = GPIO_PIN_FUNCTION_ALT3;
    status = updateAlternatePin(&alternatePin);
    ASSERT_EQ(status, GPIO_STATUS_SUCCESS);

    alternatePin.function = GPIO_PIN_FUNCTION_ALT4;
    status = updateAlternatePin(&alternatePin);
    ASSERT_EQ(status, GPIO_STATUS_SUCCESS);

    alternatePin.function = GPIO_PIN_FUNCTION_ALT5;
    status = updateAlternatePin(&alternatePin);
    ASSERT_EQ(status, GPIO_STATUS_SUCCESS);

    closeAlternatePin(&alternatePin);
    ASSERT_EQ(alternatePin.status, GPIO_PIN_CLOSED);

    status = updateAlternatePin(&alternatePin);
    ASSERT_EQ(status, GPIO_STATUS_CONFIG_ERROR);

    shutdownDrivers();

}