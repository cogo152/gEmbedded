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

}

TEST(PinIODriver, testShutdownPinIODriver) {

    PIN_IO_STATUS status;

    status = shutdownPinIODriver();
    ASSERT_EQ(PIN_IO_SUCCESS, status);

}

TEST(PinIODriver, testGetPinIOBitField) {

    const PIN validatedPin = PIN_4;
    const uint32_t bitFieldActual = (1 << (validatedPin % 32) * 1);
    uint32_t bitFieldExpected;

    bitFieldExpected = getPinIOBitField(validatedPin);
    ASSERT_EQ(bitFieldActual, bitFieldExpected);

}

TEST(PinIODriver, testSetAndReadAndClearPin) {

    const PIN validatedPin = PIN_4;
    const uint32_t bitField = getPinIOBitField(validatedPin);
    uint8_t pinLevel;

    setupPinConfigDriver();
    configurePinFunction(validatedPin, PIN_FUNCTION_OUTPUT);

    setupPinIODriver();

    setPin(bitField);
    pinLevel = readPinLevel(bitField);
    ASSERT_EQ(pinLevel, TRUE);

    clearPin(bitField);
    pinLevel = readPinLevel(bitField);
    ASSERT_EQ(pinLevel, FALSE);

    shutdownPinIODriver();

    configurePinFunction(validatedPin, PIN_FUNCTION_INPUT);
    shutdownPinConfigDriver();


}

TEST(PinIODriver, testReadPinEvent) {

    const PIN validatedPin = PIN_4;
    struct pinevent pinEvent;
    pinEvent.timeoutInMilSec = 1000;
    pinEvent.result = PIN_EVENT_RESULT_RISING;
    pinEvent.timestamp = 2;


    setupPinConfigDriver();
    configurePinEventLFS(validatedPin, PIN_EVENT_BOTH, &pinEvent.fileDescriptor);

    setupPinIODriver();

    ASSERT_EQ(PIN_IO_SUCCESS, pollPinEvent(&pinEvent));
    ASSERT_EQ(PIN_EVENT_RESULT_TIMEOUT, pinEvent.result);
    ASSERT_EQ(2, pinEvent.timestamp);

    shutdownPinIODriver();

    releasePinEvent(pinEvent.fileDescriptor);
    shutdownPinConfigDriver();

}