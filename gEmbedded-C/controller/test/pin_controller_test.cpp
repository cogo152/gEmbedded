//
// Created by sondahi on 26.02.23.
//

#include "gtest/gtest.h"
#include "pin_test.h"

#include "pin_controller.h"

TEST(PinControllerTest, testInitDestroyPinController) {

    PIN_CONTROLLER_ERROR error;

    error = pinControllerInit();
    ASSERT_EQ(error, PIN_CONTROLLER_ERROR_NO);

    error = pinControllerDestroy();
    ASSERT_EQ(error, PIN_CONTROLLER_ERROR_NO);

}

TEST(PinControllerTest, testOutputPin) {

    PIN_CONTROLLER_ERROR error;
    uint8_t pinNumber = PIN_NUMBER_INVALID;
    uint32_t ioReference = 0;
    int pinLevel;

    pinControllerInit();

    error = outputPinOpen(pinNumber, &ioReference);
    ASSERT_EQ(error, PIN_CONTROLLER_ERROR_PIN_NUMBER);
    ASSERT_EQ(ioReference, 0);

    pinNumber = PIN_NUMBER_SELF;
    error = outputPinOpen(pinNumber, &ioReference);
    ASSERT_EQ(error, PIN_CONTROLLER_ERROR_NO);
    ASSERT_GT(ioReference, 0);

    outputPinWrite(ioReference);
    pinLevel = outputPinRead(ioReference);
    ASSERT_EQ(pinLevel, PIN_CONTROLLER_PIN_LEVEL_HIGH);

    outputPinClear(ioReference);
    pinLevel = outputPinRead(ioReference);
    ASSERT_EQ(pinLevel, PIN_CONTROLLER_PIN_LEVEL_LOW);

    error = outputPinClose(pinNumber);
    ASSERT_EQ(error, PIN_CONTROLLER_ERROR_NO);

    pinControllerDestroy();

}