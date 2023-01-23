//
// Created by sondahi on 15.01.23.
//

#include <chrono>
#include <thread>

#include "pin_test.h"

static int openPinDrivers() {

    int status;

    status = openPinConfigDriver();
    if (status != PIN_CONFIG_EXCEPTION_SUCCESS) {
        return status;
    }

    status = openPinIODriver();
    if (status != PIN_IO_EXCEPTION_SUCCESS) {
        return status;
    }

    return 0;

}

static int closePinDrivers() {

    int status;

    status = closePinConfigDriver();
    if (status != PIN_CONFIG_EXCEPTION_SUCCESS) {
        return status;
    }

    status = closePinIODriver();
    if (status != PIN_IO_EXCEPTION_SUCCESS) {
        return status;
    }

    return 0;

}

TEST(PinDriverTest, testOpenCloseDrivers) {

    int status;
    status = openPinDrivers();
    ASSERT_EQ(status, 0);

    status = closePinDrivers();
    ASSERT_EQ(status, 0);

}

TEST(GpioDriverTest, testOutputPin) {

    int status;

    openPinDrivers();

    status = openOutputPin(&outputPin_SELF);
    ASSERT_EQ(status, PIN_CONFIG_EXCEPTION_SUCCESS);
    ASSERT_EQ(outputPin_SELF.reference, 1 << ((outputPin_SELF.number % 32) * 1));
    ASSERT_EQ(outputPin_SELF.status, PIN_CONFIG_STATUS_OPENED);

    setOutputPinHigh(&outputPin_SELF);
    readOutputPinLevel(&outputPin_SELF);
    ASSERT_EQ(outputPin_SELF.level, PIN_IO_LEVEL_HIGH);

    setOutputPinLow(&outputPin_SELF);
    readOutputPinLevel(&outputPin_SELF);
    ASSERT_EQ(outputPin_SELF.level, PIN_IO_LEVEL_LOW);

    closeOutputPin(&outputPin_SELF);
    ASSERT_EQ(outputPin_SELF.status, PIN_CONFIG_STATUS_CLOSED);

    closePinDrivers();

}

TEST(GpioDriverTest, testInputPin) {
    int status;

    openPinDrivers();
    openOutputPin(&outputPin_PULLDOWN);
    openOutputPin(&outputPin_PULLUP);

    inputPin_PULLDOWN.pullUpDown = PIN_CONFIG_PUD_NO_RESISTOR;
    status = openInputPin(&inputPin_PULLDOWN);
    ASSERT_EQ(status, PIN_CONFIG_EXCEPTION_SUCCESS);
    ASSERT_EQ(inputPin_PULLDOWN.reference, 1 << ((inputPin_PULLDOWN.number % 32) * 1));
    ASSERT_EQ(inputPin_PULLDOWN.status, PIN_CONFIG_STATUS_OPENED);

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
    ASSERT_EQ(status, PIN_CONFIG_EXCEPTION_SUCCESS);

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
    ASSERT_EQ(status, PIN_CONFIG_EXCEPTION_SUCCESS);
    ASSERT_EQ(inputPin_PULLUP.reference, 1 << ((inputPin_PULLUP.number % 32) * 1));
    ASSERT_EQ(inputPin_PULLUP.status, PIN_CONFIG_STATUS_OPENED);

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
    ASSERT_EQ(status, PIN_CONFIG_EXCEPTION_SUCCESS);

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
    ASSERT_EQ(inputPin_PULLDOWN.status, PIN_CONFIG_STATUS_CLOSED);
    closeInputPin(&inputPin_PULLUP);
    ASSERT_EQ(inputPin_PULLUP.status, PIN_CONFIG_STATUS_CLOSED);

    closePinDrivers();

}

static void invokeRising(struct output_pin_t *outputPin) {
    std::this_thread::sleep_for(std::chrono::milliseconds(PIN_SLEEP_IN_MILSEC / 2));
    setOutputPinHigh(outputPin);
}

static void invokeFalling(struct output_pin_t *outputPin) {
    std::this_thread::sleep_for(std::chrono::milliseconds(PIN_SLEEP_IN_MILSEC / 2));
    setOutputPinLow(outputPin);
}

