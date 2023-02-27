//
// Created by sondahi on 26.02.23.
//

#include "gtest/gtest.h"
#include "pin_test.h"

#include "pin_controller.h"

extern "C" {
#include "peripheral.h"
}

TEST(PinControllerTest, testInitDestroyPinController) {

    PIN_CONTROLLER_ERROR error;

    error = pinControllerInit();
    ASSERT_EQ(error, PIN_CONTROLLER_ERROR_NO);

    error = pinControllerDestroy();
    ASSERT_EQ(error, PIN_CONTROLLER_ERROR_NO);

}

TEST(PinControllerTest, testOutputPinError) {

    PIN_CONTROLLER_ERROR error;

    uint8_t pinNumber = PIN_NUMBER_INVALID;
    uint32_t ioReference = 0;

    pinControllerInit();

    error = outputPinOpen(pinNumber, &ioReference);
    ASSERT_EQ(error, PIN_CONTROLLER_ERROR_PIN_NUMBER);
    ASSERT_EQ(ioReference, 0);

    pinNumber = PIN_NUMBER_VALID;
    error = outputPinOpen(pinNumber, &ioReference);
    ASSERT_EQ(error, PIN_CONTROLLER_ERROR_NO);
    ASSERT_GT(ioReference, 0);

    error = outputPinClose(pinNumber);
    ASSERT_EQ(error, PIN_CONTROLLER_ERROR_NO);

    pinControllerDestroy();

}

TEST(PinControllerTest, testOutputPinWriteRead) {

    PIN_CONTROLLER_ERROR error;

    uint8_t pinNumber = PIN_NUMBER_SELF;
    uint32_t ioReference;
    int pinLevel;

    pinControllerInit();

    error = outputPinOpen(pinNumber, &ioReference);
    ASSERT_EQ(error, PIN_CONTROLLER_ERROR_NO);

    outputPinWrite(ioReference);
    pinLevel = outputPinRead(ioReference);
    ASSERT_EQ(pinLevel, PIN_CONTROLLER_PIN_LEVEL_HIGH);

    error = outputPinClose(pinNumber);
    ASSERT_EQ(error, PIN_CONTROLLER_ERROR_NO);

    pinControllerDestroy();

}

TEST(PinControllerTest, testOutputPinClearRead) {

    PIN_CONTROLLER_ERROR error;

    uint8_t pinNumber = PIN_NUMBER_SELF;
    uint32_t ioReference;
    int pinLevel;

    pinControllerInit();

    error = outputPinOpen(pinNumber, &ioReference);
    ASSERT_EQ(error, PIN_CONTROLLER_ERROR_NO);

    outputPinClear(ioReference);
    pinLevel = outputPinRead(ioReference);
    ASSERT_EQ(pinLevel, PIN_CONTROLLER_PIN_LEVEL_LOW);

    error = outputPinClose(pinNumber);
    ASSERT_EQ(error, PIN_CONTROLLER_ERROR_NO);

    pinControllerDestroy();

}

TEST(PinControllerTest, testInputPinError) {

    PIN_CONTROLLER_ERROR error;

    uint8_t pinNumber = PIN_NUMBER_INVALID;
    uint8_t pinPullUpDown = PIN_PULLUPDOWN_INVALID;
    uint32_t ioReference = 0;

    pinControllerInit();

    error = inputPinOpen(pinNumber, pinPullUpDown, &ioReference);
    ASSERT_EQ(error, PIN_CONTROLLER_ERROR_PIN_NUMBER);
    ASSERT_EQ(ioReference, 0);

    pinNumber = PIN_NUMBER_VALID;
    error = inputPinOpen(pinNumber, pinPullUpDown, &ioReference);
    ASSERT_EQ(error, PIN_CONTROLLER_ERROR_PIN_PULLUPDOWN);
    ASSERT_EQ(ioReference, 0);

    pinPullUpDown = PIN_PULLUPDOWN_VALID;
    error = inputPinOpen(pinNumber, pinPullUpDown, &ioReference);
    ASSERT_EQ(error, PIN_CONTROLLER_ERROR_NO);
    ASSERT_GT(ioReference, 0);

    error = inputPinClose(pinNumber);
    ASSERT_EQ(error, PIN_CONTROLLER_ERROR_NO);

    pinControllerDestroy();

}

