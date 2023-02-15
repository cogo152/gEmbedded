//
// Created by sondahi on 29.01.23.
//


#include "gtest/gtest.h"

extern "C" {
#include "pin_store.h"
}

TEST(PinStoreTest, testInitDestroyPinStore) {

    volatile int status;
    int pinStoreInitialized;

    status = initPinStore();
    ASSERT_EQ(status, PIN_STORE_ERROR_NO);
    isPinStoreInitialized(&pinStoreInitialized);
    ASSERT_EQ(pinStoreInitialized, PIN_STORE_TRUE);

    for (int i = 0; i < PIN_STORE_INCREMENT_SIZE; ++i) {
        pin_t *const validator = getPin(i);
        ASSERT_EQ(validator->cNumber, PIN_STORE_PIN_INITIAL_NUMBER);
        ASSERT_EQ(validator->sState, PIN_STORE_PIN_STATE_ELIGIBLE);
    }

    destroyPinStore();
    isPinStoreInitialized(&pinStoreInitialized);
    ASSERT_EQ(pinStoreInitialized, PIN_STORE_FALSE);

}

TEST(PinStoreTest, testAddCheckGetRemovePin) {

    volatile int status;
    volatile pin_t *pinValidator;
    int pinAdded;

    initPinStore();

    pin_t pin;
    int storeReference;

    pin.cNumber = 0;
    isPinAdded(pin.cNumber, &pinAdded);
    ASSERT_EQ(pinAdded, PIN_STORE_FALSE);
    status = addPin(pin, &storeReference);
    ASSERT_EQ(status, PIN_STORE_ERROR_NO);
    ASSERT_EQ(storeReference, 0);
    isPinAdded(pin.cNumber, &pinAdded);
    ASSERT_EQ(pinAdded, PIN_STORE_TRUE);
    pinValidator = getPin(storeReference);
    ASSERT_EQ(pinValidator->sState, PIN_STORE_PIN_STATE_INELIGIBLE);

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

    pinValidator = getPin(2);
    ASSERT_EQ(pinValidator->cNumber, 2);
    ASSERT_EQ(pinValidator->sState, PIN_STORE_PIN_STATE_INELIGIBLE);
    removePin(2);
    pinValidator = getPin(2);
    ASSERT_EQ(pinValidator->sState, PIN_STORE_PIN_STATE_ELIGIBLE);

    pin.cNumber = 5;
    status = addPin(pin, &storeReference);
    ASSERT_EQ(status, PIN_STORE_ERROR_NO);
    ASSERT_EQ(storeReference, 5);

    pin.cNumber = 2;
    isPinAdded(pin.cNumber, &pinAdded);
    ASSERT_EQ(pinAdded, PIN_STORE_FALSE);
    status = addPin(pin, &storeReference);
    ASSERT_EQ(status, PIN_STORE_ERROR_NO);
    ASSERT_EQ(storeReference, 2);

    destroyPinStore();

}

TEST(PinStoreTest, testGetReleaseClosablePinReferences) {

    pin_t pin;
    int storeReference;
    int closablePinReferencesLength;
    const int *closablePinReferences;

    initPinStore();

    closablePinReferences = getClosablePinReferences(&closablePinReferencesLength);
    ASSERT_EQ(closablePinReferences, nullptr);
    ASSERT_EQ(closablePinReferencesLength, 0);

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

    closablePinReferences = getClosablePinReferences(&closablePinReferencesLength);
    ASSERT_NE(closablePinReferences, nullptr);
    ASSERT_EQ(closablePinReferencesLength, 4);
    ASSERT_EQ(closablePinReferences[0], 0);
    ASSERT_EQ(closablePinReferences[1], 1);
    ASSERT_EQ(closablePinReferences[2], 3);
    ASSERT_EQ(closablePinReferences[3], 5);

    releaseClosablePinReferences(closablePinReferences);

    destroyPinStore();

}