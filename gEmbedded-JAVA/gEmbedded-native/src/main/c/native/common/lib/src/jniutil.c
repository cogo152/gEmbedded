#include "jniutil.h"

jclass static DeviceConfigurationException = NULL;
jclass static DeviceIOException = NULL;

jclass static DeviceConstant = NULL;
jmethodID static digitMethodId = NULL;
jmethodID static textMethodId = NULL;

void JNICALL Java_com_comert_gEmbedded_device_nativeinterface_JNIUtil_setupJNIUtil
        (JNIEnv *const env, jclass const JNIUtil) {

    jclass const _DeviceConfigurationException = (*env)->FindClass (env, DEVICECONFIGURATIONEXCEPTION_CLASS);
    if ((_DeviceConfigurationException == NULL) || ((*env)->ExceptionCheck (env) == JNI_TRUE)) {
        goto Return_RuntimeException;
    }

    DeviceConfigurationException = (*env)->NewGlobalRef (env, _DeviceConfigurationException);
    if ((DeviceConfigurationException == NULL) || ((*env)->ExceptionCheck (env) == JNI_TRUE)) {
        goto Return_RuntimeException;
    }

    jclass const _DeviceIOException = (*env)->FindClass (env, DEVICEIOEXCEPTION_CLASS);
    if ((_DeviceIOException == NULL) || ((*env)->ExceptionCheck (env) == JNI_TRUE)) {
        goto Return_RuntimeException;
    }

    DeviceIOException = (*env)->NewGlobalRef (env, _DeviceIOException);
    if ((DeviceIOException == NULL) || ((*env)->ExceptionCheck (env) == JNI_TRUE)) {
        goto Return_RuntimeException;
    }

    jclass const _DeviceConstant = (*env)->FindClass (env, DEVICECONSTANT_CLASS);
    if ((_DeviceConstant == NULL) || ((*env)->ExceptionCheck (env) == JNI_TRUE)) {
        goto Return_RuntimeException;
    }

    DeviceConstant = (*env)->NewGlobalRef (env, _DeviceConstant);
    if ((DeviceConstant == NULL) || ((*env)->ExceptionCheck (env) == JNI_TRUE)) {
        goto Return_RuntimeException;
    }

    digitMethodId = (*env)->GetMethodID (env, DeviceConstant, DIGIT_METHOD_NAME, DIGIT_METHOD_SIGNATURE);
    if ((digitMethodId == NULL) || ((*env)->ExceptionCheck (env) == JNI_TRUE)) {
        goto Return_RuntimeException;
    }

    textMethodId = (*env)->GetMethodID (env, DeviceConstant, TEXT_METHOD_NAME, TEXT_METHOD_SIGNATURE);
    if ((textMethodId == NULL) || ((*env)->ExceptionCheck (env) == JNI_TRUE)) {
        goto Return_RuntimeException;
    }

    return;

    Return_RuntimeException:
    {
        throwANewRuntimeException (env, "JNIUtil setup failed");
        return;
    }

}

void JNICALL Java_com_comert_gEmbedded_device_nativeinterface_JNIUtil_shutdownJNIUtil
        (JNIEnv *const env, jclass const JNIUtil) {

    (*env)->DeleteGlobalRef (env, DeviceConstant);
    if (((*env)->ExceptionCheck (env) == JNI_TRUE)) {
        goto Return_RuntimeException;
    }

    (*env)->DeleteGlobalRef (env, DeviceIOException);
    if (((*env)->ExceptionCheck (env) == JNI_TRUE)) {
        goto Return_RuntimeException;
    }

    (*env)->DeleteGlobalRef (env, DeviceConfigurationException);
    if (((*env)->ExceptionCheck (env) == JNI_TRUE)) {
        goto Return_RuntimeException;
    }

    return;

    Return_RuntimeException:
    {
        throwANewRuntimeException (env, "JNIUtil shutdown failed");
        return;
    }

}

void throwANewRuntimeException (JNIEnv *const env, const char *const message) {

    if ((env == NULL) || (message == NULL)) {
        goto Exit_Process_Failure;
    }

    // check if the exception is not logical (e.g. NULL return value) but JVM exception.
    if ((*env)->ExceptionCheck (env) == JNI_TRUE) {
        (*env)->ExceptionDescribe (env);
        (*env)->ExceptionClear (env);
    }

    jclass const RuntimeException = (*env)->FindClass (env, RUNTIMEEXCEPTION_CLASS);
    if ((RuntimeException == NULL) || ((*env)->ExceptionCheck (env) == JNI_TRUE)) {
        goto Exit_Process_Failure;
    }

    jint const exceptionSuccess = (*env)->ThrowNew (env, RuntimeException, message);
    if (exceptionSuccess != JNI_OK) {
        goto Exit_Process_Failure;
    }

    return;

    Exit_Process_Failure :
    {
        printf ("FATAL ERROR : file::jniutil.c function::throwANewRuntimeException\n");
        exit (EXIT_FAILURE);
    }

}

