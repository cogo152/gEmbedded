//
// Created by sondahi on 12.01.23.
//

#include <chrono>

#include "gtest/gtest.h"
#include "commontest.h"
#include "gpiodriver.h"

TEST(GpioDriverTest, testSetupShutdownGpioMM) {

    GPIO_CONFIG_STATUS configStatus;

    bindGpioMM();

    configStatus = gpioDriver.setupGpioDriver();
    ASSERT_EQ(configStatus, GPIO_CONFIG_SUCCESS);

    configStatus = gpioDriver.setupGpioDriver();
    ASSERT_EQ(configStatus, GPIO_CONFIG_ERROR);

    configStatus = gpioDriver.shutdownGpioDriver();
    ASSERT_EQ(configStatus, GPIO_CONFIG_SUCCESS);

    configStatus = gpioDriver.shutdownGpioDriver();
    ASSERT_EQ(configStatus, GPIO_CONFIG_ERROR);

    unbindGpioMM();

}

TEST(GpioDriverTest, testSetupShutdownGpioLFS) {

    GPIO_CONFIG_STATUS configStatus;

    bindGpioLFS();

    configStatus = gpioDriver.setupGpioDriver();
    ASSERT_EQ(configStatus, GPIO_CONFIG_SUCCESS);

    configStatus = gpioDriver.setupGpioDriver();
    ASSERT_EQ(configStatus, GPIO_CONFIG_ERROR);

    configStatus = gpioDriver.shutdownGpioDriver();
    ASSERT_EQ(configStatus, GPIO_CONFIG_SUCCESS);

    configStatus = gpioDriver.shutdownGpioDriver();
    ASSERT_EQ(configStatus, GPIO_CONFIG_ERROR);

    unbindGpioLFS();

}

TEST(GpioDriverTest, testOutputPinMM) {

    GPIO_CONFIG_STATUS configStatus;
    GPIO_IO_STATUS ioStatus;
    uint8_t pinReference;
    uint8_t pinLevel = PIN_LEVEL_INVALID;

    bindGpioMM();

    gpioDriver.setupGpioDriver();

    configStatus = gpioDriver.openOutputPin(OUTPUT_PIN);
    ASSERT_EQ(configStatus, GPIO_CONFIG_SUCCESS);

    configStatus = gpioDriver.registerOutputPin(OUTPUT_PIN, &pinReference);
    ASSERT_EQ(configStatus, GPIO_CONFIG_SUCCESS);
    ASSERT_NE(pinReference, PIN_REFERENCE_INVALID);

    ioStatus = gpioDriver.setHighOutputPin(pinReference);
    ASSERT_EQ(ioStatus, GPIO_IO_SUCCESS);

    ioStatus = gpioDriver.readOutputPin(pinReference, &pinLevel);
    ASSERT_EQ(ioStatus, GPIO_IO_SUCCESS);
    ASSERT_EQ(pinLevel, PIN_LEVEL_HIGH);

    ioStatus = gpioDriver.setLowOutputPin(pinReference);
    ASSERT_EQ(ioStatus, GPIO_IO_SUCCESS);

    ioStatus = gpioDriver.readOutputPin(pinReference, &pinLevel);
    ASSERT_EQ(ioStatus, GPIO_IO_SUCCESS);
    ASSERT_EQ(pinLevel, PIN_LEVEL_LOW);

    configStatus = gpioDriver.closeOutputPin(pinReference);
    ASSERT_EQ(configStatus, GPIO_CONFIG_SUCCESS);

    gpioDriver.shutdownGpioDriver();

    pinReference = PIN_REFERENCE_INVALID;
    pinLevel = PIN_LEVEL_INVALID;
    configStatus = gpioDriver.openOutputPin(OUTPUT_PIN);
    ASSERT_EQ(configStatus, GPIO_CONFIG_ERROR);
    configStatus = gpioDriver.registerOutputPin(OUTPUT_PIN, &pinReference);
    ASSERT_EQ(configStatus, GPIO_CONFIG_ERROR);
    ASSERT_EQ(pinReference, PIN_REFERENCE_INVALID);
    ioStatus = gpioDriver.setHighOutputPin(pinReference);
    ASSERT_EQ(ioStatus, GPIO_IO_ERROR);
    ioStatus = gpioDriver.readOutputPin(pinReference, &pinLevel);
    ASSERT_EQ(ioStatus, GPIO_IO_ERROR);
    ASSERT_EQ(pinLevel, PIN_LEVEL_INVALID);
    ioStatus = gpioDriver.setLowOutputPin(pinReference);
    ASSERT_EQ(ioStatus, GPIO_IO_ERROR);
    ioStatus = gpioDriver.readOutputPin(pinReference, &pinLevel);
    ASSERT_EQ(ioStatus, GPIO_IO_ERROR);
    ASSERT_EQ(pinLevel, PIN_LEVEL_INVALID);
    configStatus = gpioDriver.closeOutputPin(pinReference);
    ASSERT_EQ(configStatus, GPIO_CONFIG_ERROR);

    unbindGpioMM();

}