TEST(PinControllerTest, testInputPinNoResistor) {

    PIN_CONTROLLER_ERROR error;

    const uint8_t outputPin_PULLDOWN = PIN_NUMBER_OUTPUT_PULLDOWN;
    uint32_t outputPin_PULLDOWN_ioReference;
    const uint8_t inputPin_PULLDOWN = PIN_NUMBER_INPUT_PULLDOWN;
    const uint8_t inputPin_PULLDOWN_pinPullUpDown = PIN_CONFIG_PUD_NO_RESISTOR;
    uint32_t inputPin_PULLDOWN_ioReference;

    const uint8_t outputPin_PULLUP = PIN_NUMBER_OUTPUT_PULLUP;
    uint32_t outputPin_PULLUP_ioReference;
    const uint8_t inputPin_PULLUP = PIN_NUMBER_INPUT_PULLUP;
    const uint8_t inputPin_PULLUP_pinPullUpDown = PIN_CONFIG_PUD_NO_RESISTOR;
    uint32_t inputPin_PULLUP_ioReference;

    int pinLevel;

    pinControllerInit();

    // Test pull-down

    error = outputPinOpen(outputPin_PULLDOWN, &outputPin_PULLDOWN_ioReference);
    ASSERT_EQ(error, PIN_CONTROLLER_ERROR_NO);
    error = inputPinOpen(inputPin_PULLDOWN, inputPin_PULLDOWN_pinPullUpDown, &inputPin_PULLDOWN_ioReference);
    ASSERT_EQ(error, PIN_CONTROLLER_ERROR_NO);

    outputPinWrite(outputPin_PULLDOWN_ioReference);
    std::this_thread::sleep_for(std::chrono::milliseconds(PIN_SLEEP_IN_MILSEC));
    pinLevel = inputPinRead(inputPin_PULLDOWN_ioReference);
    ASSERT_EQ(pinLevel, PIN_CONTROLLER_PIN_LEVEL_HIGH);

    outputPinClear(outputPin_PULLDOWN_ioReference);
    std::this_thread::sleep_for(std::chrono::milliseconds(PIN_SLEEP_IN_MILSEC));
    pinLevel = inputPinRead(inputPin_PULLDOWN_ioReference);
    ASSERT_EQ(pinLevel, PIN_CONTROLLER_PIN_LEVEL_LOW);

    error = outputPinClose(outputPin_PULLDOWN);
    ASSERT_EQ(error, PIN_CONTROLLER_ERROR_NO);
    error = inputPinClose(inputPin_PULLDOWN);
    ASSERT_EQ(error, PIN_CONTROLLER_ERROR_NO);

    // Test pull-up

    error = outputPinOpen(outputPin_PULLUP, &outputPin_PULLUP_ioReference);
    ASSERT_EQ(error, PIN_CONTROLLER_ERROR_NO);
    error = inputPinOpen(inputPin_PULLUP, inputPin_PULLUP_pinPullUpDown, &inputPin_PULLUP_ioReference);
    ASSERT_EQ(error, PIN_CONTROLLER_ERROR_NO);

    outputPinWrite(outputPin_PULLUP_ioReference);
    std::this_thread::sleep_for(std::chrono::milliseconds(PIN_SLEEP_IN_MILSEC));
    pinLevel = inputPinRead(inputPin_PULLUP_ioReference);
    ASSERT_EQ(pinLevel, PIN_CONTROLLER_PIN_LEVEL_LOW);

    outputPinClear(outputPin_PULLUP_ioReference);
    std::this_thread::sleep_for(std::chrono::milliseconds(PIN_SLEEP_IN_MILSEC));
    pinLevel = inputPinRead(inputPin_PULLUP_ioReference);
    ASSERT_EQ(pinLevel, PIN_CONTROLLER_PIN_LEVEL_HIGH);

    error = outputPinClose(outputPin_PULLUP);
    ASSERT_EQ(error, PIN_CONTROLLER_ERROR_NO);
    error = inputPinClose(inputPin_PULLUP);
    ASSERT_EQ(error, PIN_CONTROLLER_ERROR_NO);

    pinControllerDestroy();

}

