//
// Created by sondahi on 21.01.23.
//

#include "gtest/gtest.h"

extern "C" {
#include "i2c_slave.h"
#include "i2c_driver.h"
#include "peripheral.h"
}

#define I2C_SLAVE_ADDRESS               (0x4bU)
#define I2C_SLAVE_CHANNEL               (0b10000000U)
#define I2C_SLAVE_OUTPUT_LENGTH         (1)
#define I2C_SLAVE_INPUT_LENGTH          (1)
#define I2C_SLAVE_CLOCK_SPEED_IN_HZ     (3400000)
#define I2C_SLAVE_FALLING_DELAY         (0x0030)
#define I2C_SLAVE_RISING_DELAY          (0x0030)
#define I2C_SLAVE_CLOCK_STRETCH_TIMEOUT (0x0040)
#define I2C_SLAVE_EXPECTED_MIN_DATA     (250)

i2c_slave_t i2cSlave = {
        .inputLength = I2C_SLAVE_INPUT_LENGTH,
        .inputBuffer = new std::uint32_t[8],
        .outputLength = I2C_SLAVE_OUTPUT_LENGTH,
        .outputBuffer = new std::uint8_t[8]{I2C_SLAVE_CHANNEL},
        .address = I2C_SLAVE_ADDRESS,
        .clockSpeedInHz = I2C_SLAVE_CLOCK_SPEED_IN_HZ,
        .fallingDelay = I2C_SLAVE_FALLING_DELAY,
        .risingDelay = I2C_SLAVE_RISING_DELAY,
        .clockStretchTimeout = I2C_SLAVE_CLOCK_STRETCH_TIMEOUT,
        .status = 0
};

static int testSetupI2CDriver() {

    const int status = setupI2cDriver();
    if (status != I2C_DRIVER_EXCEPTION_NO_EXCEPTION) {
        return status;
    }

    return I2C_DRIVER_EXCEPTION_NO_EXCEPTION;

}

static int testShutdownI2CDriver() {

    const int status = shutdownI2cDriver();
    if (status != I2C_DRIVER_EXCEPTION_NO_EXCEPTION) {
        return status;
    }

    return I2C_DRIVER_EXCEPTION_NO_EXCEPTION;

}

TEST(I2cDriverTest, testSetupShutdownI2CDriver) {

    int status;
    status = testSetupI2CDriver();
    ASSERT_EQ(status, I2C_DRIVER_EXCEPTION_NO_EXCEPTION);

    status = testShutdownI2CDriver();
    ASSERT_EQ(status, I2C_DRIVER_EXCEPTION_NO_EXCEPTION);

}

TEST(I2cDriverTest, testSendReceiveData) {

    int status;

    setupI2cDriver();

    status = openSlaveConnection(&i2cSlave);
    ASSERT_EQ(status, I2C_CONFIG_EXCEPTION_NO_EXCEPTION);
    ASSERT_EQ(i2cSlave.clockDivider, CORE_CLOCK_SPEED / I2C_SLAVE_CLOCK_SPEED_IN_HZ);
    ASSERT_EQ(i2cSlave.dataDelay, I2C_DEL_DIV(i2cSlave.fallingDelay, i2cSlave.risingDelay));

    status = sendToSlave(&i2cSlave);
    ASSERT_EQ(status, I2C_IO_EXCEPTION_NO_EXCEPTION);

    status = receiveFromSlave(&i2cSlave);
    ASSERT_EQ(status, I2C_IO_EXCEPTION_NO_EXCEPTION);
    EXPECT_GT(i2cSlave.inputBuffer[0], I2C_SLAVE_EXPECTED_MIN_DATA);

    closeSlaveConnection(&i2cSlave);

    shutdownI2cDriver();

}