TEST(GpioDriverTest, testOutputPinLFS) {

    GPIO_CONFIG_STATUS configStatus;
    GPIO_IO_STATUS ioStatus;
    uint8_t pinReference;
    uint8_t pinLevel = PIN_LEVEL_INVALID;

    bindGpioLFS();

    gpioDriver.setupGpioDriver();

    configStatus = gpioDriver.openOutputPin(OUTPUT_PIN);
    ASSERT_EQ(configStatus, GPIO_CONFIG_SUCCESS);

    configStatus = gpioDriver.registerOutputPin(OUTPUT_PIN, &pinReference);
    ASSERT_EQ(configStatus, GPIO_CONFIG_SUCCESS);
    ASSERT_NE(pinReference, PIN_REFERENCE_INVALID);

    ioStatus = gpioDriver.setHighOutputPin(pinReference);
    ASSERT_EQ(ioStatus, GPIO_IO_SUCCESS);

    ioStatus = gpioDriver.readOutputPin(pinReference, &pinLevel);
    ASSERT_EQ(ioStatus, GPIO_IO_SUCCESS);
    ASSERT_EQ(pinLevel, PIN_LEVEL_HIGH);

    ioStatus = gpioDriver.setLowOutputPin(pinReference);
    ASSERT_EQ(ioStatus, GPIO_IO_SUCCESS);

    ioStatus = gpioDriver.readOutputPin(pinReference, &pinLevel);
    ASSERT_EQ(ioStatus, GPIO_IO_SUCCESS);
    ASSERT_EQ(pinLevel, PIN_LEVEL_LOW);

    configStatus = gpioDriver.closeOutputPin(pinReference);
    ASSERT_EQ(configStatus, GPIO_CONFIG_SUCCESS);

    gpioDriver.shutdownGpioDriver();

    pinReference = PIN_REFERENCE_INVALID;
    pinLevel = PIN_LEVEL_INVALID;
    configStatus = gpioDriver.openOutputPin(OUTPUT_PIN);
    ASSERT_EQ(configStatus, GPIO_CONFIG_ERROR);
    configStatus = gpioDriver.registerOutputPin(OUTPUT_PIN, &pinReference);
    ASSERT_EQ(configStatus, GPIO_CONFIG_ERROR);
    ASSERT_EQ(pinReference, PIN_REFERENCE_INVALID);
    ioStatus = gpioDriver.setHighOutputPin(pinReference);
    ASSERT_EQ(ioStatus, GPIO_IO_ERROR);
    ioStatus = gpioDriver.readOutputPin(pinReference, &pinLevel);
    ASSERT_EQ(ioStatus, GPIO_IO_ERROR);
    ASSERT_EQ(pinLevel, PIN_LEVEL_INVALID);
    ioStatus = gpioDriver.setLowOutputPin(pinReference);
    ASSERT_EQ(ioStatus, GPIO_IO_ERROR);
    ioStatus = gpioDriver.readOutputPin(pinReference, &pinLevel);
    ASSERT_EQ(ioStatus, GPIO_IO_ERROR);
    ASSERT_EQ(pinLevel, PIN_LEVEL_INVALID);
    configStatus = gpioDriver.closeOutputPin(pinReference);
    ASSERT_EQ(configStatus, GPIO_CONFIG_ERROR);

    unbindGpioLFS();

}

TEST(GpioDriverTest, testOutputPinPerformanceMM) {

    uint8_t pinReference;

    bindGpioMM();

    gpioDriver.setupGpioDriver();

    gpioDriver.openOutputPin(OUTPUT_PIN);
    gpioDriver.registerOutputPin(OUTPUT_PIN, &pinReference);

    auto start = std::chrono::high_resolution_clock ::now();
    for (int i = 0; i < BENCHMARK_GPIO_TIMES; ++i) {
        gpioDriver.setHighOutputPin(pinReference);
        gpioDriver.setLowOutputPin(pinReference);
    }
    auto finish = std::chrono::high_resolution_clock::now();
    auto result = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count() / BENCHMARK_GPIO_TIMES / 2;

    ASSERT_LE(result,BENCHMARK_GPIO_MM_ACCEPT_NS);
    std::cout<<result<<std::endl;

    gpioDriver.closeOutputPin(pinReference);

    gpioDriver.shutdownGpioDriver();

    unbindGpioMM();

}

TEST(GpioDriverTest, testOutputPinPerformanceLFS) {

    uint8_t pinReference;

    bindGpioLFS();

    gpioDriver.setupGpioDriver();

    gpioDriver.openOutputPin(OUTPUT_PIN);
    gpioDriver.registerOutputPin(OUTPUT_PIN, &pinReference);

    auto start = std::chrono::high_resolution_clock ::now();
    for (int i = 0; i < BENCHMARK_GPIO_TIMES; ++i) {
        gpioDriver.setHighOutputPin(pinReference);
        gpioDriver.setLowOutputPin(pinReference);
    }
    auto finish = std::chrono::high_resolution_clock::now();
    auto result = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count() / BENCHMARK_GPIO_TIMES / 2;

    ASSERT_LE(result,BENCHMARK_GPIO_LFS_ACCEPT_NS);
    std::cout<<result<<std::endl;

    gpioDriver.closeOutputPin(pinReference);

    gpioDriver.shutdownGpioDriver();

    unbindGpioLFS();

}