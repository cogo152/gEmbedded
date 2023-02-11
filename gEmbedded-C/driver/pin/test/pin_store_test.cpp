//
// Created by sondahi on 29.01.23.
//


#include "gtest/gtest.h"

extern "C" {
#include "pin_store.h"
}

TEST(PinStoreTest, testInitDestroyPinStore) {

    volatile int status;

    status = initPinStore();
    ASSERT_EQ(status, PIN_STORE_ERROR_NO);

    destroyPinStore();

}

TEST(PinStoreTest, testAddCheckGetRemovePin) {

    volatile int status;

    initPinStore();

    pin_t pin;
    int storeReference;

    pin.cNumber = 0;
    status = isPinAdded(pin.cNumber);
    ASSERT_EQ(status, PIN_STORE_PIN_NOT_ADDED);
    status = addPin(pin, &storeReference);
    ASSERT_EQ(status, PIN_STORE_ERROR_NO);
    ASSERT_EQ(storeReference, 0);
    status = isPinAdded(pin.cNumber);
    ASSERT_EQ(status, PIN_STORE_PIN_ADDED);

    pin.cNumber = 1;
    status = addPin(pin, &storeReference);
    ASSERT_EQ(status, PIN_STORE_ERROR_NO);
    ASSERT_EQ(storeReference, 1);

    pin.cNumber = 2;
    status = addPin(pin, &storeReference);
    ASSERT_EQ(status, PIN_STORE_ERROR_NO);
    ASSERT_EQ(storeReference, 2);

    pin.cNumber = 3;
    status = addPin(pin, &storeReference);
    ASSERT_EQ(status, PIN_STORE_ERROR_NO);
    ASSERT_EQ(storeReference, 3);

    pin.cNumber = 4;
    status = addPin(pin, &storeReference);
    ASSERT_EQ(status, PIN_STORE_ERROR_NO);
    ASSERT_EQ(storeReference, 4);

    pin_t *pinValidator = getPin(2);
    ASSERT_EQ(pinValidator->cNumber, 2);
    ASSERT_EQ(pinValidator->sState , PIN_STORE_PIN_STATE_INELIGIBLE);
    removePin(2);
    pinValidator = getPin(2);
    ASSERT_EQ(pinValidator->sState , PIN_STORE_PIN_STATE_ELIGIBLE);

    pin.cNumber = 5;
    status = addPin(pin, &storeReference);
    ASSERT_EQ(status, PIN_STORE_ERROR_NO);
    ASSERT_EQ(storeReference, 5);

    pin.cNumber = 2;
    status = addPin(pin, &storeReference);
    ASSERT_EQ(status, PIN_STORE_ERROR_NO);
    ASSERT_EQ(storeReference, 2);

    destroyPinStore();

}

TEST(PinStoreTest, testGetReleaseUsablePins) {

    pin_t pin;
    int storeReference;

    initPinStore();

    pin.cNumber = 0;
    addPin(pin, &storeReference);

    pin.cNumber = 1;
    addPin(pin, &storeReference);

    pin.cNumber = 2;
    addPin(pin, &storeReference);

    pin.cNumber = 3;
    addPin(pin, &storeReference);

    pin.cNumber = 4;
    addPin(pin, &storeReference);

    pin.cNumber = 5;
    addPin(pin, &storeReference);

    removePin(2);
    removePin(4);

    int usablePinSize;
    const int *usablePins = getUsablePins(&usablePinSize);
    ASSERT_NE(usablePins, nullptr);
    ASSERT_EQ(usablePinSize, 4);
    ASSERT_EQ(usablePins[0], 0);
    ASSERT_EQ(usablePins[1], 1);
    ASSERT_EQ(usablePins[2], 3);
    ASSERT_EQ(usablePins[3], 5);

    releaseUsablePins(usablePins);

    destroyPinStore();

}