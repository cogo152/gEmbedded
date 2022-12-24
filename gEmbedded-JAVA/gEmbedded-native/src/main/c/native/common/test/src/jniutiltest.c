#include "jniutiltest.h"

JNIEnv static *jniEnv = NULL;
jobject static pin = NULL;
jobject static notInstance = NULL;

int initJniUtilSuite (void) {

    getJNIEnv (&jniEnv);

    jclass const pinClass = (*jniEnv)->FindClass (jniEnv, PIN_CLASS);
    if ((pinClass == NULL) || ((*jniEnv)->ExceptionCheck (jniEnv) == JNI_TRUE)) {
        (*jniEnv)->ExceptionDescribe (jniEnv);
        (*jniEnv)->ExceptionClear (jniEnv);
        return SCENARIO_FAIL;
    } else {
        jfieldID pinFieldId = (*jniEnv)->GetStaticFieldID (jniEnv, pinClass, PIN_NAME, PIN_SIGNATURE);
        if ((pinFieldId == NULL) || ((*jniEnv)->ExceptionCheck (jniEnv) == JNI_TRUE)) {
            (*jniEnv)->ExceptionDescribe (jniEnv);
            (*jniEnv)->ExceptionClear (jniEnv);
            return SCENARIO_FAIL;
        } else {
            pin = (*jniEnv)->GetStaticObjectField (jniEnv, pinClass, pinFieldId);
            if ((pin == NULL) || ((*jniEnv)->ExceptionCheck (jniEnv) == JNI_TRUE)) {
                (*jniEnv)->ExceptionDescribe (jniEnv);
                (*jniEnv)->ExceptionClear (jniEnv);
                return SCENARIO_FAIL;
            }
        }
    }

    jclass const notInstanceClass = (*jniEnv)->FindClass (jniEnv, NOT_INSTANCE_ENUM_CLASS);
    if ((notInstanceClass == NULL) || ((*jniEnv)->ExceptionCheck (jniEnv) == JNI_TRUE)) {
        (*jniEnv)->ExceptionDescribe (jniEnv);
        (*jniEnv)->ExceptionClear (jniEnv);
        return SCENARIO_FAIL;
    } else {
        jfieldID notInstanceFieldId = (*jniEnv)->GetStaticFieldID (jniEnv, notInstanceClass, NOT_INSTANCE_ENUM_NAME,
                                                                   NOT_INSTANCE_ENUM_SIGNATURE);
        if ((notInstanceFieldId == NULL) || ((*jniEnv)->ExceptionCheck (jniEnv) == JNI_TRUE)) {
            (*jniEnv)->ExceptionDescribe (jniEnv);
            (*jniEnv)->ExceptionClear (jniEnv);
            return SCENARIO_FAIL;
        } else {
            notInstance = (*jniEnv)->GetStaticObjectField (jniEnv, notInstanceClass, notInstanceFieldId);
            if ((notInstance == NULL) || ((*jniEnv)->ExceptionCheck (jniEnv) == JNI_TRUE)) {
                (*jniEnv)->ExceptionDescribe (jniEnv);
                (*jniEnv)->ExceptionClear (jniEnv);
                return SCENARIO_FAIL;
            }
        }
    }


    return SCENARIO_SUCCESS;

}

int cleanupJniUtilSuite (void) {

    if ((*jniEnv)->ExceptionCheck (jniEnv) == JNI_TRUE) {
        (*jniEnv)->ExceptionDescribe (jniEnv);
        (*jniEnv)->ExceptionClear (jniEnv);
    }

    jniEnv = NULL;
    pin = NULL;
    notInstance = NULL;

    return SCENARIO_SUCCESS;

}

void testSetupJNIUtil (void) {

    Java_com_comert_gEmbedded_device_nativeinterface_JNIUtil_setupJNIUtil (jniEnv, NULL);

    jboolean exceptionOccurred = (*jniEnv)->ExceptionCheck (jniEnv);
    CU_ASSERT_EQUAL_FATAL(exceptionOccurred, JNI_FALSE)
}

void testThrowANewRuntimeException (void) {

    // ERROR EXIT_FAILURE: if the env is NULL.
    //throwANewRuntimeException(NULL, "Hello World"); // exits process

    // ERROR EXIT_FAILURE: if the message is NULL.
    //throwANewRuntimeException(jniEnv,NULL); // exits process

    throwANewRuntimeException (jniEnv, "***TestRuntimeException***");

    jboolean const exceptionOccurred = (*jniEnv)->ExceptionCheck (jniEnv);
    CU_ASSERT_EQUAL(exceptionOccurred, JNI_TRUE)

    jthrowable exceptionClass = (*jniEnv)->ExceptionOccurred (jniEnv);
    jboolean isInstance = (*jniEnv)->IsInstanceOf (jniEnv, exceptionClass,
                                                   (*jniEnv)->FindClass (jniEnv, RUNTIMEEXCEPTION_CLASS));
    CU_ASSERT_EQUAL(isInstance, JNI_TRUE)

    (*jniEnv)->ExceptionDescribe (jniEnv);
    (*jniEnv)->ExceptionClear (jniEnv);

    CU_ASSERT_EQUAL((*jniEnv)->ExceptionCheck (jniEnv), JNI_FALSE)

}

