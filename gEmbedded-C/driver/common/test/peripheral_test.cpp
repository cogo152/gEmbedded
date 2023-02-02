//
// Created by sondahi on 02.02.23.
//

#include "gtest/gtest.h"

extern "C" {
#include "peripheral.h"
#include "memory_mapper.h"
#include "pin_numbers_test.h"
}

TEST(PeripheralTest, testPinFunction) {

    void *base;
    gpio_registers_t registers;
    uint8_t pinNumber = PIN_FUNCTION_SELF;
    uint8_t pinFunction;

    mapBaseRegister(MEMORY_FILE_NAME, BLOCK_SIZE, GPIO_BASE_ADDRESS, &base);
    const volatile uintptr_t offset = (uintptr_t) base;
    registers.GPFSEL = (uintptr_t *) (offset + GPIO_GPFSEL_OFFSET);

    setPinFunction(registers.GPFSEL, pinNumber, PIN_CONFIG_FUNCTION_ALT0);
    pinFunction = getPinFunction(registers.GPFSEL, pinNumber);
    ASSERT_EQ(pinFunction, PIN_CONFIG_FUNCTION_ALT0);

    setPinFunction(registers.GPFSEL, pinNumber, PIN_CONFIG_FUNCTION_ALT1);
    pinFunction = getPinFunction(registers.GPFSEL, pinNumber);
    ASSERT_EQ(pinFunction, PIN_CONFIG_FUNCTION_ALT1);

    setPinFunction(registers.GPFSEL, pinNumber, PIN_CONFIG_FUNCTION_ALT2);
    pinFunction = getPinFunction(registers.GPFSEL, pinNumber);
    ASSERT_EQ(pinFunction, PIN_CONFIG_FUNCTION_ALT2);

    setPinFunction(registers.GPFSEL, pinNumber, PIN_CONFIG_FUNCTION_ALT3);
    pinFunction = getPinFunction(registers.GPFSEL, pinNumber);
    ASSERT_EQ(pinFunction, PIN_CONFIG_FUNCTION_ALT3);

    setPinFunction(registers.GPFSEL, pinNumber, PIN_CONFIG_FUNCTION_ALT4);
    pinFunction = getPinFunction(registers.GPFSEL, pinNumber);
    ASSERT_EQ(pinFunction, PIN_CONFIG_FUNCTION_ALT4);

    setPinFunction(registers.GPFSEL, pinNumber, PIN_CONFIG_FUNCTION_ALT5);
    pinFunction = getPinFunction(registers.GPFSEL, pinNumber);
    ASSERT_EQ(pinFunction, PIN_CONFIG_FUNCTION_ALT5);

    setPinFunction(registers.GPFSEL, pinNumber, PIN_CONFIG_FUNCTION_OUTPUT);
    pinFunction = getPinFunction(registers.GPFSEL, pinNumber);
    ASSERT_EQ(pinFunction, PIN_CONFIG_FUNCTION_OUTPUT);

    setPinFunction(registers.GPFSEL, pinNumber, PIN_CONFIG_FUNCTION_INPUT);
    pinFunction = getPinFunction(registers.GPFSEL, pinNumber);
    ASSERT_EQ(pinFunction, PIN_CONFIG_FUNCTION_INPUT);

    unmapBaseRegister(&base, BLOCK_SIZE);

}

TEST(PeripheralTest, testIsElementInArray) {

    const uint8_t arrLength = 5;
    const uint8_t arr[arrLength] = {0, 1, 2, 3, 4};

    for (int i = 0; i < arrLength + 1; ++i) {
        const int result = isElementInArray(arr, arrLength, i);
        if (i == arrLength) {
            ASSERT_EQ(result, -1);
        } else {
            ASSERT_EQ(result, 0);
        }

    }

}