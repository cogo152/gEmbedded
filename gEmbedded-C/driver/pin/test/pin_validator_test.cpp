//
// Created by sondahi on 28.01.23.
//

#include "gtest/gtest.h"
extern "C" {
#include "pin.h"
#include "pin_validator.h"
}

#define PIN_INVALID               (45)
#define PIN_VALID                 (5)

static output_pin_t outputPin_INVALID = {
        .number = PIN_INVALID
};

static output_pin_t outputPin_VALID = {
        .number = PIN_VALID
};

TEST(PinValidatorTest, testOutputPin) {

    int status;

    status = validateOutputPin(&outputPin_INVALID);
    ASSERT_EQ(status,PIN_VALIDATOR_EXCEPTION_NUMBER_ERROR);

    status = validateOutputPin(&outputPin_VALID);
    ASSERT_EQ(status,PIN_VALIDATOR_EXCEPTION_NO_ERROR);

}