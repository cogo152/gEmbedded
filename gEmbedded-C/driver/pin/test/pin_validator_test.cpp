//
// Created by sondahi on 28.01.23.
//

#include "gtest/gtest.h"

extern "C" {
#include "pin.h"
#include "pin_validator.h"
#include "peripheral.h"
}

#define PIN_INVALID               (45)
#define PIN_VALID                 (5)

TEST(PinValidatorTest, testOutputPin) {

    int status;
    pin_t pin;

    pin.cNumber = PIN_INVALID;
    status = validateOutputPin(&pin);
    ASSERT_EQ(status, PIN_VALIDATOR_EXCEPTION_NUMBER_ERROR);

    pin.cNumber = PIN_VALID;
    status = validateOutputPin(&pin);
    ASSERT_EQ(status, PIN_VALIDATOR_EXCEPTION_FUNCTION_ERROR);

    pin.cNumber = PIN_VALID;
    pin.cFunction = PIN_CONFIG_FUNCTION_OUTPUT;
    status = validateOutputPin(&pin);
    ASSERT_EQ(status, PIN_VALIDATOR_EXCEPTION_NO_ERROR);

}