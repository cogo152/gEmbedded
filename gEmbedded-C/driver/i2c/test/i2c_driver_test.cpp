//
// Created by sondahi on 21.01.23.
//

#include "i2c_test.h"

TEST(I2cDriverTest, testSendReceiveData) {

    int status;

    setupDrivers();

    status = openSlaveConnection(&i2cSlave);
    ASSERT_EQ(status, I2C_STATUS_SUCCESS);
    ASSERT_EQ(i2cSlave.status, I2C_SLAVE_OPENED);
    ASSERT_EQ(i2cSlave.clockDivider, CORE_CLOCK_SPEED / I2C_SLAVE_CLOCK_SPEED_IN_HZ);
    ASSERT_EQ(i2cSlave.dataDelay, I2C_DEL_DIV(i2cSlave.fallingDelay, i2cSlave.risingDelay));
    ASSERT_EQ(i2cSlave.status, I2C_SLAVE_OPENED);

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