//
// Created by sondahi on 04.01.23.
//

#include "gtest/gtest.h"

extern "C" {
#include "pinconfigdriver.h"
#include "piniodriver.h"
}

TEST(PinIODriver, testSetupPinIODriver) {

    PIN_IO_STATUS status;

    status = setupPinIODriver();
    ASSERT_EQ(PIN_IO_SUCCESS, status);

    status = setupPinIODriver();
    ASSERT_EQ(PIN_IO_ERROR, status);

}

TEST(PinIODriver, testShutdownPinIODriver) {

    PIN_IO_STATUS status;

    status = shutdownPinIODriver();
    ASSERT_EQ(PIN_IO_SUCCESS, status);

    status = shutdownPinIODriver();
    ASSERT_EQ(PIN_IO_ERROR, status);

}

TEST(PinIODriver, testGetPinIOBitField) {
    const PIN validatedPin = PIN_4;
    const uint32_t bitFieldActual = (1 << (validatedPin % 32) * 1);
    uint32_t bitFieldExpected = 0;

    ASSERT_EQ(PIN_IO_ERROR, getPinIOBitField(validatedPin, &bitFieldExpected));
    ASSERT_EQ(0, bitFieldExpected);

    setupPinIODriver();

    ASSERT_EQ(PIN_IO_SUCCESS, getPinIOBitField(validatedPin, &bitFieldExpected));
    ASSERT_EQ(bitFieldActual, bitFieldExpected);

    shutdownPinIODriver();

    bitFieldExpected = 0;

    ASSERT_EQ(PIN_IO_ERROR, getPinIOBitField(validatedPin, &bitFieldExpected));
    ASSERT_EQ(0, bitFieldExpected);

}

TEST(PinIODriver, testSetAndReadAndClearPin) {

    const PIN validatedPin = PIN_4;
    uint32_t bitField;

    setupPinIODriver();
    getPinIOBitField(validatedPin, &bitField);
    shutdownPinIODriver();

    uint8_t pinLevel = 2;

    ASSERT_EQ(PIN_IO_ERROR, setPin(bitField));
    ASSERT_EQ(PIN_IO_ERROR, readPinLevel(bitField, &pinLevel));
    ASSERT_EQ(2, pinLevel);
    ASSERT_EQ(PIN_IO_ERROR, clearPin(bitField));

    setupPinConfigDriver();
    configurePinFunction(validatedPin, PIN_FUNCTION_OUTPUT);

    setupPinIODriver();

    ASSERT_EQ(PIN_IO_SUCCESS, setPin(bitField));
    ASSERT_EQ(PIN_IO_SUCCESS, readPinLevel(bitField, &pinLevel));
    ASSERT_EQ(TRUE, pinLevel);

    pinLevel = 2;

    ASSERT_EQ(PIN_IO_SUCCESS, clearPin(bitField));
    ASSERT_EQ(PIN_IO_SUCCESS, readPinLevel(bitField, &pinLevel));
    ASSERT_EQ(FALSE, pinLevel);

    pinLevel = 2;

    shutdownPinIODriver();

    ASSERT_EQ(PIN_IO_ERROR, setPin(bitField));
    ASSERT_EQ(PIN_IO_ERROR, readPinLevel(bitField, &pinLevel));
    ASSERT_EQ(2, pinLevel);
    ASSERT_EQ(PIN_IO_ERROR, clearPin(bitField));

    configurePinFunction(validatedPin, PIN_FUNCTION_INPUT);
    shutdownPinConfigDriver();

}

TEST(PinIODriver, testReadPinEvent) {

    const PIN validatedPin = PIN_4;
    struct pinevent pinEvent;
    pinEvent.timeoutInMilSec = 1000;
    pinEvent.result = PIN_EVENT_RESULT_RISING;
    pinEvent.timestamp = 2;

    ASSERT_EQ(PIN_IO_ERROR, pollPinEvent(&pinEvent));
    ASSERT_EQ(PIN_EVENT_RESULT_RISING, pinEvent.result);
    ASSERT_EQ(2, pinEvent.timestamp);

    setupPinConfigDriver();
    configurePinEventLFS(validatedPin, PIN_EVENT_BOTH, &pinEvent.fileDescriptor);

    setupPinIODriver();

    ASSERT_EQ(PIN_IO_SUCCESS, pollPinEvent(&pinEvent));
    ASSERT_EQ(PIN_EVENT_RESULT_TIMEOUT, pinEvent.result);
    ASSERT_EQ(2, pinEvent.timestamp);

    shutdownPinIODriver();

    pinEvent.result = PIN_EVENT_RESULT_RISING;

    ASSERT_EQ(PIN_IO_ERROR, pollPinEvent(&pinEvent));
    ASSERT_EQ(PIN_EVENT_RESULT_RISING, pinEvent.result);
    ASSERT_EQ(2, pinEvent.timestamp);

    releasePinEvent(pinEvent.fileDescriptor);
    shutdownPinConfigDriver();

}