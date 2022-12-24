#include "devicedriver.h"

void static *gpioBase = NULL;
void static *clockBase = NULL;
void static *pwmBase = NULL;
void static *i2cMasterBase = NULL;

void JNICALL Java_com_comert_gEmbedded_device_nativeinterface_DeviceDriver_setupDeviceDriver
        (JNIEnv *const env, jclass const DeviceDriver) {

    MAPPER_STATUS const gpioMapperStatus = mapBaseRegister (MEMORY_FILE_NAME, BLOCK_SIZE, GPIO_BASE_ADDRESS,
                                                            &gpioBase);
    if (gpioMapperStatus != MAPPER_SUCCESS) {
        throwANewDeviceConfigurationException (env, "GPIO base register mapping failed");
        return;
    }

    MAPPER_STATUS const clockMapperStatus = mapBaseRegister (MEMORY_FILE_NAME, BLOCK_SIZE, CLOCK_BASE_ADDRESS,
                                                             &clockBase);
    if (clockMapperStatus != MAPPER_SUCCESS) {
        throwANewDeviceConfigurationException (env, "Clock base register mapping failed");
        return;
    }

    MAPPER_STATUS const pwmMapperStatus = mapBaseRegister (MEMORY_FILE_NAME, BLOCK_SIZE, PWM_BASE_ADDRESS,
                                                           &pwmBase);
    if (pwmMapperStatus != MAPPER_SUCCESS) {
        throwANewDeviceConfigurationException (env, "PWM base register mapping failed");
        return;
    }

    MAPPER_STATUS const i2cMapperStatus = mapBaseRegister (MEMORY_FILE_NAME, BLOCK_SIZE,
                                                           I2CMASTER_BASE_ADDRESS,
                                                           &i2cMasterBase);
    if (i2cMapperStatus != MAPPER_SUCCESS) {
        throwANewDeviceConfigurationException (env, "I2C master base register mapping failed");
        return;
    }

}

void JNICALL Java_com_comert_gEmbedded_device_nativeinterface_DeviceDriver_shutdownDeviceDriver
        (JNIEnv *const env, jclass const DeviceDriver) {


    MAPPER_STATUS const i2cMapperStatus = unmapBaseRegister (&i2cMasterBase, BLOCK_SIZE);
    if (i2cMapperStatus != MAPPER_SUCCESS) {
        throwANewDeviceConfigurationException (env, "I2C master base register unmapping failed");
        return;
    }

    MAPPER_STATUS const pwmMapperStatus = unmapBaseRegister (&pwmBase, BLOCK_SIZE);
    if (pwmMapperStatus != MAPPER_SUCCESS) {
        throwANewDeviceConfigurationException (env, "PWM base register unmapping failed");
        return;
    }

    MAPPER_STATUS const clockMapperStatus = unmapBaseRegister (&clockBase, BLOCK_SIZE);
    if (clockMapperStatus != MAPPER_SUCCESS) {
        throwANewDeviceConfigurationException (env, "Clock base register unmapping failed");
        return;
    }

    MAPPER_STATUS const gpioMapperStatus = unmapBaseRegister (&gpioBase, BLOCK_SIZE);
    if (gpioMapperStatus != MAPPER_SUCCESS) {
        throwANewDeviceConfigurationException (env, "GPIO base register unmapping failed");
        return;
    }

}

jstring JNICALL Java_com_comert_gEmbedded_device_nativeinterface_DeviceDriver_getDeviceName
        (JNIEnv *const env, jclass const DeviceDriver) {

    return (*env)->NewStringUTF (env, DEVICE_NAME);

}

void *requestGPIOOBase (void) {

    return gpioBase;

}

void *requestClockBase (void) {

    return clockBase;

}

void *requestPWMBase (void) {

    return pwmBase;

}

void *requestI2CMasterBase (void) {

    return i2cMasterBase;

}
