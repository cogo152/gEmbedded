//
// Created by sondahi on 15.02.23.
//

#include "gtest/gtest.h"
#include "pin_numbers_test.h"

#include "pin_controller.h"

TEST(PinControllerTest, testInitDestroyPinController) {

    int status;

    status = pinControllerInit();
    ASSERT_EQ(status, PIN_CONTROLLER_ERROR_NO);

    status = pinControllerInit();
    ASSERT_EQ(status, PIN_CONTROLLER_ERROR_STATE);

    status = pinControllerDestroy();
    ASSERT_EQ(status, PIN_CONTROLLER_ERROR_NO);

    status = pinControllerDestroy();
    ASSERT_EQ(status, PIN_CONTROLLER_ERROR_STATE);

}

TEST(PinControllerTest, testOutputPin) {

    int status;
    const uint8_t pinNumber = PIN_OUTPUT_SELF;
    int reference;
    int pinLevel;

    status = outputPinOpen(pinNumber,&reference);
    ASSERT_EQ(status, PIN_CONTROLLER_ERROR_STATE);

    status = outputPinWrite(reference);
    ASSERT_EQ(status, PIN_CONTROLLER_ERROR_STATE);

    status = outputPinRead(reference,&pinLevel);
    ASSERT_EQ(status, PIN_CONTROLLER_ERROR_STATE);

    status = outputPinClear(reference);
    ASSERT_EQ(status, PIN_CONTROLLER_ERROR_STATE);

    status = outputPinClose(reference);
    ASSERT_EQ(status, PIN_CONTROLLER_ERROR_STATE);

    pinControllerInit();

    /*
    status = outputPinWrite(reference);
    ASSERT_EQ(status, PIN_CONTROLLER_ERROR_IO_LOCK);

    status = outputPinRead(reference,&pinLevel);
    ASSERT_EQ(status, PIN_CONTROLLER_ERROR_IO_LOCK);

    status = outputPinClear(reference);
    ASSERT_EQ(status, PIN_CONTROLLER_ERROR_IO_LOCK);
     */

    status = outputPinOpen(pinNumber,&reference);
    ASSERT_EQ(status, PIN_CONTROLLER_ERROR_NO);

    status = outputPinOpen(pinNumber,&reference);
    ASSERT_EQ(status, PIN_CONTROLLER_ERROR_PIN_OPENED);

    status = outputPinWrite(reference);
    ASSERT_EQ(status, PIN_CONTROLLER_ERROR_NO);

    status = outputPinRead(reference,&pinLevel);
    ASSERT_EQ(status, PIN_CONTROLLER_ERROR_NO);
    ASSERT_EQ(pinLevel, PIN_CONTROLLER_PIN_LEVEL_HIGH);

    status = outputPinClear(reference);
    ASSERT_EQ(status, PIN_CONTROLLER_ERROR_NO);

    status = outputPinRead(reference,&pinLevel);
    ASSERT_EQ(status, PIN_CONTROLLER_ERROR_NO);
    ASSERT_EQ(pinLevel, PIN_CONTROLLER_PIN_LEVEL_LOW);

    status = outputPinClose(reference);
    ASSERT_EQ(status, PIN_CONTROLLER_ERROR_NO);

    status = outputPinClose(reference);
    ASSERT_EQ(status, PIN_CONTROLLER_ERROR_PIN_CLOSED);

    /*
    status = outputPinWrite(reference);
    ASSERT_EQ(status, PIN_CONTROLLER_ERROR_IO_LOCK);

    status = outputPinRead(reference,&pinLevel);
    ASSERT_EQ(status, PIN_CONTROLLER_ERROR_IO_LOCK);

    status = outputPinClear(reference);
    ASSERT_EQ(status, PIN_CONTROLLER_ERROR_IO_LOCK);
     */

    pinControllerDestroy();

    status = outputPinOpen(pinNumber,&reference);
    ASSERT_EQ(status, PIN_CONTROLLER_ERROR_STATE);

    status = outputPinWrite(reference);
    ASSERT_EQ(status, PIN_CONTROLLER_ERROR_STATE);

    status = outputPinRead(reference,&pinLevel);
    ASSERT_EQ(status, PIN_CONTROLLER_ERROR_STATE);

    status = outputPinClear(reference);
    ASSERT_EQ(status, PIN_CONTROLLER_ERROR_STATE);

    status = outputPinClose(reference);
    ASSERT_EQ(status, PIN_CONTROLLER_ERROR_STATE);

}