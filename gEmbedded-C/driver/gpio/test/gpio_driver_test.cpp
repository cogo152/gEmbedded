//
// Created by sondahi on 15.01.23.
//

#include <chrono>
#include <thread>

#include "common_test.h"
#include "gpio_test.h"

#include "driver_context.h"

TEST(GpioDriverTest, testOutputPin) {

    int status;

    setupDrivers();

    status = openOutputPin(&outputPin_SELF);
    ASSERT_EQ(status, GPIO_STATUS_SUCCESS);
    ASSERT_EQ(outputPin_SELF.reference, 0b1 << ((outputPin_SELF.number % 32) * 1));
    ASSERT_EQ(outputPin_SELF.status, GPIO_PIN_OPENED);

    status = openOutputPin(&outputPin_SELF);
    ASSERT_EQ(status, GPIO_STATUS_CONFIG_ERROR);

    status = setOutputPinHigh(&outputPin_SELF);
    ASSERT_EQ(status, GPIO_STATUS_SUCCESS);
    status = readOutputPinLevel(&outputPin_SELF);
    ASSERT_EQ(status, GPIO_STATUS_SUCCESS);
    ASSERT_EQ(outputPin_SELF.level, GPIO_PIN_LEVEL_HIGH);

    status = setOutputPinLow(&outputPin_SELF);
    ASSERT_EQ(status, GPIO_STATUS_SUCCESS);
    status = readOutputPinLevel(&outputPin_SELF);
    ASSERT_EQ(status, GPIO_STATUS_SUCCESS);
    ASSERT_EQ(outputPin_SELF.level, GPIO_PIN_LEVEL_LOW);

    closeOutputPin(&outputPin_SELF);
    ASSERT_EQ(outputPin_SELF.status, GPIO_PIN_CLOSED);

    status = setOutputPinHigh(&outputPin_SELF);
    ASSERT_EQ(status, GPIO_STATUS_CONFIG_ERROR);
    status = readOutputPinLevel(&outputPin_SELF);
    ASSERT_EQ(status, GPIO_STATUS_CONFIG_ERROR);

    shutdownDrivers();

}