void testThrowANewDeviceConfigurationException (void) {

    // ERROR EXIT_FAILURE: if the env is NULL.
    //throwANewDeviceConfigurationException(NULL, "Hello World"); // exits process

    // ERROR EXIT_FAILURE: if the message is NULL.
    //throwANewDeviceConfigurationException(jniEnv,NULL); // exits process

    throwANewDeviceConfigurationException (jniEnv, "***TestDeviceConfigurationException***");

    jboolean const exceptionOccurred = (*jniEnv)->ExceptionCheck (jniEnv);
    CU_ASSERT_EQUAL(exceptionOccurred, JNI_TRUE)

    jthrowable exceptionClass = (*jniEnv)->ExceptionOccurred (jniEnv);
    jboolean isInstance = (*jniEnv)->IsInstanceOf (jniEnv, exceptionClass,
                                                   (*jniEnv)->FindClass (jniEnv, DEVICECONFIGURATIONEXCEPTION_CLASS));
    CU_ASSERT_EQUAL(isInstance, JNI_TRUE)

    (*jniEnv)->ExceptionDescribe (jniEnv);
    (*jniEnv)->ExceptionClear (jniEnv);

    CU_ASSERT_EQUAL((*jniEnv)->ExceptionCheck (jniEnv), JNI_FALSE)

}

void testThrowANewDeviceIOException (void) {

    // ERROR EXIT_FAILURE: if the env is NULL.
    //throwANewDeviceIOException(NULL, "Hello World"); // exits process

    // ERROR EXIT_FAILURE: if the message is NULL.
    //throwANewDeviceIOException(jniEnv,NULL); // exits process

    throwANewDeviceIOException (jniEnv, "***TestDeviceIOException***");

    jboolean const exceptionOccurred = (*jniEnv)->ExceptionCheck (jniEnv);
    CU_ASSERT_EQUAL(exceptionOccurred, JNI_TRUE)

    jthrowable exceptionClass = (*jniEnv)->ExceptionOccurred (jniEnv);
    jboolean isInstance = (*jniEnv)->IsInstanceOf (jniEnv, exceptionClass,
                                                   (*jniEnv)->FindClass (jniEnv, DEVICEIOEXCEPTION_CLASS));
    CU_ASSERT_EQUAL(isInstance, JNI_TRUE)

    (*jniEnv)->ExceptionDescribe (jniEnv);
    (*jniEnv)->ExceptionClear (jniEnv);

    CU_ASSERT_EQUAL((*jniEnv)->ExceptionCheck (jniEnv), JNI_FALSE)

}

void testGetEnumDigit (void) {

    jbyte digitValue = -1;
    JNI_STATUS status;

    // JNI_ERROR : if the env is NULL.
    status = getEnumDigit (NULL, pin, NULL);
    CU_ASSERT_EQUAL(status, JNI_ERROR)

    // JNI_ERROR : if the enumObject is NULL.
    status = getEnumDigit (jniEnv, NULL, NULL);
    CU_ASSERT_EQUAL(status, JNI_ERROR)

    // JNI_ERROR : if the enum does not implement DeviceConstant interface.
    status = getEnumDigit (jniEnv, notInstance, &digitValue);
    CU_ASSERT_EQUAL(status, JNI_ERROR)

    status = getEnumDigit (jniEnv, pin, &digitValue);
    CU_ASSERT_EQUAL(status, JNI_SUCCESS)
    CU_ASSERT_EQUAL(digitValue, PIN_DIGIT)

}