TEST(PinControllerTest, testInputPinPullDown) {

    PIN_CONTROLLER_ERROR error;

    const uint8_t outputPin_PULLDOWN = PIN_NUMBER_OUTPUT_PULLDOWN;
    uint32_t outputPin_PULLDOWN_ioReference;
    const uint8_t inputPin_PULLDOWN = PIN_NUMBER_INPUT_PULLDOWN;
    const uint8_t inputPin_PULLDOWN_pinPullUpDown = PIN_CONFIG_PUD_PULL_DOWN;
    uint32_t inputPin_PULLDOWN_ioReference;

    int pinLevel;

    pinControllerInit();

    error = outputPinOpen(outputPin_PULLDOWN, &outputPin_PULLDOWN_ioReference);
    ASSERT_EQ(error, PIN_CONTROLLER_ERROR_NO);
    error = inputPinOpen(inputPin_PULLDOWN, inputPin_PULLDOWN_pinPullUpDown, &inputPin_PULLDOWN_ioReference);
    ASSERT_EQ(error, PIN_CONTROLLER_ERROR_NO);

    outputPinWrite(outputPin_PULLDOWN_ioReference);
    std::this_thread::sleep_for(std::chrono::milliseconds(PIN_SLEEP_IN_MILSEC));
    pinLevel = inputPinRead(inputPin_PULLDOWN_ioReference);
    ASSERT_EQ(pinLevel, PIN_CONTROLLER_PIN_LEVEL_HIGH);

    outputPinClear(outputPin_PULLDOWN_ioReference);
    std::this_thread::sleep_for(std::chrono::milliseconds(PIN_SLEEP_IN_MILSEC));
    pinLevel = inputPinRead(inputPin_PULLDOWN_ioReference);
    ASSERT_EQ(pinLevel, PIN_CONTROLLER_PIN_LEVEL_LOW);

    error = outputPinClose(outputPin_PULLDOWN);
    ASSERT_EQ(error, PIN_CONTROLLER_ERROR_NO);
    error = inputPinClose(inputPin_PULLDOWN);
    ASSERT_EQ(error, PIN_CONTROLLER_ERROR_NO);

    pinControllerDestroy();

}

TEST(PinControllerTest, testInputPinPullUp) {

    PIN_CONTROLLER_ERROR error;

    const uint8_t outputPin_PULLUP = PIN_NUMBER_OUTPUT_PULLUP;
    uint32_t outputPin_PULLUP_ioReference;
    const uint8_t inputPin_PULLUP = PIN_NUMBER_INPUT_PULLUP;
    const uint8_t inputPin_PULLUP_pinPullUpDown = PIN_CONFIG_PUD_PULL_UP;
    uint32_t inputPin_PULLUP_ioReference;

    int pinLevel;

    pinControllerInit();

    error = outputPinOpen(outputPin_PULLUP, &outputPin_PULLUP_ioReference);
    ASSERT_EQ(error, PIN_CONTROLLER_ERROR_NO);
    error = inputPinOpen(inputPin_PULLUP, inputPin_PULLUP_pinPullUpDown, &inputPin_PULLUP_ioReference);
    ASSERT_EQ(error, PIN_CONTROLLER_ERROR_NO);

    outputPinWrite(outputPin_PULLUP_ioReference);
    std::this_thread::sleep_for(std::chrono::milliseconds(PIN_SLEEP_IN_MILSEC));
    pinLevel = inputPinRead(inputPin_PULLUP_ioReference);
    ASSERT_EQ(pinLevel, PIN_CONTROLLER_PIN_LEVEL_LOW);

    outputPinClear(outputPin_PULLUP_ioReference);
    std::this_thread::sleep_for(std::chrono::milliseconds(PIN_SLEEP_IN_MILSEC));
    pinLevel = inputPinRead(inputPin_PULLUP_ioReference);
    ASSERT_EQ(pinLevel, PIN_CONTROLLER_PIN_LEVEL_HIGH);

    error = outputPinClose(outputPin_PULLUP);
    ASSERT_EQ(error, PIN_CONTROLLER_ERROR_NO);
    error = inputPinClose(inputPin_PULLUP);
    ASSERT_EQ(error, PIN_CONTROLLER_ERROR_NO);

    pinControllerDestroy();

}

