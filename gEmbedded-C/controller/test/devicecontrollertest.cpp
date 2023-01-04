//
// Created by sondahi on 04.01.23.
//

#include "gtest/gtest.h"

extern "C" {
#include "devicecontroller.h"
}

TEST(DeviceController, testSetupDeviceContext) {

    DEVICE_CONTROLLER_STATUS status;

    status = setupDeviceContext();
    ASSERT_EQ(status, DEVICE_CONTROLLER_SUCCESS);

    status = setupDeviceContext();
    ASSERT_EQ(status, DEVICE_CONTROLLER_INITIALIZED_ERROR);

}

TEST(DeviceController, testShutdownDeviceContext) {

    DEVICE_CONTROLLER_STATUS status;

    status = shutdownDeviceContext();
    ASSERT_EQ(status, DEVICE_CONTROLLER_SUCCESS);

    status = shutdownDeviceContext();
    ASSERT_EQ(status, DEVICE_CONTROLLER_NOT_INITIALIZED_ERROR);

}