void testGetEnumText (void) {

    char text[sizeof PIN_TEXT];
    JNI_STATUS status;

    // JNI_ERROR : if the env is NULL.
    status = getEnumText (NULL, pin, text, sizeof (text));
    CU_ASSERT_EQUAL(status, JNI_ERROR)

    // JNI_ERROR : if the enumObject is NULL.
    status = getEnumText (jniEnv, NULL, text, sizeof (text));
    CU_ASSERT_EQUAL(status, JNI_ERROR)

    // JNI_ERROR : if the textToReturn is a NULL char array.
    status = getEnumText (jniEnv, pin, NULL, sizeof (text));
    CU_ASSERT_EQUAL(status, JNI_ERROR)

    // JNI_ERROR : if the enum does not implement DeviceConstant interface.
    status = getEnumText (jniEnv, notInstance, text, sizeof (text));
    CU_ASSERT_EQUAL(status, JNI_ERROR)

    // JNI_ERROR : if the textToReturnSize is less than string size.
    status = getEnumText (jniEnv, pin, text, sizeof (text) - 2); // nil character
    CU_ASSERT_EQUAL(status, JNI_ERROR)

    status = getEnumText (jniEnv, pin, text, sizeof (text));
    CU_ASSERT_EQUAL(status, JNI_SUCCESS)
    CU_ASSERT_STRING_EQUAL(text, PIN_TEXT)

}

void testGetEnum (void) {

    jobject pinToGet;
    JNI_STATUS status;

    // JNI_ERROR : if the env is NULL.
    status = getEnum (NULL, PIN_CLASS, PIN_NAME, PIN_SIGNATURE, &pinToGet);
    CU_ASSERT_EQUAL(status, JNI_ERROR)

    // JNI_ERROR : if the fullyQualifiedEnumClassName is NULL.
    status = getEnum (jniEnv, NULL, PIN_NAME, PIN_SIGNATURE, &pinToGet);
    CU_ASSERT_EQUAL(status, JNI_ERROR)

    // JNI_ERROR : if the enumName is NULL.
    status = getEnum (jniEnv, PIN_CLASS, NULL, PIN_SIGNATURE, &pinToGet);
    CU_ASSERT_EQUAL(status, JNI_ERROR)

    // JNI_ERROR : if the enumSignature is NULL.
    status = getEnum (jniEnv, PIN_CLASS, PIN_NAME, NULL, &pinToGet);
    CU_ASSERT_EQUAL(status, JNI_ERROR)

    // JNI_ERROR : if the enumToReturn is NULL.
    status = getEnum (jniEnv, PIN_CLASS, PIN_NAME, PIN_SIGNATURE, NULL);
    CU_ASSERT_EQUAL(status, JNI_ERROR)

    // JNI_ERROR : if the fullyQualifiedEnumClassName is invalid.
    status = getEnum (jniEnv, INVALID_PIN_CLASS, PIN_NAME, PIN_SIGNATURE, NULL);
    CU_ASSERT_EQUAL(status, JNI_ERROR)
    if ((*jniEnv)->ExceptionCheck (jniEnv) == JNI_TRUE) {
        (*jniEnv)->ExceptionClear (jniEnv);
    }

    // JNI_ERROR : if the enum does not implement DeviceConstant interface.
    status = getEnum (jniEnv, NOT_INSTANCE_ENUM_CLASS, NOT_INSTANCE_ENUM_NAME, NOT_INSTANCE_ENUM_SIGNATURE, &pinToGet);
    CU_ASSERT_EQUAL(status, JNI_ERROR)
    if ((*jniEnv)->ExceptionCheck (jniEnv) == JNI_TRUE) {
        (*jniEnv)->ExceptionClear (jniEnv);
    }

    // JNI_ERROR : if the enumName is invalid.
    status = getEnum (jniEnv, PIN_CLASS, INVALID_PIN_NAME, PIN_SIGNATURE, &pinToGet);
    CU_ASSERT_EQUAL(status, JNI_ERROR)
    if ((*jniEnv)->ExceptionCheck (jniEnv) == JNI_TRUE) {
        (*jniEnv)->ExceptionClear (jniEnv);
    }

    // JNI_ERROR : if the enumSignature is invalid.
    status = getEnum (jniEnv, PIN_CLASS, PIN_NAME, INVALID_PIN_SIGNATURE, &pinToGet);
    CU_ASSERT_EQUAL(status, JNI_ERROR)
    if ((*jniEnv)->ExceptionCheck (jniEnv) == JNI_TRUE) {
        (*jniEnv)->ExceptionClear (jniEnv);
    }

    status = getEnum (jniEnv, PIN_CLASS, PIN_NAME, PIN_SIGNATURE, &pinToGet);
    CU_ASSERT_EQUAL(status, JNI_SUCCESS)
    jboolean isSameObject = (*jniEnv)->IsSameObject (jniEnv, pin, pinToGet);
    CU_ASSERT_TRUE(isSameObject);

}

void testShutdownJNIUtil (void) {

    Java_com_comert_gEmbedded_device_nativeinterface_JNIUtil_shutdownJNIUtil (jniEnv, NULL);

    jboolean exceptionOccurred = (*jniEnv)->ExceptionCheck (jniEnv);
    CU_ASSERT_EQUAL_FATAL(exceptionOccurred, JNI_FALSE)

}