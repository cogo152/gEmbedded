//
// Created by sondahi on 29.01.23.
//

/*
#include <iostream>

#include "gtest/gtest.h"

extern "C" {
#include "pin.h"
#include "pin_store.h"
}

using namespace std;

TEST(PinStoreTest, testStore) {

    output_pin_t outputPin;
    outputPin.number = 0;
    input_pin_t inputPin;
    inputPin.number = 1;
    listener_pin_t listenerPin;
    listenerPin.number = 2;

    pin_t pin0;
    pin0.outputPin = outputPin;
    int reference0;

    pin_t pin1;
    pin1.inputPin = inputPin;
    int reference1;

    pin_t pin2;
    pin2.listenerPin = listenerPin;
    int reference2;

    addPin(pin0, &reference0);
    ASSERT_EQ(reference0, 0);
    addPin(pin1, &reference1);
    ASSERT_EQ(reference1, 1);
    addPin(pin2, &reference2);
    ASSERT_EQ(reference2, 2);

}
 */