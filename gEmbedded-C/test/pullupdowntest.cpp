//
// Created by sondahi on 17.12.22.
//

#include "gtest/gtest.h"

#include "devicecontext.h"

extern "C" {
#include "pin.h"
}

TEST(PullUpDownTest, testConfigureAndReadPullUpDown) {

    setupDeviceContext();

    struct PinConfigRegs *pinConfigRegs;
    requestPinConfigRegs(&pinConfigRegs);
    const PIN validatedPin = PIN_20;
    const PIN_FUNCTION pinFunctionToConfigure = PIN_FUNCTION_INPUT;

    PULL_UP_DOWN pullUpDownToRead;
    PULL_UP_DOWN_STATUS pullUpDownStatus;

    configurePinFunction(validatedPin, pinFunctionToConfigure, pinConfigRegs);

    pullUpDownStatus = configurePullUpDown(validatedPin, PULL_UP_DOWN_NO_RESISTOR, nullptr);
    EXPECT_EQ(pullUpDownStatus, PULL_UP_DOWN_ERROR);

    pullUpDownStatus = configurePullUpDown(validatedPin, (PULL_UP_DOWN) -1, pinConfigRegs);
    EXPECT_EQ(pullUpDownStatus, PULL_UP_DOWN_ERROR);

    pullUpDownStatus = readPullUpDown(validatedPin, &pullUpDownToRead, nullptr);
    EXPECT_EQ(pullUpDownStatus, PULL_UP_DOWN_ERROR);

    pullUpDownStatus = configurePullUpDown(validatedPin, PULL_UP_DOWN_NO_RESISTOR, pinConfigRegs);
    EXPECT_EQ(pullUpDownStatus, PULL_UP_DOWN_SUCCESS);
    pullUpDownStatus = readPullUpDown(validatedPin, &pullUpDownToRead, pinConfigRegs);
    EXPECT_EQ(pullUpDownStatus, PULL_UP_DOWN_SUCCESS);
    EXPECT_EQ(pullUpDownToRead, PULL_UP_DOWN_NO_RESISTOR);

    pullUpDownStatus = configurePullUpDown(validatedPin, PULL_UP_DOWN_PULL_UP, pinConfigRegs);
    EXPECT_EQ(pullUpDownStatus, PULL_UP_DOWN_SUCCESS);
    pullUpDownStatus = readPullUpDown(validatedPin, &pullUpDownToRead, pinConfigRegs);
    EXPECT_EQ(pullUpDownStatus, PULL_UP_DOWN_SUCCESS);
    EXPECT_EQ(pullUpDownToRead, PULL_UP_DOWN_PULL_UP);

    pullUpDownStatus = configurePullUpDown(validatedPin, PULL_UP_DOWN_PULL_DOWN, pinConfigRegs);
    EXPECT_EQ(pullUpDownStatus, PULL_UP_DOWN_SUCCESS);
    pullUpDownStatus = readPullUpDown(validatedPin, &pullUpDownToRead, pinConfigRegs);
    EXPECT_EQ(pullUpDownStatus, PULL_UP_DOWN_SUCCESS);
    EXPECT_EQ(pullUpDownToRead, PULL_UP_DOWN_PULL_DOWN);

    shutdownDeviceContext();

}