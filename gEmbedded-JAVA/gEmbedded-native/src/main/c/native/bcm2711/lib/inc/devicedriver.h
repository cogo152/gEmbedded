#ifndef DEVICEDRIVER_H
#define DEVICEDRIVER_H

#include "com_comert_gEmbedded_device_nativeinterface_DeviceDriver.h"

#include "common.h"
#include "jniutil.h"
#include "mapper.h"

#include <unistd.h>

#define DEVICE_NAME             ("RaspberryPi-4B")
#define CORE_CLOCK_SPEED        (1500000000U)

#define MEMORY_FILE_NAME        ("/dev/mem")
#define PERIPHERAL_BASE_ADDRESS (0xFE000000)
#define BLOCK_SIZE              (0X1000)

#define GPIO_BASE_ADDRESS       (PERIPHERAL_BASE_ADDRESS+0x00200000)
#define CLOCK_BASE_ADDRESS      (PERIPHERAL_BASE_ADDRESS+0x00101000)
#define PWM_BASE_ADDRESS        (PERIPHERAL_BASE_ADDRESS+0x0020c000)
#define I2CMASTER_BASE_ADDRESS  (PERIPHERAL_BASE_ADDRESS+0x804000)

void *requestGPIOOBase (void);

void *requestClockBase (void);

void *requestPWMBase (void);

void *requestI2CMasterBase (void);

#endif //DEVICEDRIVER_H
