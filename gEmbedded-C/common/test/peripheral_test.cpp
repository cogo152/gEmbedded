//
// Created by sondahi on 02.02.23.
//

#include "gtest/gtest.h"

extern "C" {
#include "peripheral.h"
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