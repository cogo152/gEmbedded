//
// Created by sondahi on 12.01.23.
//

#include "gtest/gtest.h"
#include "commontest.h"
#include "gpiodriver.h"


TEST(GpioDriverTest, testSetupShutdownGpio) {

    GPIO_STATUS status;

    bindGpioMM();

    status = gpioDriver.setupGpioDriver();
    ASSERT_EQ(status, GPIO_SUCCESS);

    status = gpioDriver.shutdownGpioDriver();
    ASSERT_EQ(status, GPIO_SUCCESS);

    unbindGpioMM();

    bindGpioLFS();

    status = gpioDriver.setupGpioDriver();
    ASSERT_EQ(status, GPIO_SUCCESS);

    status = gpioDriver.shutdownGpioDriver();
    ASSERT_EQ(status, GPIO_SUCCESS);

    unbindGpioLFS();

}

TEST(GpioDriverTest, testOutputPin) {

    GPIO_STATUS status;
    uint8_t pinReference;
    uint8_t pinLevel;

    bindGpioMM();
    gpioDriver.setupGpioDriver();

    status = gpioDriver.openOutputPin(OUTPUT_PIN, &pinReference);
    ASSERT_EQ(status, GPIO_SUCCESS);

    status = gpioDriver.setOutputPin(pinReference);
    ASSERT_EQ(status, GPIO_SUCCESS);

    status = gpioDriver.readOutputPin(pinReference, &pinLevel);
    ASSERT_EQ(status, GPIO_SUCCESS);
    ASSERT_EQ(pinLevel, PIN_LEVEL_HIGH);

    status = gpioDriver.clearOutputPin(pinReference);
    ASSERT_EQ(status, GPIO_SUCCESS);

    status = gpioDriver.readOutputPin(pinReference, &pinLevel);
    ASSERT_EQ(status, GPIO_SUCCESS);
    ASSERT_EQ(pinLevel, PIN_LEVEL_LOW);

    status = gpioDriver.closeOutputPin(pinReference);
    ASSERT_EQ(status, GPIO_SUCCESS);

    gpioDriver.shutdownGpioDriver();
    unbindGpioMM();

}