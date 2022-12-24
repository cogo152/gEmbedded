/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_comert_gEmbedded_device_nativeinterface_I2CMasterDriver */

#ifndef _Included_com_comert_gEmbedded_device_nativeinterface_I2CMasterDriver
#define _Included_com_comert_gEmbedded_device_nativeinterface_I2CMasterDriver
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_comert_gEmbedded_device_nativeinterface_I2CMasterDriver
 * Method:    setupI2CMasterDriver
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_comert_gEmbedded_device_nativeinterface_I2CMasterDriver_setupI2CMasterDriver
  (JNIEnv *, jclass);

/*
 * Class:     com_comert_gEmbedded_device_nativeinterface_I2CMasterDriver
 * Method:    shutdownI2CMasterDriver
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_comert_gEmbedded_device_nativeinterface_I2CMasterDriver_shutdownI2CMasterDriver
  (JNIEnv *, jclass);

/*
 * Class:     com_comert_gEmbedded_device_nativeinterface_I2CMasterDriver
 * Method:    configureMaster
 * Signature: (Lcom/comert/gEmbedded/api/device/i2c/I2CBus;IILcom/comert/gEmbedded/api/device/Pin;Lcom/comert/gEmbedded/api/device/Pin;II[B[I)V
 */
JNIEXPORT void JNICALL Java_com_comert_gEmbedded_device_nativeinterface_I2CMasterDriver_configureMaster
  (JNIEnv *, jclass, jobject, jint, jint, jobject, jobject, jint, jint, jbyteArray, jintArray);

/*
 * Class:     com_comert_gEmbedded_device_nativeinterface_I2CMasterDriver
 * Method:    getI2CBusRegisterSelector
 * Signature: (B)B
 */
JNIEXPORT jbyte JNICALL Java_com_comert_gEmbedded_device_nativeinterface_I2CMasterDriver_getI2CBusRegisterSelector
  (JNIEnv *, jclass, jbyte);

/*
 * Class:     com_comert_gEmbedded_device_nativeinterface_I2CMasterDriver
 * Method:    sendData
 * Signature: (BBI)V
 */
JNIEXPORT void JNICALL Java_com_comert_gEmbedded_device_nativeinterface_I2CMasterDriver_sendData
  (JNIEnv *, jclass, jbyte, jbyte, jint);

/*
 * Class:     com_comert_gEmbedded_device_nativeinterface_I2CMasterDriver
 * Method:    sendDataWithException
 * Signature: (BBI)V
 */
JNIEXPORT void JNICALL Java_com_comert_gEmbedded_device_nativeinterface_I2CMasterDriver_sendDataWithException
  (JNIEnv *, jclass, jbyte, jbyte, jint);

/*
 * Class:     com_comert_gEmbedded_device_nativeinterface_I2CMasterDriver
 * Method:    receiveData
 * Signature: (BBI)V
 */
JNIEXPORT void JNICALL Java_com_comert_gEmbedded_device_nativeinterface_I2CMasterDriver_receiveData
  (JNIEnv *, jclass, jbyte, jbyte, jint);

/*
 * Class:     com_comert_gEmbedded_device_nativeinterface_I2CMasterDriver
 * Method:    receiveDataWithException
 * Signature: (BBI)V
 */
JNIEXPORT void JNICALL Java_com_comert_gEmbedded_device_nativeinterface_I2CMasterDriver_receiveDataWithException
  (JNIEnv *, jclass, jbyte, jbyte, jint);

/*
 * Class:     com_comert_gEmbedded_device_nativeinterface_I2CMasterDriver
 * Method:    sendAndReceiveData
 * Signature: (BBII)V
 */
JNIEXPORT void JNICALL Java_com_comert_gEmbedded_device_nativeinterface_I2CMasterDriver_sendAndReceiveData
  (JNIEnv *, jclass, jbyte, jbyte, jint, jint);

/*
 * Class:     com_comert_gEmbedded_device_nativeinterface_I2CMasterDriver
 * Method:    sendAndReceiveDataWithException
 * Signature: (BBII)V
 */
JNIEXPORT void JNICALL Java_com_comert_gEmbedded_device_nativeinterface_I2CMasterDriver_sendAndReceiveDataWithException
  (JNIEnv *, jclass, jbyte, jbyte, jint, jint);

#ifdef __cplusplus
}
#endif
#endif