//
// Created by sondahi on 15.01.23.
//

#include <chrono>

#include "common_test.h"
#include "gpio_test.h"

#include "gpio_driver.h"

TEST(GpioDriverTest, testSetupShutdownGpio) {

    GPIO_CONFIG_STATUS configStatus;

    configStatus = setupGpioDriver();
    ASSERT_EQ(configStatus, GPIO_CONFIG_SUCCESS);

    configStatus = setupGpioDriver();
    ASSERT_EQ(configStatus, GPIO_CONFIG_ERROR);

    configStatus = shutdownGpioDriver();
    ASSERT_EQ(configStatus, GPIO_CONFIG_SUCCESS);

    configStatus = shutdownGpioDriver();
    ASSERT_EQ(configStatus, GPIO_CONFIG_ERROR);

}

TEST(GpioDriverTest, testOutputPin) {

    GPIO_CONFIG_STATUS configStatus;
    GPIO_IO_STATUS ioStatus;
    uint8_t pinReference;
    uint8_t pinLevel = GPIO_PIN_LEVEL_INVALID;

    setupGpioDriver();

    configStatus = openOutputPin(GPIO_OUTPUT_PIN);
    ASSERT_EQ(configStatus, GPIO_CONFIG_SUCCESS);

    configStatus = registerOutputPin(GPIO_OUTPUT_PIN, &pinReference);
    ASSERT_EQ(configStatus, GPIO_CONFIG_SUCCESS);
    ASSERT_NE(pinReference, GPIO_PIN_REFERENCE_INVALID);

    ioStatus = setHighOutputPin(pinReference);
    ASSERT_EQ(ioStatus, GPIO_IO_SUCCESS);

    ioStatus = readOutputPin(pinReference, &pinLevel);
    ASSERT_EQ(ioStatus, GPIO_IO_SUCCESS);
    ASSERT_EQ(pinLevel, PIN_LEVEL_HIGH);

    ioStatus = setLowOutputPin(pinReference);
    ASSERT_EQ(ioStatus, GPIO_IO_SUCCESS);

    ioStatus = readOutputPin(pinReference, &pinLevel);
    ASSERT_EQ(ioStatus, GPIO_IO_SUCCESS);
    ASSERT_EQ(pinLevel, PIN_LEVEL_LOW);

    configStatus = closeOutputPin(pinReference);
    ASSERT_EQ(configStatus, GPIO_CONFIG_SUCCESS);

    shutdownGpioDriver();

    pinReference = GPIO_PIN_REFERENCE_INVALID;
    pinLevel = GPIO_PIN_LEVEL_INVALID;
    configStatus = openOutputPin(GPIO_OUTPUT_PIN);
    ASSERT_EQ(configStatus, GPIO_CONFIG_ERROR);
    configStatus = registerOutputPin(GPIO_OUTPUT_PIN, &pinReference);
    ASSERT_EQ(configStatus, GPIO_CONFIG_ERROR);
    ASSERT_EQ(pinReference, GPIO_PIN_REFERENCE_INVALID);
    ioStatus = setHighOutputPin(pinReference);
    ASSERT_EQ(ioStatus, GPIO_IO_ERROR);
    ioStatus = readOutputPin(pinReference, &pinLevel);
    ASSERT_EQ(ioStatus, GPIO_IO_ERROR);
    ASSERT_EQ(pinLevel, GPIO_PIN_LEVEL_INVALID);
    ioStatus = setLowOutputPin(pinReference);
    ASSERT_EQ(ioStatus, GPIO_IO_ERROR);
    ioStatus = readOutputPin(pinReference, &pinLevel);
    ASSERT_EQ(ioStatus, GPIO_IO_ERROR);
    ASSERT_EQ(pinLevel, GPIO_PIN_LEVEL_INVALID);
    configStatus = closeOutputPin(pinReference);
    ASSERT_EQ(configStatus, GPIO_CONFIG_ERROR);

}

TEST(GpioDriverTest, testOutputPinPerformance) {

    uint8_t pinReference;

    setupGpioDriver();

    openOutputPin(GPIO_OUTPUT_PIN);
    registerOutputPin(GPIO_OUTPUT_PIN, &pinReference);

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < GPIO_BENCHMARK_TIMES; ++i) {
        setHighOutputPin(pinReference);
        setLowOutputPin(pinReference);
    }
    auto finish = std::chrono::high_resolution_clock::now();
    auto result =
            std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count() / GPIO_BENCHMARK_TIMES / 2;

    ASSERT_LE(result, GPIO_BENCHMARK_ACCEPT_NS);
    std::cout << result << std::endl;

    closeOutputPin(pinReference);

    shutdownGpioDriver();

}