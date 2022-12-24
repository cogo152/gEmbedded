#ifndef JNIUTILTEST_H
#define JNIUTILTEST_H

#include "com_comert_gEmbedded_device_nativeinterface_JNIUtil.h"
#include "jniutil.h"

#include "commontest.h"
#include "jvm.h"

#define PIN_CLASS                   ("com/comert/gEmbedded/api/device/Pin")
#define PIN_NAME                    ("PIN_27")
#define PIN_SIGNATURE               ("Lcom/comert/gEmbedded/api/device/Pin;")
#define PIN_DIGIT                   (27)
#define PIN_TEXT                    ("Twenty seven")

#define INVALID_PIN_CLASS           ("com/comert/gEmbedded/api/device/InvalidPin")
#define INVALID_PIN_NAME            ("PIN_INVALID")
#define INVALID_PIN_SIGNATURE       ("Lcom/comert/gEmbedded/api/device/InvalidPin;")

#define NOT_INSTANCE_ENUM_CLASS     ("java/lang/Thread$State")
#define NOT_INSTANCE_ENUM_NAME      ("NEW")
#define NOT_INSTANCE_ENUM_SIGNATURE ("Ljava/lang/Thread$State;")

int initJniUtilSuite (void);

int cleanupJniUtilSuite (void);

void testSetupJNIUtil (void);

void testThrowANewRuntimeException (void);

void testThrowANewDeviceConfigurationException (void);

void testThrowANewDeviceIOException (void);

void testGetEnumDigit (void);

void testGetEnumText (void);

void testGetEnum(void );

void testShutdownJNIUtil (void);

#define JNIUTIL_TEST \
    CU_TestInfo jniUtilTests[] = { \
    { "testSetupJNIUtil", testSetupJNIUtil }, \
    { "testThrowANewRuntimeException", testThrowANewRuntimeException }, \
    { "testThrowANewDeviceConfigurationException", testThrowANewDeviceConfigurationException }, \
    { "testThrowANewDeviceIOException", testThrowANewDeviceIOException }, \
    { "testGetEnumDigit", testGetEnumDigit }, \
    { "testGetEnumText", testGetEnumText },                             \
    { "testGetEnum", testGetEnum },   \
    { "testShutdownJNIUtil", testShutdownJNIUtil }, \
    CU_TEST_INFO_NULL }; \

#endif //JNIUTILTEST_H
