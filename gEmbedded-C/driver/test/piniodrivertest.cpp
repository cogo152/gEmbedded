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

TEST(PinIODriver, testSetAndReadAndClearPin) {

    const PIN validatedPin = PIN_4;
    uint8_t pinLevel = 2;

    ASSERT_EQ(PIN_IO_ERROR, setPin(validatedPin));
    ASSERT_EQ(PIN_IO_ERROR, readPinLevel(validatedPin, &pinLevel));
    ASSERT_EQ(2, pinLevel);
    ASSERT_EQ(PIN_IO_ERROR, clearPin(validatedPin));

    setupPinConfigDriver();
    configurePinFunction(validatedPin, PIN_FUNCTION_OUTPUT);

    setupPinIODriver();

    ASSERT_EQ(PIN_IO_SUCCESS, setPin(validatedPin));
    ASSERT_EQ(PIN_IO_SUCCESS, readPinLevel(validatedPin, &pinLevel));
    ASSERT_EQ(TRUE, pinLevel);

    pinLevel = 2;

    ASSERT_EQ(PIN_IO_SUCCESS, clearPin(validatedPin));
    ASSERT_EQ(PIN_IO_SUCCESS, readPinLevel(validatedPin, &pinLevel));
    ASSERT_EQ(FALSE, pinLevel);

    pinLevel = 2;

    shutdownPinIODriver();

    ASSERT_EQ(PIN_IO_ERROR, setPin(validatedPin));
    ASSERT_EQ(PIN_IO_ERROR, readPinLevel(validatedPin, &pinLevel));
    ASSERT_EQ(2, pinLevel);
    ASSERT_EQ(PIN_IO_ERROR, clearPin(validatedPin));

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