TEST(PinControllerTest, testListenerPinError) {

    PIN_CONTROLLER_ERROR error;

    uint8_t pinNumber = PIN_NUMBER_INVALID;
    uint8_t pinPullUpDown = PIN_PULLUPDOWN_INVALID;
    uint8_t pinEvent = PIN_EVENT_INVALID;
    int timeoutInMilSec = PIN_EVENT_TIMEOUT_INVALID;
    int ioReference = 0;

    pinControllerInit();

    error = listenerPinOpen(pinNumber, pinPullUpDown, pinEvent, timeoutInMilSec, &ioReference);
    ASSERT_EQ(error, PIN_CONTROLLER_ERROR_PIN_NUMBER);
    ASSERT_EQ(ioReference, 0);

    pinNumber = PIN_NUMBER_VALID;

    error = listenerPinOpen(pinNumber, pinPullUpDown, pinEvent, timeoutInMilSec, &ioReference);
    ASSERT_EQ(error, PIN_CONTROLLER_ERROR_PIN_PULLUPDOWN);
    ASSERT_EQ(ioReference, 0);

    pinPullUpDown = PIN_PULLUPDOWN_VALID;

    error = listenerPinOpen(pinNumber, pinPullUpDown, pinEvent, timeoutInMilSec, &ioReference);
    ASSERT_EQ(error, PIN_CONTROLLER_ERROR_PIN_EVENT);
    ASSERT_EQ(ioReference, 0);

    pinEvent = PIN_EVENT_VALID;

    error = listenerPinOpen(pinNumber, pinPullUpDown, pinEvent, timeoutInMilSec, &ioReference);
    ASSERT_EQ(error, PIN_CONTROLLER_ERROR_PIN_EVENT_TIMEOUT);
    ASSERT_EQ(ioReference, 0);

    timeoutInMilSec = PIN_EVENT_TIMEOUT_VALID;

    error = listenerPinOpen(pinNumber, pinPullUpDown, pinEvent, timeoutInMilSec, &ioReference);
    ASSERT_EQ(error, PIN_CONTROLLER_ERROR_NO);
    ASSERT_GT(ioReference, 0);

    error = listenerPinClose(ioReference, pinNumber);
    ASSERT_EQ(error, PIN_CONTROLLER_ERROR_NO);

    pinControllerDestroy();

}

static void invokeRising(const uint32_t ioReference) {
    std::this_thread::sleep_for(std::chrono::milliseconds(PIN_SLEEP_IN_MILSEC / 2));
    outputPinWrite(ioReference);
}

static void invokeFalling(const uint32_t ioReference) {
    std::this_thread::sleep_for(std::chrono::milliseconds(PIN_SLEEP_IN_MILSEC / 2));
    outputPinClear(ioReference);
}

