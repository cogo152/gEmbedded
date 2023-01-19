//
// Created by sondahi on 15.01.23.
//

#include <chrono>
#include <thread>

#include "common_test.h"
#include "gpio_test.h"

#include "gpio_driver.h"

TEST(GpioDriverTest, testInputPin) {

    int status;
    struct output_pin_t outputPin;
    outputPin.number = GPIO_OUTPUT_PIN_FOR_LISTENER;

    struct input_pin_t inputPin;
    inputPin.number = GPIO_LISTENER_PIN;

    setupGpioDriver();
    openOutputPin(&outputPin);

    inputPin.reference = 0;
    inputPin.pullUpDown = GPIO_PIN_PUD_NO_RESISTOR;
    status = openInputPin(&inputPin);
    EXPECT_EQ(status, GPIO_STATUS_SUCCESS);
    EXPECT_GT(inputPin.reference, 0);

    readInputPinLevel(&inputPin);
    EXPECT_EQ(inputPin.level, GPIO_PIN_LEVEL_LOW);
    setOutputPinHigh(&outputPin);
    std::this_thread::sleep_for(std::chrono::milliseconds(GPIO_SLEEP_IN_MILSEC));
    readInputPinLevel(&inputPin);
    EXPECT_EQ(inputPin.level, GPIO_PIN_LEVEL_HIGH);


    //setOutputPinLow(&outputPin);

    inputPin.pullUpDown = GPIO_PIN_PUD_PULL_UP;
    status = updateInputPin(&inputPin);
    EXPECT_EQ(status, GPIO_STATUS_SUCCESS);
    setOutputPinHigh(&outputPin);
    readInputPinLevel(&inputPin);
    EXPECT_EQ(inputPin.level, GPIO_PIN_LEVEL_HIGH);
    setOutputPinLow(&outputPin);
    EXPECT_EQ(inputPin.level, GPIO_PIN_LEVEL_LOW);

    inputPin.pullUpDown = GPIO_PIN_PUD_PULL_DOWN;
    status = updateInputPin(&inputPin);
    EXPECT_EQ(status, GPIO_STATUS_SUCCESS);
    setOutputPinHigh(&outputPin);
    readInputPinLevel(&inputPin);
    EXPECT_EQ(inputPin.level, GPIO_PIN_LEVEL_HIGH);
    setOutputPinLow(&outputPin);
    EXPECT_EQ(inputPin.level, GPIO_PIN_LEVEL_LOW);

    closeOutputPin(&outputPin);

    closeInputPin(&inputPin);
    EXPECT_EQ(inputPin.reference, 0);

    shutdownGpioDriver();

}

