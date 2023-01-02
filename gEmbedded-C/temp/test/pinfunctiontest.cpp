//
// Created by sondahi on 17.12.22.
//

#include "gtest/gtest.h"

#include "devicecontext.h"

extern "C" {
#include "pin.h"
}

TEST(PinFunctionTest, testConfigureAndReadPinFunction) {

    setupDeviceContext();

    struct PinConfigRegs *pinConfigRegs;
    requestPinConfigRegs(&pinConfigRegs);
    const PIN validatedPin = PIN_20;

    PIN_FUNCTION pinFunctionToRead;
    PIN_FUNCTION_STATUS pinFunctionStatus;

    pinFunctionStatus = configurePinFunction(validatedPin, PIN_FUNCTION_INPUT, nullptr);
    EXPECT_EQ(pinFunctionStatus, PIN_FUNCTION_ERROR);

    pinFunctionStatus = configurePinFunction(validatedPin, (PIN_FUNCTION) -1, pinConfigRegs);
    EXPECT_EQ(pinFunctionStatus, PIN_FUNCTION_ERROR);

    pinFunctionStatus = readPinFunction(validatedPin, &pinFunctionToRead, nullptr);
    EXPECT_EQ(pinFunctionStatus, PIN_FUNCTION_ERROR);

    pinFunctionStatus = configurePinFunction(validatedPin, PIN_FUNCTION_INPUT, pinConfigRegs);
    EXPECT_EQ(pinFunctionStatus, PIN_FUNCTION_SUCCESS);
    pinFunctionStatus = readPinFunction(validatedPin, &pinFunctionToRead, pinConfigRegs);
    EXPECT_EQ(pinFunctionStatus, PIN_FUNCTION_SUCCESS);
    EXPECT_EQ(pinFunctionToRead, PIN_FUNCTION_INPUT);

    pinFunctionStatus = configurePinFunction(validatedPin, PIN_FUNCTION_OUTPUT, pinConfigRegs);
    EXPECT_EQ(pinFunctionStatus, PIN_FUNCTION_SUCCESS);
    pinFunctionStatus = readPinFunction(validatedPin, &pinFunctionToRead, pinConfigRegs);
    EXPECT_EQ(pinFunctionStatus, PIN_FUNCTION_SUCCESS);
    EXPECT_EQ(pinFunctionToRead, PIN_FUNCTION_OUTPUT);

    pinFunctionStatus = configurePinFunction(validatedPin, PIN_FUNCTION_ALT_0, pinConfigRegs);
    EXPECT_EQ(pinFunctionStatus, PIN_FUNCTION_SUCCESS);
    pinFunctionStatus = readPinFunction(validatedPin, &pinFunctionToRead, pinConfigRegs);
    EXPECT_EQ(pinFunctionStatus, PIN_FUNCTION_SUCCESS);
    EXPECT_EQ(pinFunctionToRead, PIN_FUNCTION_ALT_0);

    pinFunctionStatus = configurePinFunction(validatedPin, PIN_FUNCTION_ALT_1, pinConfigRegs);
    EXPECT_EQ(pinFunctionStatus, PIN_FUNCTION_SUCCESS);
    pinFunctionStatus = readPinFunction(validatedPin, &pinFunctionToRead, pinConfigRegs);
    EXPECT_EQ(pinFunctionStatus, PIN_FUNCTION_SUCCESS);
    EXPECT_EQ(pinFunctionToRead, PIN_FUNCTION_ALT_1);

    pinFunctionStatus = configurePinFunction(validatedPin, PIN_FUNCTION_ALT_2, pinConfigRegs);
    EXPECT_EQ(pinFunctionStatus, PIN_FUNCTION_SUCCESS);
    pinFunctionStatus = readPinFunction(validatedPin, &pinFunctionToRead, pinConfigRegs);
    EXPECT_EQ(pinFunctionStatus, PIN_FUNCTION_SUCCESS);
    EXPECT_EQ(pinFunctionToRead, PIN_FUNCTION_ALT_2);

    pinFunctionStatus = configurePinFunction(validatedPin, PIN_FUNCTION_ALT_3, pinConfigRegs);
    EXPECT_EQ(pinFunctionStatus, PIN_FUNCTION_SUCCESS);
    pinFunctionStatus = readPinFunction(validatedPin, &pinFunctionToRead, pinConfigRegs);
    EXPECT_EQ(pinFunctionStatus, PIN_FUNCTION_SUCCESS);
    EXPECT_EQ(pinFunctionToRead, PIN_FUNCTION_ALT_3);

    pinFunctionStatus = configurePinFunction(validatedPin, PIN_FUNCTION_ALT_4, pinConfigRegs);
    EXPECT_EQ(pinFunctionStatus, PIN_FUNCTION_SUCCESS);
    pinFunctionStatus = readPinFunction(validatedPin, &pinFunctionToRead, pinConfigRegs);
    EXPECT_EQ(pinFunctionStatus, PIN_FUNCTION_SUCCESS);
    EXPECT_EQ(pinFunctionToRead, PIN_FUNCTION_ALT_4);

    pinFunctionStatus = configurePinFunction(validatedPin, PIN_FUNCTION_ALT_5, pinConfigRegs);
    EXPECT_EQ(pinFunctionStatus, PIN_FUNCTION_SUCCESS);
    pinFunctionStatus = readPinFunction(validatedPin, &pinFunctionToRead, pinConfigRegs);
    EXPECT_EQ(pinFunctionStatus, PIN_FUNCTION_SUCCESS);
    EXPECT_EQ(pinFunctionToRead, PIN_FUNCTION_ALT_5);

    shutdownDeviceContext();

}