TEST(GpioDriverTest, testInputPin) {
    int status;

    setupDrivers();
    openOutputPin(&outputPin_PULLDOWN);
    openOutputPin(&outputPin_PULLUP);

    inputPin_PULLDOWN.pullUpDown = GPIO_PIN_PUD_NO_RESISTOR;
    status = openInputPin(&inputPin_PULLDOWN);
    ASSERT_EQ(status, GPIO_STATUS_SUCCESS);
    ASSERT_EQ(inputPin_PULLDOWN.reference, 0b1 << ((inputPin_PULLDOWN.number % 32) * 1));
    ASSERT_EQ(inputPin_PULLDOWN.status, GPIO_PIN_OPENED);

    status = openInputPin(&inputPin_PULLDOWN);
    ASSERT_EQ(status, GPIO_STATUS_CONFIG_ERROR);

    setOutputPinHigh(&outputPin_PULLDOWN);
    std::this_thread::sleep_for(std::chrono::milliseconds(GPIO_SLEEP_IN_MILSEC));
    status = readInputPinLevel(&inputPin_PULLDOWN);
    ASSERT_EQ(status, GPIO_STATUS_SUCCESS);
    ASSERT_EQ(inputPin_PULLDOWN.level, GPIO_PIN_LEVEL_HIGH);
    setOutputPinLow(&outputPin_PULLDOWN);
    std::this_thread::sleep_for(std::chrono::milliseconds(GPIO_SLEEP_IN_MILSEC));
    status = readInputPinLevel(&inputPin_PULLDOWN);
    ASSERT_EQ(status, GPIO_STATUS_SUCCESS);
    ASSERT_EQ(inputPin_PULLDOWN.level, GPIO_PIN_LEVEL_LOW);

    inputPin_PULLDOWN.pullUpDown = GPIO_PIN_PUD_PULL_DOWN;
    status = updateInputPin(&inputPin_PULLDOWN);
    ASSERT_EQ(status, GPIO_STATUS_SUCCESS);

    setOutputPinHigh(&outputPin_PULLDOWN);
    std::this_thread::sleep_for(std::chrono::milliseconds(GPIO_SLEEP_IN_MILSEC));
    status = readInputPinLevel(&inputPin_PULLDOWN);
    ASSERT_EQ(status, GPIO_STATUS_SUCCESS);
    ASSERT_EQ(inputPin_PULLDOWN.level, GPIO_PIN_LEVEL_HIGH);
    setOutputPinLow(&outputPin_PULLDOWN);
    std::this_thread::sleep_for(std::chrono::milliseconds(GPIO_SLEEP_IN_MILSEC));
    status = readInputPinLevel(&inputPin_PULLDOWN);
    ASSERT_EQ(status, GPIO_STATUS_SUCCESS);
    ASSERT_EQ(inputPin_PULLDOWN.level, GPIO_PIN_LEVEL_LOW);

    inputPin_PULLUP.pullUpDown = GPIO_PIN_PUD_NO_RESISTOR;
    status = openInputPin(&inputPin_PULLUP);
    ASSERT_EQ(status, GPIO_STATUS_SUCCESS);
    ASSERT_EQ(inputPin_PULLUP.reference, 0b1 << ((inputPin_PULLUP.number % 32) * 1));
    ASSERT_EQ(inputPin_PULLUP.status, GPIO_PIN_OPENED);

    status = openInputPin(&inputPin_PULLUP);
    ASSERT_EQ(status, GPIO_STATUS_CONFIG_ERROR);

    setOutputPinHigh(&outputPin_PULLUP);
    std::this_thread::sleep_for(std::chrono::milliseconds(GPIO_SLEEP_IN_MILSEC));
    status = readInputPinLevel(&inputPin_PULLUP);
    ASSERT_EQ(status, GPIO_STATUS_SUCCESS);
    ASSERT_EQ(inputPin_PULLUP.level, GPIO_PIN_LEVEL_LOW);
    setOutputPinLow(&outputPin_PULLUP);
    std::this_thread::sleep_for(std::chrono::milliseconds(GPIO_SLEEP_IN_MILSEC));
    status = readInputPinLevel(&inputPin_PULLUP);
    ASSERT_EQ(status, GPIO_STATUS_SUCCESS);
    ASSERT_EQ(inputPin_PULLUP.level, GPIO_PIN_LEVEL_HIGH);

    inputPin_PULLUP.pullUpDown = GPIO_PIN_PUD_PULL_UP;
    status = updateInputPin(&inputPin_PULLUP);
    ASSERT_EQ(status, GPIO_STATUS_SUCCESS);

    setOutputPinHigh(&outputPin_PULLUP);
    std::this_thread::sleep_for(std::chrono::milliseconds(GPIO_SLEEP_IN_MILSEC));
    status = readInputPinLevel(&inputPin_PULLUP);
    ASSERT_EQ(status, GPIO_STATUS_SUCCESS);
    ASSERT_EQ(inputPin_PULLUP.level, GPIO_PIN_LEVEL_LOW);
    setOutputPinLow(&outputPin_PULLUP);
    std::this_thread::sleep_for(std::chrono::milliseconds(GPIO_SLEEP_IN_MILSEC));
    status = readInputPinLevel(&inputPin_PULLUP);
    ASSERT_EQ(status, GPIO_STATUS_SUCCESS);
    ASSERT_EQ(inputPin_PULLUP.level, GPIO_PIN_LEVEL_HIGH);

    closeOutputPin(&outputPin_PULLDOWN);
    closeOutputPin(&outputPin_PULLUP);

    closeInputPin(&inputPin_PULLDOWN);
    ASSERT_EQ(inputPin_PULLDOWN.status, GPIO_PIN_CLOSED);
    status = updateInputPin(&inputPin_PULLDOWN);
    ASSERT_EQ(status, GPIO_STATUS_CONFIG_ERROR);
    status = readInputPinLevel(&inputPin_PULLDOWN);
    ASSERT_EQ(status, GPIO_STATUS_CONFIG_ERROR);

    closeInputPin(&inputPin_PULLUP);
    ASSERT_EQ(inputPin_PULLUP.status, GPIO_PIN_CLOSED);
    status = updateInputPin(&inputPin_PULLUP);
    ASSERT_EQ(status, GPIO_STATUS_CONFIG_ERROR);
    status = readInputPinLevel(&inputPin_PULLUP);
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

    setupDrivers();
    openOutputPin(&outputPin_LISTENER);

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
    std::thread risingSuccessOnBoth(invokeRising, &outputPin_LISTENER);
    status = readListenerPinEvent(&listenerPin);
    risingSuccessOnBoth.join();
    ASSERT_EQ(status, GPIO_STATUS_SUCCESS);
    ASSERT_EQ(listenerPin.revent, GPIO_PIN_EVENT_RISING);
    ASSERT_GT(listenerPin.timeStamp, 0);

    // trig falling and success
    listenerPin.timeStamp = 0;
    std::thread fallingSuccessOnBoth(invokeFalling, &outputPin_LISTENER);
    status = readListenerPinEvent(&listenerPin);
    fallingSuccessOnBoth.join();
    ASSERT_EQ(status, GPIO_STATUS_SUCCESS);
    ASSERT_EQ(listenerPin.revent, GPIO_PIN_EVENT_FALLING);
    ASSERT_GT(listenerPin.timeStamp, 0);

    // prepare falling fails on rising
    setOutputPinHigh(&outputPin_LISTENER);
    // update event rising success
    listenerPin.cevent = GPIO_PIN_EVENT_RISING;
    status = updateListenerPin(&listenerPin);
    ASSERT_EQ(status, GPIO_STATUS_SUCCESS);

    // trig falling fail timeout on rising
    std::thread fallingFailOnRising(invokeFalling, &outputPin_LISTENER);
    status = readListenerPinEvent(&listenerPin);
    fallingFailOnRising.join();
    ASSERT_EQ(status, GPIO_STATUS_POLL_TIMEOUT_ERROR);

    // trig rising success on rising
    listenerPin.timeStamp = 0;
    std::thread risingSuccessOnRising(invokeRising, &outputPin_LISTENER);
    status = readListenerPinEvent(&listenerPin);
    risingSuccessOnRising.join();
    ASSERT_EQ(status, GPIO_STATUS_SUCCESS);
    ASSERT_EQ(listenerPin.revent, GPIO_PIN_EVENT_RISING);
    ASSERT_GT(listenerPin.timeStamp, 0);

    // prepare rising fails on falling
    setOutputPinLow(&outputPin_LISTENER);
    // update event falling success
    listenerPin.cevent = GPIO_PIN_EVENT_FALLING;
    status = updateListenerPin(&listenerPin);
    ASSERT_EQ(status, GPIO_STATUS_SUCCESS);

    // trig rising fail timeout on falling
    std::thread risingFailOnFalling(invokeRising, &outputPin_LISTENER);
    status = readListenerPinEvent(&listenerPin);
    risingFailOnFalling.join();
    ASSERT_EQ(status, GPIO_STATUS_POLL_TIMEOUT_ERROR);

    // trig falling success on falling
    listenerPin.timeStamp = 0;
    std::thread fallingSuccessOnFalling(invokeFalling, &outputPin_LISTENER);
    status = readListenerPinEvent(&listenerPin);
    fallingSuccessOnFalling.join();
    ASSERT_EQ(status, GPIO_STATUS_SUCCESS);
    ASSERT_EQ(listenerPin.revent, GPIO_PIN_EVENT_FALLING);
    ASSERT_GT(listenerPin.timeStamp, 0);

    closeOutputPin(&outputPin_LISTENER);

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