void throwANewDeviceConfigurationException (JNIEnv *const env, const char *const message) {

    if ((env == NULL) || (message == NULL)) {
        goto Exit_Process_Failure;
    }

    if ((*env)->ExceptionCheck (env) == JNI_TRUE) {
        (*env)->ExceptionDescribe (env);
        (*env)->ExceptionClear (env);
    }

    jint const exceptionSuccess = (*env)->ThrowNew (env, DeviceConfigurationException, message);
    if (exceptionSuccess != JNI_OK) {
        throwANewRuntimeException (env, "DeviceConfigurationException could not be thrown");
    }

    return;

    Exit_Process_Failure :
    {
        printf ("FATAL ERROR : file::jniutil.c function::throwANewDeviceConfigurationException\n");
        exit (EXIT_FAILURE);
    }

}

void throwANewDeviceIOException (JNIEnv *const env, const char *const message) {

    if ((env == NULL) || (message == NULL)) {
        goto Exit_Process_Failure;
    }

    if ((*env)->ExceptionCheck (env) == JNI_TRUE) {
        (*env)->ExceptionDescribe (env);
        (*env)->ExceptionClear (env);
    }

    jint const exceptionSuccess = (*env)->ThrowNew (env, DeviceIOException, message);
    if (exceptionSuccess != JNI_OK) {
        throwANewRuntimeException (env, "DeviceIOException could not be thrown");
    }

    return;

    Exit_Process_Failure :
    {
        printf ("FATAL ERROR : file::jniutil.c function::throwANewDeviceIOException\n");
        exit (EXIT_FAILURE);
    }

}

JNI_STATUS getEnumDigit (JNIEnv *const env, jobject enumObject, jbyte *const digitToReturn) {

    if ((env == NULL) || (enumObject == NULL)) {
        return JNI_ERROR;
    }

    jboolean const isInstance = (*env)->IsInstanceOf (env, enumObject, DeviceConstant);
    if (isInstance == JNI_FALSE) {
        return JNI_ERROR;
    }

    *digitToReturn = (*env)->CallByteMethod (env, enumObject, digitMethodId);
    if ((*env)->ExceptionCheck (env) == JNI_TRUE) {
        return JNI_ERROR;
    }

    return JNI_SUCCESS;

}

JNI_STATUS
getEnumText (JNIEnv *const env, jobject enumObject, char *const textToReturn, uint8_t const textToReturnSize) {

    if ((env == NULL) || (enumObject == NULL) || (textToReturn == NULL)) {
        return JNI_ERROR;
    }

    jboolean const isInstance = (*env)->IsInstanceOf (env, enumObject, DeviceConstant);
    if (isInstance == JNI_FALSE) {
        return JNI_ERROR;
    }

    jstring const string = (*env)->CallObjectMethod (env, enumObject, textMethodId);
    if ((string == NULL) || (*env)->ExceptionCheck (env) == JNI_TRUE) {
        return JNI_ERROR;
    }

    jsize const stringSize = (*env)->GetStringLength (env, string);
    if (textToReturnSize < stringSize) {
        return JNI_ERROR;
    }

    (*env)->GetStringUTFRegion (env, string, 0, stringSize, textToReturn);
    if ((*env)->ExceptionCheck (env) == JNI_TRUE) {
        return JNI_ERROR;
    }

    return JNI_SUCCESS;

}

JNI_STATUS
getEnum (JNIEnv *const env, const char *const fullyQualifiedEnumClassName, const char *const enumName,
         const char *const enumSignature,
         jobject *const enumToReturn) {

    if ((env == NULL) || (fullyQualifiedEnumClassName == NULL) || (enumName == NULL) || (enumSignature == NULL) ||
        (enumToReturn == NULL)) {
        return JNI_ERROR;
    }

    jclass const pinClass = (*env)->FindClass (env, fullyQualifiedEnumClassName);
    if ((pinClass == NULL) || ((*env)->ExceptionCheck (env) == JNI_TRUE)) {
        return JNI_ERROR;
    }

    jboolean const isAssignable = (*env)->IsAssignableFrom (env, pinClass, DeviceConstant);
    if (isAssignable == JNI_FALSE) {
        return JNI_ERROR;
    }

    jfieldID pinFieldId = (*env)->GetStaticFieldID (env, pinClass, enumName, enumSignature);
    if ((pinFieldId == NULL) || ((*env)->ExceptionCheck (env) == JNI_TRUE)) {
        return JNI_ERROR;
    }

    jobject pin = (*env)->GetStaticObjectField (env, pinClass, pinFieldId);
    if ((pin == NULL) || ((*env)->ExceptionCheck (env) == JNI_TRUE)) {
        return JNI_ERROR;
    }

    *enumToReturn = pin;

    return JNI_SUCCESS;

}