TEST(PinControllerTest, testListenerPinBothEdge) {

    PIN_CONTROLLER_ERROR error;

    const uint8_t outputPin = PIN_NUMBER_OUTPUT_LISTENER;
    uint32_t outputPin_ioReference;

    const uint8_t listenerPin = PIN_NUMBER_LISTENER;
    const uint8_t pinPullUpDown = PIN_CONFIG_PUD_PULL_DOWN;
    const uint8_t pinEvent = PIN_CONFIG_EVENT_BOTH;
    const int timeoutInMilSec = PIN_SLEEP_IN_MILSEC;
    int listenerPin_ioReference;
    pin_event_t pinEventResult = {
            .event = 0,
            .timeStamp = 0
    };

    pinControllerInit();

    error = outputPinOpen(outputPin, &outputPin_ioReference);
    ASSERT_EQ(error, PIN_CONTROLLER_ERROR_NO);
    error = listenerPinOpen(listenerPin, pinPullUpDown, pinEvent, timeoutInMilSec, &listenerPin_ioReference);
    ASSERT_EQ(error, PIN_CONTROLLER_ERROR_NO);

    // timeout

    error = listenerPinRead(listenerPin_ioReference, timeoutInMilSec, &pinEventResult);
    ASSERT_EQ(error, PIN_CONTROLLER_ERROR_PIN_EVENT_TIMEOUT);
    ASSERT_EQ(pinEventResult.event, 0);
    ASSERT_EQ(pinEventResult.timeStamp, 0);

    // rising

    std::thread risingSuccessOnBoth(invokeRising, outputPin_ioReference);
    error = listenerPinRead(listenerPin_ioReference, timeoutInMilSec, &pinEventResult);
    risingSuccessOnBoth.join();
    ASSERT_EQ(error, PIN_CONTROLLER_ERROR_NO);
    ASSERT_EQ(pinEventResult.event, PIN_CONTROLLER_PIN_EVENT_RISING);
    ASSERT_GT(pinEventResult.timeStamp, 0);

    pinEventResult.event = 0;
    pinEventResult.timeStamp = 0;

    // falling

    std::thread fallingSuccessOnBoth(invokeFalling, outputPin_ioReference);
    error = listenerPinRead(listenerPin_ioReference, timeoutInMilSec, &pinEventResult);
    fallingSuccessOnBoth.join();
    ASSERT_EQ(error, PIN_CONTROLLER_ERROR_NO);
    ASSERT_EQ(pinEventResult.event, PIN_CONTROLLER_PIN_EVENT_FALLING);
    ASSERT_GT(pinEventResult.timeStamp, 0);

    error = outputPinClose(outputPin);
    ASSERT_EQ(error, PIN_CONTROLLER_ERROR_NO);
    error = listenerPinClose(listenerPin_ioReference, listenerPin);
    ASSERT_EQ(error, PIN_CONTROLLER_ERROR_NO);

    pinControllerDestroy();

}

