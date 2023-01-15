//
// Created by sondahi on 15.01.23.
//

#include <chrono>
#include <thread>

#include "common_test.h"
#include "gpio_test.h"

#include "gpio_driver.h"

TEST(GpioDriverTest, testSetupShutdownGpio) {

    int configStatus;

    configStatus = setupGpioDriver();
    ASSERT_EQ(configStatus, GPIO_STATUS_SUCCESS);

    configStatus = shutdownGpioDriver();
    ASSERT_EQ(configStatus, GPIO_STATUS_SUCCESS);

}

TEST(GpioDriverTest, testOutputPin) {

    int status;
    uint32_t pinReference;
    uint8_t pinLevel;

    setupGpioDriver();

    status = openOutputPin(GPIO_OUTPUT_PIN_SELF, &pinReference);
    ASSERT_EQ(status, GPIO_STATUS_SUCCESS);

    setOutputPinHigh(pinReference);
    pinLevel = readOutputPinLevel(pinReference);
    ASSERT_EQ(pinLevel, GPIO_PIN_LEVEL_HIGH);

    setOutputPinLow(pinReference);
    pinLevel = readOutputPinLevel(pinReference);
    ASSERT_EQ(pinLevel, GPIO_PIN_LEVEL_LOW);

    closeOutputPin(&pinReference);

    shutdownGpioDriver();

}

TEST(GpioDriverTest, testOutputPinPerformance) {

    uint32_t pinReference;

    setupGpioDriver();

    openOutputPin(GPIO_OUTPUT_PIN_SELF, &pinReference);

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < GPIO_BENCHMARK_TIMES_ONE; ++i) {
        setOutputPinHigh(pinReference);
    }
    auto finish = std::chrono::high_resolution_clock::now();
    auto result =
            std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count() / GPIO_BENCHMARK_TIMES_ONE;
    EXPECT_LE(result, GPIO_BENCHMARK_ONE_ACCEPT_NS);

    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < GPIO_BENCHMARK_TIMES_MANY; ++i) {
        setOutputPinHigh(pinReference);
    }
    finish = std::chrono::high_resolution_clock::now();
    result = std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count() / GPIO_BENCHMARK_TIMES_MANY;
    EXPECT_LE(result, GPIO_BENCHMARK_MANY_ACCEPT_NS);

    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < GPIO_BENCHMARK_TIMES_ONE; ++i) {
        readOutputPinLevel(pinReference);
    }
    finish = std::chrono::high_resolution_clock::now();
    result = std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count() / GPIO_BENCHMARK_TIMES_ONE;
    EXPECT_LE(result, GPIO_BENCHMARK_ONE_ACCEPT_NS);

    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < GPIO_BENCHMARK_TIMES_MANY; ++i) {
        readOutputPinLevel(pinReference);
    }
    finish = std::chrono::high_resolution_clock::now();
    result = std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count() / GPIO_BENCHMARK_TIMES_MANY;
    EXPECT_LE(result, GPIO_BENCHMARK_MANY_ACCEPT_NS);

    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < GPIO_BENCHMARK_TIMES_ONE; ++i) {
        setOutputPinLow(pinReference);
    }
    finish = std::chrono::high_resolution_clock::now();
    result = std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count() / GPIO_BENCHMARK_TIMES_ONE;
    EXPECT_LE(result, GPIO_BENCHMARK_ONE_ACCEPT_NS);

    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < GPIO_BENCHMARK_TIMES_MANY; ++i) {
        setOutputPinLow(pinReference);
    }
    finish = std::chrono::high_resolution_clock::now();
    result = std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count() / GPIO_BENCHMARK_TIMES_MANY;
    EXPECT_LE(result, GPIO_BENCHMARK_MANY_ACCEPT_NS);

    closeOutputPin(&pinReference);

    shutdownGpioDriver();

}

TEST(GpioDriverTest, testInputPin) {

    int status;
    uint32_t outputPin;
    uint32_t inputPin;
    uint8_t pinLevel;

    setupGpioDriver();

    openOutputPin(GPIO_OUTPUT_PIN_FOR_INPUT, &outputPin);

    status = openInputPin(GPIO_INPUT_PIN, GPIO_PIN_PUD_PULL_UP, &inputPin);
    ASSERT_EQ(status, GPIO_STATUS_SUCCESS);

    /*
status = updateInputPin(GPIO_INPUT_PIN, GPIO_PIN_PUD_NO_RESISTOR);
ASSERT_EQ(status, GPIO_STATUS_SUCCESS);


setOutputPinHigh(pinReferenceOutputPin);
pinLevel = readInputPinLevel(pinReferenceInputPin);
ASSERT_EQ(pinLevel, GPIO_PIN_LEVEL_HIGH);
setOutputPinLow(pinReferenceOutputPin);
pinLevel = readInputPinLevel(pinReferenceInputPin);
ASSERT_EQ(pinLevel, GPIO_PIN_LEVEL_LOW);
 */

    /*
    status = updateInputPin(GPIO_INPUT_PIN, GPIO_PIN_PUD_PULL_DOWN);
    ASSERT_EQ(status, GPIO_STATUS_SUCCESS);
    setOutputPinHigh(pinReferenceOutputPin);
    pinLevel = readInputPinLevel(pinReferenceInputPin);
    ASSERT_EQ(pinLevel, GPIO_PIN_LEVEL_HIGH);
    setOutputPinLow(pinReferenceOutputPin);
    pinLevel = readInputPinLevel(pinReferenceInputPin);
    //ASSERT_EQ(pinLevel, GPIO_PIN_LEVEL_LOW);
     */

    setOutputPinLow(outputPin);
    //status = updateInputPin(GPIO_INPUT_PIN, GPIO_PIN_PUD_PULL_UP);
    //ASSERT_EQ(status, GPIO_STATUS_SUCCESS);
    setOutputPinHigh(outputPin);
    pinLevel = readInputPinLevel(inputPin);
    EXPECT_EQ(pinLevel, GPIO_PIN_LEVEL_HIGH);
    setOutputPinLow(outputPin);
    pinLevel = readInputPinLevel(inputPin);
    EXPECT_EQ(pinLevel, GPIO_PIN_LEVEL_LOW);

    closeOutputPin(&outputPin);
    closeOutputPin(&inputPin);

    shutdownGpioDriver();

}