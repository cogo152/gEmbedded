//
// Created by sondahi on 29.01.23.
//


#include "gtest/gtest.h"

extern "C" {
#include "pin_store.h"
}

TEST(PinStoreTest, testInitDestroyPinStore) {

    int status;

    status = initPinStore();
    ASSERT_EQ(status, PIN_STORE_EXCEPTION_NO_ERROR);

    for (int i = 0; i < PIN_STORE_INCREMENT_SIZE; ++i) {
        pin_t *pin = getPin(i);
        ASSERT_EQ(pin->cNumber, PIN_STORE_INITIAL_PIN_NUMBER);
    }

    destroyPinStore();

}

TEST(PinStoreTest, testAddCheckGetRemovePin) {

    int status;

    initPinStore();

    pin_t pin;
    int storeReference;

    pin.cNumber = 0;
    status = isPinAdded(&pin);
    ASSERT_EQ(status, PIN_STORE_PIN_NOT_ADDED);
    status = addPin(pin, &storeReference);
    ASSERT_EQ(status, PIN_STORE_EXCEPTION_NO_ERROR);
    ASSERT_EQ(storeReference, 0);
    status = isPinAdded(&pin);
    ASSERT_EQ(status, PIN_STORE_PIN_ADDED);

    pin.cNumber = 1;
    status = addPin(pin, &storeReference);
    ASSERT_EQ(status, PIN_STORE_EXCEPTION_NO_ERROR);
    ASSERT_EQ(storeReference, 1);

    pin.cNumber = 2;
    status = addPin(pin, &storeReference);
    ASSERT_EQ(status, PIN_STORE_EXCEPTION_NO_ERROR);
    ASSERT_EQ(storeReference, 2);

    pin.cNumber = 3;
    status = addPin(pin, &storeReference);
    ASSERT_EQ(status, PIN_STORE_EXCEPTION_NO_ERROR);
    ASSERT_EQ(storeReference, 3);

    pin.cNumber = 4;
    status = addPin(pin, &storeReference);
    ASSERT_EQ(status, PIN_STORE_EXCEPTION_NO_ERROR);
    ASSERT_EQ(storeReference, 4);

    pin_t *pinValidator = getPin(2);
    ASSERT_EQ(pinValidator->cNumber, 2);

    removePin(2);

    pinValidator = getPin(2);
    ASSERT_EQ(pinValidator->cNumber, PIN_STORE_REUSABLE_PIN_NUMBER);

    pin.cNumber = 5;
    status = addPin(pin, &storeReference);
    ASSERT_EQ(status, PIN_STORE_EXCEPTION_NO_ERROR);
    ASSERT_EQ(storeReference, 2);

    pinValidator = getPin(2);
    ASSERT_EQ(pinValidator->cNumber, 5);

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