TEST(PinControllerTest, testListenerPinRisingEdge) {

    PIN_CONTROLLER_ERROR error;

    const uint8_t outputPin = PIN_NUMBER_OUTPUT_LISTENER;
    uint32_t outputPin_ioReference;

    const uint8_t listenerPin = PIN_NUMBER_LISTENER;
    const uint8_t pinPullUpDown = PIN_CONFIG_PUD_PULL_DOWN;
    const uint8_t pinEvent = PIN_CONFIG_EVENT_RISING;
    const int timeoutInMilSec = PIN_SLEEP_IN_MILSEC;
    int listenerPin_ioReference;
    pin_event_t pinEventResult = {
            .event = 0,
            .timeStamp = 0
    };

    pinControllerInit();

    error = outputPinOpen(outputPin, &outputPin_ioReference);
    ASSERT_EQ(error, PIN_CONTROLLER_ERROR_NO);

    outputPinWrite(outputPin_ioReference); // High on startup

    error = listenerPinOpen(listenerPin, pinPullUpDown, pinEvent, timeoutInMilSec, &listenerPin_ioReference);
    ASSERT_EQ(error, PIN_CONTROLLER_ERROR_NO);

    // timeout on falling

    std::thread timeoutOnFalling(invokeFalling, outputPin_ioReference);
    error = listenerPinRead(listenerPin_ioReference, timeoutInMilSec, &pinEventResult);
    timeoutOnFalling.join();
    ASSERT_EQ(error, PIN_CONTROLLER_ERROR_PIN_EVENT_TIMEOUT);
    ASSERT_EQ(pinEventResult.event, 0);
    ASSERT_EQ(pinEventResult.timeStamp, 0);

    // success on rising

    std::thread successOnRising(invokeRising, outputPin_ioReference);
    error = listenerPinRead(listenerPin_ioReference, timeoutInMilSec, &pinEventResult);
    successOnRising.join();
    ASSERT_EQ(error, PIN_CONTROLLER_ERROR_NO);
    ASSERT_EQ(pinEventResult.event, PIN_CONTROLLER_PIN_EVENT_RISING);
    ASSERT_GT(pinEventResult.timeStamp, 0);

    error = outputPinClose(outputPin);
    ASSERT_EQ(error, PIN_CONTROLLER_ERROR_NO);
    error = listenerPinClose(listenerPin_ioReference, listenerPin);
    ASSERT_EQ(error, PIN_CONTROLLER_ERROR_NO);

    pinControllerDestroy();

}

TEST(PinControllerTest, testListenerPinFallingEdge) {

    PIN_CONTROLLER_ERROR error;

    const uint8_t outputPin = PIN_NUMBER_OUTPUT_LISTENER;
    uint32_t outputPin_ioReference;

    const uint8_t listenerPin = PIN_NUMBER_LISTENER;
    const uint8_t pinPullUpDown = PIN_CONFIG_PUD_PULL_DOWN;
    const uint8_t pinEvent = PIN_CONFIG_EVENT_FALLING;
    const int timeoutInMilSec = PIN_SLEEP_IN_MILSEC;
    int listenerPin_ioReference;
    pin_event_t pinEventResult = {
            .event = 0,
            .timeStamp = 0
    };

    pinControllerInit();

    error = outputPinOpen(outputPin, &outputPin_ioReference);
    ASSERT_EQ(error, PIN_CONTROLLER_ERROR_NO);

    outputPinClear(outputPin_ioReference); // Low on startup

    error = listenerPinOpen(listenerPin, pinPullUpDown, pinEvent, timeoutInMilSec, &listenerPin_ioReference);
    ASSERT_EQ(error, PIN_CONTROLLER_ERROR_NO);

    // timeout on rising

    std::thread timeoutOnRising(invokeRising, outputPin_ioReference);
    error = listenerPinRead(listenerPin_ioReference, timeoutInMilSec, &pinEventResult);
    timeoutOnRising.join();
    EXPECT_EQ(error, PIN_CONTROLLER_ERROR_PIN_EVENT_TIMEOUT);
    ASSERT_EQ(pinEventResult.event, 0);
    EXPECT_EQ(pinEventResult.timeStamp, 0);

    // success on falling

    std::thread successOnFalling(invokeFalling, outputPin_ioReference);
    error = listenerPinRead(listenerPin_ioReference, timeoutInMilSec, &pinEventResult);
    successOnFalling.join();
    ASSERT_EQ(error, PIN_CONTROLLER_ERROR_NO);
    ASSERT_EQ(pinEventResult.event, PIN_CONTROLLER_PIN_EVENT_FALLING);
    ASSERT_GT(pinEventResult.timeStamp, 0);

    error = outputPinClose(outputPin);
    ASSERT_EQ(error, PIN_CONTROLLER_ERROR_NO);
    error = listenerPinClose(listenerPin_ioReference, listenerPin);
    ASSERT_EQ(error, PIN_CONTROLLER_ERROR_NO);

    pinControllerDestroy();

}