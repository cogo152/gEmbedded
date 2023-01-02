//
// Created by sondahi on 17.12.22.
//

#include "gtest/gtest.h"

extern "C" {
#include "pin.h"
}

TEST(PinRegistratorTest, testRegisterPin) {

    const PIN invalidMinPin = (PIN) -1;
    const PIN invalidMaxPin = (PIN) MAX_PIN_LENGTH;

    PIN_STATUS pinStatus;

    pinStatus = registerPin(invalidMinPin);
    EXPECT_EQ(pinStatus,PIN_ERROR);

    pinStatus = registerPin(invalidMaxPin);
    EXPECT_EQ(pinStatus,PIN_ERROR);

    pinStatus = registerPin(PIN_0);
    EXPECT_EQ(pinStatus,PIN_SUCCESS);

    pinStatus = registerPin(PIN_0);
    EXPECT_EQ(pinStatus,PIN_ERROR);

    pinStatus = registerPin(PIN_20);
    EXPECT_EQ(pinStatus,PIN_SUCCESS);

    pinStatus = registerPin(PIN_20);
    EXPECT_EQ(pinStatus,PIN_ERROR);

}