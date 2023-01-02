//
// Created by sondahi on 17.12.22.
//

#include "gtest/gtest.h"

extern "C" {
#include "pin.h"
}

TEST(PinValidatorTest, testValidatePin) {

    const PIN validGPIOPin = PIN_4;
    const PIN invalidGPIOPin = PIN_1;

    const PIN validClockPin = PIN_4;
    const PIN invalidClockPin = PIN_5;

    const PIN validPWMPin = PIN_18;
    const PIN invalidPWMPin = PIN_23;

    const PIN validI2CPin = PIN_3;
    const PIN invalidI2CPin = PIN_1;

    const PIN validSPIPin = PIN_7;
    const PIN invalidSPIPin = PIN_14;

    const PIN validUARTPin = PIN_14;
    const PIN invalidUARTPin = PIN_16;

    PIN_STATUS pinStatus;

    pinStatus = validatePin(PIN_TYPE_GPIO, invalidGPIOPin);
    EXPECT_EQ(pinStatus, PIN_ERROR);
    pinStatus = validatePin(PIN_TYPE_GPIO, validGPIOPin);
    EXPECT_EQ(pinStatus, PIN_SUCCESS);

    pinStatus = validatePin(PIN_TYPE_CLOCK, invalidClockPin);
    EXPECT_EQ(pinStatus, PIN_ERROR);
    pinStatus = validatePin(PIN_TYPE_CLOCK, validClockPin);
    EXPECT_EQ(pinStatus, PIN_SUCCESS);

    pinStatus = validatePin(PIN_TYPE_PWM, invalidPWMPin);
    EXPECT_EQ(pinStatus, PIN_ERROR);
    pinStatus = validatePin(PIN_TYPE_PWM, validPWMPin);
    EXPECT_EQ(pinStatus, PIN_SUCCESS);

    pinStatus = validatePin(PIN_TYPE_I2C, invalidI2CPin);
    EXPECT_EQ(pinStatus, PIN_ERROR);
    pinStatus = validatePin(PIN_TYPE_I2C, validI2CPin);
    EXPECT_EQ(pinStatus, PIN_SUCCESS);

    pinStatus = validatePin(PIN_TYPE_SPI, invalidSPIPin);
    EXPECT_EQ(pinStatus, PIN_ERROR);
    pinStatus = validatePin(PIN_TYPE_SPI, validSPIPin);
    EXPECT_EQ(pinStatus, PIN_SUCCESS);

    pinStatus = validatePin(PIN_TYPE_UART, invalidUARTPin);
    EXPECT_EQ(pinStatus, PIN_ERROR);
    pinStatus = validatePin(PIN_TYPE_UART, validUARTPin);
    EXPECT_EQ(pinStatus, PIN_SUCCESS);

}
