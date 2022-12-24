#ifndef JNIUTIL_H
#define JNIUTIL_H

#include "common.h"
#include "com_comert_gEmbedded_device_nativeinterface_JNIUtil.h"

#include <jni.h>
#include <stdlib.h>

#define RUNTIMEEXCEPTION_CLASS              ("java/lang/RuntimeException")
#define DEVICECONFIGURATIONEXCEPTION_CLASS  ("com/comert/gEmbedded/api/device/DeviceConfigurationException")
#define DEVICEIOEXCEPTION_CLASS             ("com/comert/gEmbedded/api/device/DeviceIOException")

#define DEVICECONSTANT_CLASS                ("com/comert/gEmbedded/api/device/DeviceConstant")
#define DIGIT_METHOD_NAME                   ("getDigit")
#define DIGIT_METHOD_SIGNATURE              ("()B")
#define TEXT_METHOD_NAME                    ("getText")
#define TEXT_METHOD_SIGNATURE               ("()Ljava/lang/String;")
#define LARGEST_TEXT_SIZE (50)

typedef enum {
    JNI_SUCCESS = 0,
    JNI_ERROR = 1
} JNI_STATUS;

void throwANewRuntimeException (JNIEnv *env, const char *message);

void throwANewDeviceConfigurationException (JNIEnv *env, const char *message);

void throwANewDeviceIOException (JNIEnv *env, const char *message);

// Only the enums which implements DeviceConstant interface
JNI_STATUS getEnumDigit (JNIEnv *env, jobject enumObject, jbyte *digitToReturn);

// Only the enums which implements DeviceConstant interface
JNI_STATUS getEnumText (JNIEnv *env, jobject enumObject, char *textToReturn, uint8_t textToReturnSize);

// Only the enums which implements DeviceConstant interface
JNI_STATUS getEnum(JNIEnv *env, const char *fullyQualifiedEnumClassName, const char *enumName, const char *enumSignature, jobject *enumToReturn );

#endif //JNIUTIL_H
