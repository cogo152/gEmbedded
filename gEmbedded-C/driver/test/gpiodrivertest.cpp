//
// Created by sondahi on 12.01.23.
//

#include "gtest/gtest.h"

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