TEST(GpioDriverTest, testListenerPin) {

    int status;

    openPinDrivers();
    openOutputPin(&outputPin_LISTENER);

    // set pinevent both
    listenerPin.cevent = PIN_CONFIG_EVENT_BOTH;
    status = openListenerPin(&listenerPin);
    ASSERT_EQ(status, PIN_CONFIG_EXCEPTION_SUCCESS);
    ASSERT_GT(listenerPin.reference, 0);
    ASSERT_EQ(listenerPin.status, PIN_CONFIG_STATUS_OPENED);

    // no trigger timeout
    status = readListenerPinEvent(&listenerPin);
    ASSERT_EQ(status, PIN_IO_EXCEPTION_POLL_TIMEOUT_ERROR);

    // trig rising and success
    listenerPin.timeStamp = 0;
    std::thread risingSuccessOnBoth(invokeRising, &outputPin_LISTENER);
    status = readListenerPinEvent(&listenerPin);
    risingSuccessOnBoth.join();
    ASSERT_EQ(status, PIN_IO_EXCEPTION_SUCCESS);
    ASSERT_EQ(listenerPin.revent, PIN_IO_EVENT_RISING);
    ASSERT_GT(listenerPin.timeStamp, 0);

    // trig falling and success
    listenerPin.timeStamp = 0;
    std::thread fallingSuccessOnBoth(invokeFalling, &outputPin_LISTENER);
    status = readListenerPinEvent(&listenerPin);
    fallingSuccessOnBoth.join();
    ASSERT_EQ(status, PIN_IO_EXCEPTION_SUCCESS);
    ASSERT_EQ(listenerPin.revent, PIN_IO_EVENT_FALLING);
    ASSERT_GT(listenerPin.timeStamp, 0);

    // prepare falling fails on rising
    setOutputPinHigh(&outputPin_LISTENER);
    // update event rising success
    listenerPin.cevent = PIN_CONFIG_EVENT_RISING;
    status = updateListenerPin(&listenerPin);
    ASSERT_EQ(status, PIN_CONFIG_EXCEPTION_SUCCESS);

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
    ASSERT_EQ(status, PIN_IO_EXCEPTION_SUCCESS);
    ASSERT_EQ(listenerPin.revent, PIN_IO_EVENT_RISING);
    ASSERT_GT(listenerPin.timeStamp, 0);

    // prepare rising fails on falling
    setOutputPinLow(&outputPin_LISTENER);
    // update event falling success
    listenerPin.cevent = PIN_CONFIG_EVENT_FALLING;
    status = updateListenerPin(&listenerPin);
    ASSERT_EQ(status, PIN_CONFIG_EXCEPTION_SUCCESS);

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
    ASSERT_EQ(status, PIN_IO_EXCEPTION_SUCCESS);
    ASSERT_EQ(listenerPin.revent, PIN_IO_EVENT_FALLING);
    ASSERT_GT(listenerPin.timeStamp, 0);

    closeOutputPin(&outputPin_LISTENER);

    closeListenerPin(&listenerPin);
    ASSERT_EQ(listenerPin.status, PIN_CONFIG_STATUS_CLOSED);

    closePinDrivers();

}


TEST(GpioDriverTest, testAlternatePin) {

    int status;

    openPinDrivers();

    alternatePin.function = PIN_CONFIG_FUNCTION_ALT0;
    status = openAlternatePin(&alternatePin);
    ASSERT_EQ(status, PIN_CONFIG_EXCEPTION_SUCCESS);
    ASSERT_EQ(alternatePin.status, PIN_CONFIG_STATUS_OPENED);

    alternatePin.function = PIN_CONFIG_FUNCTION_ALT1;
    status = updateAlternatePin(&alternatePin);
    ASSERT_EQ(status, PIN_CONFIG_EXCEPTION_SUCCESS);

    alternatePin.function = PIN_CONFIG_FUNCTION_ALT2;
    status = updateAlternatePin(&alternatePin);
    ASSERT_EQ(status, PIN_CONFIG_EXCEPTION_SUCCESS);

    alternatePin.function = PIN_CONFIG_FUNCTION_ALT3;
    status = updateAlternatePin(&alternatePin);
    ASSERT_EQ(status, PIN_CONFIG_EXCEPTION_SUCCESS);

    alternatePin.function = PIN_CONFIG_FUNCTION_ALT4;
    status = updateAlternatePin(&alternatePin);
    ASSERT_EQ(status, PIN_CONFIG_EXCEPTION_SUCCESS);

    alternatePin.function = PIN_CONFIG_FUNCTION_ALT5;
    status = updateAlternatePin(&alternatePin);
    ASSERT_EQ(status, PIN_CONFIG_EXCEPTION_SUCCESS);

    closeAlternatePin(&alternatePin);
    ASSERT_EQ(alternatePin.status, PIN_CONFIG_STATUS_CLOSED);


    closePinDrivers();

}