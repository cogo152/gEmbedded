#ifndef DEVICEDRIVERTEST_H
#define DEVICEDRIVERTEST_H

#include "devicedriver.h"

#include "commontest.h"
#include "jniutil.h"
#include "mapper.h"
#include "jvm.h"

#define SOC_RANGE_FILE          ("/proc/device-tree/soc/ranges")
#define PERIPHERAL_BASE_OFFSET  (8)

#define PAGE_LENGTH             (8)
#define PAGE_SHIFT              (12)

int initDeviceDriverSuite (void);

int cleanupDeviceDriverSuite (void);

void testSetupDeviceDriver (void);

void testGetDeviceName (void);

void testRequestGPIOOBase (void);

void testRequestClockBase (void);

void testRequestPWMBase (void);

void testRequestI2CMasterBase (void);

void testShutdownDeviceDriver (void);

#define DEVICEDRIVER_TEST \
    CU_TestInfo deviceDriverTests[] = { \
    { "testSetupDeviceDriver", testSetupDeviceDriver }, \
    { "testGetDeviceName", testGetDeviceName }, \
    { "testRequestGPIOOBase", testRequestGPIOOBase }, \
    { "testRequestClockBase", testRequestClockBase }, \
    { "testRequestPWMBase", testRequestPWMBase }, \
    { "testRequestI2CMasterBase", testRequestI2CMasterBase },  \
    { "testShutdownDeviceDriver", testShutdownDeviceDriver },   \
    CU_TEST_INFO_NULL }; \

#endif //DEVICEDRIVERTEST_H
