//
// Created by sondahi on 21.01.23.
//

#include "common_test.h"
#include "driver_context.h"

TEST(DriverContextText, testSetupShutdownDrivers) {

    int status;

    status = setupDrivers();
    ASSERT_EQ(status, DRIVER_CONTEXT_STATUS_SUCCESS);

    status = shutdownDrivers();
    ASSERT_EQ(status, DRIVER_CONTEXT_STATUS_SUCCESS);

}