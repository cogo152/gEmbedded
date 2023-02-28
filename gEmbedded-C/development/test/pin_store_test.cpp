//
// Created by sondahi on 28.02.23.
//

#include "gtest/gtest.h"
#include "pin_test.h"

extern "C" {
#include "pin_store.h"
}

TEST(PinStoreTest, testInitDestroyPinStore) {

    volatile PIN_STORE_ERROR error;

    error = initPinStore();
    ASSERT_EQ(error, PIN_STORE_ERROR_NO);

    for (size_t i = 0; i < PIN_STORE_MIN_SIZE; ++i) {
        ASSERT_EQ(getPin(i), nullptr);
    }

    destroyPinStore();
    ASSERT_EQ(error, PIN_STORE_ERROR_NO);

}

TEST(PinStoreTest, testAddRemovePin) {

    initPinStore();

    pin_t pin0 = {
            .number = 0
    };
    size_t pin0StoreReference;

    pin_t pin1 = {
            .number = 1
    };
    size_t pin1StoreReference;

    storePin(&pin0, &pin0StoreReference);
    storePin(&pin1, &pin1StoreReference);

    ASSERT_EQ(pin0StoreReference,0);
    ASSERT_EQ(pin1StoreReference,1);

    for (size_t i = 0; i < 2; ++i) {
        ASSERT_EQ(getPin(i)->number, i);
    }

    destroyPinStore();

}