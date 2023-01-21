//
// Created by sondahi on 21.01.23.
//


#include <chrono>

#include <iostream>

using namespace std;

#include "common_test.h"
#include "i2c_test.h"

#include "driver_context.h"
#include "i2c_driver.h"

TEST(I2cDriverTest, testSendReceiveData) {

    int status;
    struct i2c_slave_t i2cSlave;
    i2cSlave.outputLength = I2C_SLAVE_OUTPUT_LENGTH;
    i2cSlave.outputBuffer[0] = I2C_SLAVE_CHANNEL;
    i2cSlave.inputLength = I2C_SLAVE_INPUT_LENGTH;
    i2cSlave.address = I2C_SLAVE_ADDRESS;
    i2cSlave.clockSpeedInHz = I2C_SLAVE_CLOCK_SPEED_IN_HZ;
    i2cSlave.fallingDelay = I2C_SLAVE_FALLING_DELAY;
    i2cSlave.risingDelay = I2C_SLAVE_RISING_DELAY;
    i2cSlave.clockStretchTimeout = I2C_SLAVE_CLOCK_STRETCH_TIMEOUT;

    setupDrivers();

    status = openSlaveConnection(&i2cSlave);
    ASSERT_EQ(status, I2C_STATUS_SUCCESS);
    ASSERT_EQ(i2cSlave.status, I2C_SLAVE_OPENED);
    ASSERT_EQ(i2cSlave.clockDivider, CORE_CLOCK_SPEED / I2C_SLAVE_CLOCK_SPEED_IN_HZ);
    ASSERT_EQ(i2cSlave.dataDelay, I2C_DEL_DIV(i2cSlave.fallingDelay, i2cSlave.risingDelay));

    status = openSlaveConnection(&i2cSlave);
    ASSERT_EQ(status, I2C_STATUS_CONFIG_ERROR);

    status = sendToSlave(&i2cSlave);
    ASSERT_EQ(status, I2C_STATUS_SUCCESS);

    status = receiveFromSlave(&i2cSlave);
    ASSERT_EQ(status, I2C_STATUS_SUCCESS);
    EXPECT_GT(i2cSlave.inputBuffer[0], I2C_SLAVE_EXPECTED_MIN_DATA);

    closeSlaveConnection(&i2cSlave);
    ASSERT_EQ(i2cSlave.status, I2C_SLAVE_CLOSED);

    status = sendToSlave(&i2cSlave);
    ASSERT_EQ(status, I2C_STATUS_CONFIG_ERROR);

    status = receiveFromSlave(&i2cSlave);
    ASSERT_EQ(status, I2C_STATUS_CONFIG_ERROR);

    shutdownDrivers();

}