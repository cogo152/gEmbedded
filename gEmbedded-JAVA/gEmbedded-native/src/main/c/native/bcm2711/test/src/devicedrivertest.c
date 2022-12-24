#include <unistd.h>
#include <zconf.h>
#include "devicedrivertest.h"
#include "jvm.h"

JNIEnv static *jniEnv = NULL;

int initDeviceDriverSuite (void) {

    getJNIEnv (&jniEnv);

    Java_com_comert_gEmbedded_device_nativeinterface_JNIUtil_setupJNIUtil (jniEnv, NULL);
    if ((*jniEnv)->ExceptionCheck (jniEnv) == JNI_TRUE) {
        (*jniEnv)->ExceptionDescribe (jniEnv);
        (*jniEnv)->ExceptionClear (jniEnv);
        return SCENARIO_FAIL;
    }

    return SCENARIO_SUCCESS;

}

int cleanupDeviceDriverSuite (void) {

    Java_com_comert_gEmbedded_device_nativeinterface_JNIUtil_shutdownJNIUtil (jniEnv, NULL);
    if ((*jniEnv)->ExceptionCheck (jniEnv) == JNI_TRUE) {
        (*jniEnv)->ExceptionDescribe (jniEnv);
        (*jniEnv)->ExceptionClear (jniEnv);
        return SCENARIO_FAIL;
    }

    jniEnv = NULL;

    return SCENARIO_SUCCESS;

}

void testSetupDeviceDriver (void) {

    off_t peripheralBase;

    FILE *const fp = fopen (SOC_RANGE_FILE, "rb");
    if (fp == NULL) {
        fclose (fp);
        CU_FAIL_FATAL("SOC_RANGE_FILE opening failed")
        return;
    }

    int const seekStatus = fseek (fp, PERIPHERAL_BASE_OFFSET, SEEK_SET);
    if (seekStatus != 0) {
        fclose (fp);
        CU_FAIL_FATAL("fseek failed")
        return;
    }

    uint8_t buf[4];
    uint32_t const readStatus = fread (buf, 1, sizeof buf, fp);
    if (readStatus != sizeof buf) {
        fclose (fp);
        CU_FAIL_FATAL("freed failed")
        return;
    }

    fclose (fp);

    peripheralBase = buf[0] << 24 | buf[1] << 16 | buf[2] << 8 | buf[3] << 0;
    CU_ASSERT_EQUAL_FATAL(peripheralBase, PERIPHERAL_BASE_ADDRESS);

    Java_com_comert_gEmbedded_device_nativeinterface_DeviceDriver_setupDeviceDriver (jniEnv, NULL);

    jboolean const exceptionStatus = (*jniEnv)->ExceptionCheck (jniEnv);

    CU_ASSERT_EQUAL(exceptionStatus, JNI_FALSE);

    if (exceptionStatus == JNI_TRUE) {
        (*jniEnv)->ExceptionDescribe (jniEnv);
        (*jniEnv)->ExceptionClear (jniEnv);
        CU_FAIL("DeviceDriver setup failed.")
    }

}

void testGetDeviceName (void) {

    char deviceName[sizeof DEVICE_NAME];

    jstring deviceNameString = Java_com_comert_gEmbedded_device_nativeinterface_DeviceDriver_getDeviceName (jniEnv,
                                                                                                            NULL);
    CU_ASSERT_PTR_NOT_NULL(deviceNameString);

    jsize stringSize = (*jniEnv)->GetStringUTFLength (jniEnv, deviceNameString);
    (*jniEnv)->GetStringUTFRegion (jniEnv, deviceNameString, 0, stringSize, deviceName);
    CU_ASSERT_STRING_EQUAL(deviceName, DEVICE_NAME);

}

void testRequestGPIOOBase (void) {

    void *ptr = requestGPIOOBase ();
    CU_ASSERT_PTR_NOT_NULL(ptr);

}

void testRequestClockBase (void) {

    void *ptr = requestClockBase ();
    CU_ASSERT_PTR_NOT_NULL(ptr);

}

void testRequestPWMBase (void) {

    void *ptr = requestPWMBase ();
    CU_ASSERT_PTR_NOT_NULL(ptr);

}

void testRequestI2CMasterBase (void) {

    void *ptr = requestI2CMasterBase ();
    CU_ASSERT_PTR_NOT_NULL(ptr);

}

void testShutdownDeviceDriver (void) {

    Java_com_comert_gEmbedded_device_nativeinterface_JNIUtil_shutdownJNIUtil (jniEnv, NULL);

    jboolean exceptionStatus = (*jniEnv)->ExceptionCheck (jniEnv);

    CU_ASSERT_EQUAL(exceptionStatus, JNI_FALSE);

    if (exceptionStatus == JNI_TRUE) {
        (*jniEnv)->ExceptionDescribe (jniEnv);
        (*jniEnv)->ExceptionClear (jniEnv);
        CU_FAIL("DeviceDriver shutdown failed.")
    }

}