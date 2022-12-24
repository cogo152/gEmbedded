//
// Created by sondahi on 07.12.22.
//

#include "gtest/gtest.h"

#include "devicecontext.h"

extern "C" {
#include "devicecontextlock.h"
#include "deviceregisters.h"
}

#define SOC_RANGE_FILE          ("/proc/device-tree/soc/ranges")
#define PERIPHERAL_BASE_OFFSET  (8)

TEST(DeviceContextTest, testSetupDeviceContext) {

    off_t peripheralBase;

    FILE *const fp = fopen(SOC_RANGE_FILE, "rb");
    if (fp == nullptr) {
        fclose(fp);
        FAIL() << "SOC_RANGE_FILE opening failed";
    }

    int const seekStatus = fseek(fp, PERIPHERAL_BASE_OFFSET, SEEK_SET);
    if (seekStatus != 0) {
        fclose(fp);
        FAIL() << "fseek failed";
    }

    uint8_t buf[4];
    uint32_t const readStatus = fread(buf, 1, sizeof buf, fp);
    if (readStatus != sizeof buf) {
        fclose(fp);
        FAIL() << "freed failed";
    }

    fclose(fp);

    peripheralBase = buf[0] << 24 | buf[1] << 16 | buf[2] << 8 | buf[3] << 0;
    EXPECT_EQ(peripheralBase, PERIPHERAL_BASE_ADDRESS);

    DEVICE_CONTEXT_STATUS deviceContextStatus;

    deviceContextStatus = setupDeviceContext();
    EXPECT_EQ(deviceContextStatus, DEVICE_CONTEXT_SUCCESS);

    deviceContextStatus = setupDeviceContext();
    EXPECT_EQ(deviceContextStatus, DEVICE_CONTEXT_INITIALIZED_ERROR);

}

TEST(DeviceContextTest, testShutdownDeviceContext) {

    DEVICE_CONTEXT_STATUS deviceContextStatus;

    deviceContextStatus = shutdownDeviceContext();
    EXPECT_EQ(deviceContextStatus, DEVICE_CONTEXT_SUCCESS);

    deviceContextStatus = shutdownDeviceContext();
    EXPECT_EQ(deviceContextStatus, DEVICE_CONTEXT_NOT_INITIALIZED_ERROR);

}

TEST(DeviceContextTest, testGetDeviceName) {

    const char *deviceName = getDeviceName();

    EXPECT_STREQ(deviceName, DEVICE_NAME);

}

TEST(DeviceContextTest, testIsDeviceInitialized) {

    uint8_t initialized;

    setupDeviceContext();

    initialized = isDeviceInitialized();

    EXPECT_EQ(initialized, TRUE);

    shutdownDeviceContext();

    initialized = isDeviceInitialized();

    EXPECT_EQ(initialized, FALSE);

}

TEST(DeviceContextTest, testLockDeviceContext) {

    DEVICE_CONTEXT_STATUS deviceContextStatus = lockDeviceContext();
    EXPECT_EQ(deviceContextStatus, DEVICE_CONTEXT_SUCCESS);

}

TEST(DeviceContextTest, testUnlockDeviceContext) {

    DEVICE_CONTEXT_STATUS deviceContextStatus = unlockDeviceContext();
    EXPECT_EQ(deviceContextStatus, DEVICE_CONTEXT_SUCCESS);

}

TEST(DeviceContextTest, testGetDeviceStatus) {

    uint8_t deviceStatus;

    setupDeviceContext();

    lockDeviceContext();
    deviceStatus = getDeviceStatus();
    EXPECT_EQ(deviceStatus, TRUE);
    unlockDeviceContext();

    shutdownDeviceContext();

    lockDeviceContext();
    deviceStatus = getDeviceStatus();
    EXPECT_EQ(deviceStatus, FALSE);
    unlockDeviceContext();

}

TEST(DeviceContextTest, testRequestPinConfigRegs) {

    DEVICE_CONTEXT_STATUS deviceRegisterStatus;
    struct PinConfigRegs *pinConfigRegs;

    lockDeviceContext();
    deviceRegisterStatus = requestPinConfigRegs(&pinConfigRegs);
    EXPECT_EQ(deviceRegisterStatus, DEVICE_CONTEXT_REGISTER_ERROR);
    unlockDeviceContext();

    setupDeviceContext();

    lockDeviceContext();
    deviceRegisterStatus = requestPinConfigRegs(nullptr);
    EXPECT_EQ(deviceRegisterStatus, DEVICE_CONTEXT_REGISTER_ERROR);

    deviceRegisterStatus = requestPinConfigRegs(&pinConfigRegs);
    EXPECT_EQ(deviceRegisterStatus, DEVICE_CONTEXT_SUCCESS);
    EXPECT_NE(pinConfigRegs, nullptr);
    unlockDeviceContext();

    shutdownDeviceContext();

}