/*

TEST(GpioDriverTest, testSetupShutdownGpio) {

    int status;

    status = setupGpioDriver();
    ASSERT_EQ(status, GPIO_STATUS_SUCCESS);

    status = shutdownGpioDriver();
    ASSERT_EQ(status, GPIO_STATUS_SUCCESS);

}

TEST(GpioDriverTest, testOutputPin) {

    int status;
    struct output_pin_t outputPin;
    outputPin.number = GPIO_OUTPUT_PIN_SELF;
    outputPin.reference = 0;

    setupGpioDriver();

    status = openOutputPin(&outputPin);
    ASSERT_EQ(status, GPIO_STATUS_SUCCESS);
    ASSERT_NE(outputPin.reference, 0);

    setOutputPinHigh(&outputPin);
    readOutputPinLevel(&outputPin);
    ASSERT_EQ(outputPin.level, GPIO_PIN_LEVEL_HIGH);

    setOutputPinLow(&outputPin);
    readOutputPinLevel(&outputPin);
    ASSERT_EQ(outputPin.level, GPIO_PIN_LEVEL_LOW);

    closeOutputPin(&outputPin);
    ASSERT_EQ(outputPin.reference, 0);

    shutdownGpioDriver();

}


static void invokeRising(struct output_pin_t *outputPin) {
    std::this_thread::sleep_for(std::chrono::milliseconds(GPIO_LISTENER_PIN_TIMEOUT_MILSEC / 2));
    setOutputPinHigh(outputPin);
}

static void invokeFalling(struct output_pin_t *outputPin) {
    std::this_thread::sleep_for(std::chrono::milliseconds(GPIO_LISTENER_PIN_TIMEOUT_MILSEC / 2));
    setOutputPinLow(outputPin);
}

TEST(GpioDriverTest, testListenerPin) {

    int status;
    struct output_pin_t outputPin;
    outputPin.number = GPIO_OUTPUT_PIN_FOR_LISTENER;

    struct listener_pin_t listenerPin;
    listenerPin.number = GPIO_LISTENER_PIN;

    setupGpioDriver();
    openOutputPin(&outputPin);

    // timeout < 0
    listenerPin.timeoutInMilSec = -1;
    listenerPin.reference = 1;
    status = openListenerPin(&listenerPin);
    ASSERT_EQ(status, GPIO_STATUS_CONFIG_ERROR);
    ASSERT_EQ(listenerPin.reference, 0);

    // timeout = 0
    listenerPin.timeoutInMilSec = -1;
    listenerPin.reference = 1;
    status = openListenerPin(&listenerPin);
    ASSERT_EQ(status, GPIO_STATUS_CONFIG_ERROR);
    ASSERT_EQ(listenerPin.reference, 0);

    // set pinevent both
    listenerPin.timeoutInMilSec = GPIO_LISTENER_PIN_TIMEOUT_MILSEC;
    listenerPin.reference = 0;
    listenerPin.cevent = GPIO_PIN_EVENT_BOTH;
    status = openListenerPin(&listenerPin);
    ASSERT_EQ(status, GPIO_STATUS_SUCCESS);
    ASSERT_NE(listenerPin.reference, 0);

    // no trigger timeout
    listenerPin.timeStamp = 1;
    status = readListenerPinEvent(&listenerPin);
    ASSERT_EQ(status, GPIO_STATUS_POLL_TIMEOUT_ERROR);
    ASSERT_EQ(listenerPin.timeStamp, 0);

    // trig rising and success
    listenerPin.timeStamp = 0;
    std::thread risingSuccessBoth(invokeRising, &outputPin);
    status = readListenerPinEvent(&listenerPin);
    risingSuccessBoth.join();
    ASSERT_EQ(status, GPIO_STATUS_SUCCESS);
    ASSERT_EQ(listenerPin.revent, GPIO_PIN_EVENT_RISING);
    ASSERT_GT(listenerPin.timeStamp, 0);

    // trig falling and success
    listenerPin.timeStamp = 0;
    std::thread fallingSuccessBoth(invokeFalling, &outputPin);
    status = readListenerPinEvent(&listenerPin);
    fallingSuccessBoth.join();
    ASSERT_EQ(status, GPIO_STATUS_SUCCESS);
    ASSERT_EQ(listenerPin.revent, GPIO_PIN_EVENT_FALLING);
    ASSERT_GT(listenerPin.timeStamp, 0);

    // prepare falling fails on rising
    setOutputPinHigh(&outputPin);

    // update event rising success
    listenerPin.cevent = GPIO_PIN_EVENT_RISING;
    status = updateListenerPin(&listenerPin);
    ASSERT_EQ(status, GPIO_STATUS_SUCCESS);
    ASSERT_NE(listenerPin.reference, 0);

    // trig falling fail timeout on rising
    listenerPin.timeStamp = 1;
    std::thread fallingFailRising(invokeFalling, &outputPin);
    status = readListenerPinEvent(&listenerPin);
    fallingFailRising.join();
    ASSERT_EQ(status, GPIO_STATUS_POLL_TIMEOUT_ERROR);
    ASSERT_EQ(listenerPin.timeStamp, 0);

    // trig rising success on rising
    listenerPin.timeStamp = 0;
    std::thread risingSuccessRising(invokeRising, &outputPin);
    status = readListenerPinEvent(&listenerPin);
    risingSuccessRising.join();
    ASSERT_EQ(status, GPIO_STATUS_SUCCESS);
    ASSERT_EQ(listenerPin.revent, GPIO_PIN_EVENT_RISING);
    ASSERT_GT(listenerPin.timeStamp, 0);

    // prepare rising fails on falling
    setOutputPinHigh(&outputPin);

    // update event falling success
    listenerPin.cevent = GPIO_PIN_EVENT_FALLING;
    status = updateListenerPin(&listenerPin);
    ASSERT_EQ(status, GPIO_STATUS_SUCCESS);
    ASSERT_NE(listenerPin.reference, 0);

    // trig falling fail timeout on rising
    listenerPin.timeStamp = 1;
    std::thread risingFailFalling(invokeRising, &outputPin);
    status = readListenerPinEvent(&listenerPin);
    risingFailFalling.join();
    ASSERT_EQ(status, GPIO_STATUS_POLL_TIMEOUT_ERROR);
    ASSERT_EQ(listenerPin.timeStamp, 0);

    // trig falling success on falling
    listenerPin.timeStamp = 0;
    std::thread fallingSuccessFalling(invokeFalling, &outputPin);
    status = readListenerPinEvent(&listenerPin);
    fallingSuccessFalling.join();
    ASSERT_EQ(status, GPIO_STATUS_SUCCESS);
    ASSERT_EQ(listenerPin.revent, GPIO_PIN_EVENT_FALLING);
    ASSERT_GT(listenerPin.timeStamp, 0);

    closeOutputPin(&outputPin);

    closeListenerPin(&listenerPin);
    ASSERT_EQ(listenerPin.reference, 0);

    shutdownGpioDriver();

}

 */