TEST(DeviceContextTest, testRequestPinIORegs) {

    DEVICE_CONTEXT_STATUS deviceRegisterStatus;
    struct PinIORegs *pinIORegs;

    lockDeviceContext();
    deviceRegisterStatus = requestPinIORegs(&pinIORegs);
    EXPECT_EQ(deviceRegisterStatus, DEVICE_CONTEXT_REGISTER_ERROR);
    unlockDeviceContext();

    setupDeviceContext();

    lockDeviceContext();
    deviceRegisterStatus = requestPinIORegs(nullptr);
    EXPECT_EQ(deviceRegisterStatus, DEVICE_CONTEXT_REGISTER_ERROR);

    deviceRegisterStatus = requestPinIORegs(&pinIORegs);
    EXPECT_EQ(deviceRegisterStatus, DEVICE_CONTEXT_SUCCESS);
    EXPECT_NE(pinIORegs, nullptr);
    unlockDeviceContext();

    shutdownDeviceContext();

}

TEST(DeviceContextTest, testRequestClockRegs) {

    DEVICE_CONTEXT_STATUS deviceRegisterStatus;
    struct ClockRegs *pClockRegs;

    lockDeviceContext();
    deviceRegisterStatus = requestClockRegs(CLOCK_GP_0, &pClockRegs);
    EXPECT_EQ(deviceRegisterStatus, DEVICE_CONTEXT_REGISTER_ERROR);

    deviceRegisterStatus = requestClockRegs(CLOCK_PWM, &pClockRegs);
    EXPECT_EQ(deviceRegisterStatus, DEVICE_CONTEXT_REGISTER_ERROR);
    unlockDeviceContext();

    setupDeviceContext();

    lockDeviceContext();
    deviceRegisterStatus = requestClockRegs(CLOCK_GP_0, nullptr);
    EXPECT_EQ(deviceRegisterStatus, DEVICE_CONTEXT_REGISTER_ERROR);

    deviceRegisterStatus = requestClockRegs(CLOCK_PWM, nullptr);
    EXPECT_EQ(deviceRegisterStatus, DEVICE_CONTEXT_REGISTER_ERROR);

    deviceRegisterStatus = requestClockRegs((CLOCK_ID) -1, &pClockRegs);
    EXPECT_EQ(deviceRegisterStatus, DEVICE_CONTEXT_REGISTER_ERROR);

    deviceRegisterStatus = requestClockRegs(CLOCK_GP_0, &pClockRegs);
    EXPECT_EQ(deviceRegisterStatus, DEVICE_CONTEXT_SUCCESS);

    deviceRegisterStatus = requestClockRegs(CLOCK_PWM, &pClockRegs);
    EXPECT_EQ(deviceRegisterStatus, DEVICE_CONTEXT_SUCCESS);
    EXPECT_NE(pClockRegs, nullptr);
    unlockDeviceContext();

    shutdownDeviceContext();

}

TEST(DeviceContextTest, testRequestPWMRegs) {

    DEVICE_CONTEXT_STATUS deviceRegisterStatus;
    struct PWMRegs *pPWMRegs;

    lockDeviceContext();
    deviceRegisterStatus = requestPWMRegs(&pPWMRegs);
    EXPECT_EQ(deviceRegisterStatus, DEVICE_CONTEXT_REGISTER_ERROR);
    unlockDeviceContext();

    setupDeviceContext();

    lockDeviceContext();
    deviceRegisterStatus = requestPWMRegs(nullptr);
    EXPECT_EQ(deviceRegisterStatus, DEVICE_CONTEXT_REGISTER_ERROR);

    deviceRegisterStatus = requestPWMRegs(&pPWMRegs);
    EXPECT_EQ(deviceRegisterStatus, DEVICE_CONTEXT_SUCCESS);
    EXPECT_NE(pPWMRegs, nullptr);
    unlockDeviceContext();

    shutdownDeviceContext();

}

TEST(DeviceContextTest, testRequestI2CRegs) {

    DEVICE_CONTEXT_STATUS deviceRegisterStatus;
    struct I2CRegs *pI2CRegs;

    lockDeviceContext();
    deviceRegisterStatus = requestI2CRegs(&pI2CRegs);
    EXPECT_EQ(deviceRegisterStatus, DEVICE_CONTEXT_REGISTER_ERROR);
    unlockDeviceContext();

    setupDeviceContext();

    lockDeviceContext();
    deviceRegisterStatus = requestI2CRegs(nullptr);
    EXPECT_EQ(deviceRegisterStatus, DEVICE_CONTEXT_REGISTER_ERROR);

    deviceRegisterStatus = requestI2CRegs(&pI2CRegs);
    EXPECT_EQ(deviceRegisterStatus, DEVICE_CONTEXT_SUCCESS);
    EXPECT_NE(pI2CRegs, nullptr);
    unlockDeviceContext();

    shutdownDeviceContext();

}