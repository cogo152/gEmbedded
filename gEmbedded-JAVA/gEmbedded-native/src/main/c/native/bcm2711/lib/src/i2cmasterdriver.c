#include "com_comert_gEmbedded_device_nativeinterface_I2CMasterDriver.h"
#include "i2cmasterdriver.h"
#include "jniutil.h"

#include "devicedriver.h"
#include "gpiodriver.h"

uintptr_t static volatile *C;
uintptr_t static volatile *S;
uintptr_t static volatile *DLEN;
uintptr_t static volatile *A;
uintptr_t static volatile *FIFO;
uintptr_t static volatile *DIV;
uintptr_t static volatile *DEL;
uintptr_t static volatile *CLKT;
jbyteArray static writeBufferArray;
uint8_t static volatile *writeBuffer;
jintArray static readBufferArray;
jint static volatile *readBuffer;

void JNICALL Java_com_comert_gEmbedded_device_nativeinterface_I2CMasterDriver_setupI2CMasterDriver
        (JNIEnv *env, jclass I2CMasterDriver) {

    uintptr_t *i2cMasterBase = (uintptr_t *) requestI2CMasterBase ();

    C = i2cMasterBase + I2C_C_OFFSET;
    S = i2cMasterBase + I2C_S_OFFSET;
    DLEN = i2cMasterBase + I2C_DLEN_OFFSET;
    A = i2cMasterBase + I2C_A_OFFSET;
    FIFO = i2cMasterBase + I2C_FIFO_OFFSET;
    DIV = i2cMasterBase + I2C_DIV_OFFSET;
    DEL = i2cMasterBase + I2C_DEL_OFFSET;
    CLKT = i2cMasterBase + I2C_CLKT_OFFSET;

}

void JNICALL Java_com_comert_gEmbedded_device_nativeinterface_I2CMasterDriver_shutdownI2CMasterDriver
        (JNIEnv *env, jclass I2CMasterDriver) {

    C = NULL;
    S = NULL;
    DLEN = NULL;
    A = NULL;
    FIFO = NULL;
    DIV = NULL;
    DEL = NULL;
    CLKT = NULL;

    (*env)->ReleasePrimitiveArrayCritical (env, writeBufferArray, (void *) writeBuffer, 0);
    (*env)->DeleteGlobalRef (env, writeBufferArray);

    (*env)->ReleasePrimitiveArrayCritical (env, readBufferArray, (void *) readBuffer, 0);
    (*env)->DeleteGlobalRef (env, readBufferArray);


}

void JNICALL Java_com_comert_gEmbedded_device_nativeinterface_I2CMasterDriver_configureMaster
        (JNIEnv *env,
         jclass I2CMasterDriver,
         jobject i2cBus,
         jint busClockInHertz,
         jint slaveWaitClockTimeout,
         jobject sdaPin,
         jobject sclPin,
         jint sclFallingEdgeClockDelay,
         jint sclRisingEdgeClockDelay,
         jbyteArray _writeBufferArray,
         jintArray _readBufferArray) {

    JNI_STATUS jniStatusI2CBus, jniStatusSDAPin, jniStatusSCLPin;
    jbyte _i2cBus, _sdaPin, _sclPin;

    jniStatusI2CBus = getEnumDigit (env, i2cBus, &_i2cBus);
    if (jniStatusI2CBus != JNI_SUCCESS) {
        throwANewDeviceConfigurationException (env, "I2C bus configuration failed");
        return;
    }

    jniStatusSDAPin = getEnumDigit (env, sdaPin, &_sdaPin);
    if (jniStatusSDAPin != JNI_SUCCESS) {
        throwANewDeviceConfigurationException (env, "I2C bus sda pin configuration failed");
        return;
    }

    jniStatusSCLPin = getEnumDigit (env, sclPin, &_sclPin);
    if (jniStatusSCLPin != JNI_SUCCESS) {
        throwANewDeviceConfigurationException (env, "I2C bus scl pin configuration failed");
        return;
    }


    if (_i2cBus == 1) {

        if ((_sdaPin == 2) && (_sclPin == 3)) {
            configurePinFunction (_sdaPin, PIN_FUNCTION_ALT_0);
            configurePinFunction (_sclPin, PIN_FUNCTION_ALT_0);
        } else {
            throwANewDeviceConfigurationException (env, "sda or scl pin are not supported");
            return;
        }
    } else {
        throwANewDeviceConfigurationException (env, "i2c bus is not supported");
        return;
    }

    // primitive exception check

    *DIV = CORE_CLOCK_SPEED / busClockInHertz;
    *CLKT = slaveWaitClockTimeout;
    *DEL = I2C_DEL_DIV(sclFallingEdgeClockDelay, sclRisingEdgeClockDelay);

    writeBufferArray = (*env)->NewGlobalRef (env, _writeBufferArray);
    writeBuffer = (uint8_t *) (*env)->GetPrimitiveArrayCritical (env, _writeBufferArray, 0);
    readBufferArray = (*env)->NewGlobalRef (env, _readBufferArray);
    readBuffer = (*env)->GetPrimitiveArrayCritical (env, _readBufferArray, 0);

}

jbyte JNICALL Java_com_comert_gEmbedded_device_nativeinterface_I2CMasterDriver_getI2CBusRegisterSelector
        (JNIEnv *env, jclass I2CMasterDriver, jbyte i2cBus) {

    return i2cBus;
}

static inline void sendData (uint8_t slaveAddress, uint8_t dataToSendSize) {

    int volatile count = 0;

    *A = (uint8_t) slaveAddress;
    *DLEN = dataToSendSize;
    *S = I2C_S_CLEAR;
    *C = I2C_C_SEND;

    while (!(*S & I2C_S_DONE)) {
        while (count < dataToSendSize && *S & I2C_S_TXD) {
            *FIFO = writeBuffer[count++];
        }
    }
}

static inline I2C_STATUS sendDataWithException (uint8_t slaveAddress, uint8_t dataToSendSize) {

    int volatile count = 0;

    *A = (uint8_t) slaveAddress;
    *DLEN = dataToSendSize;
    *S = I2C_S_CLEAR;
    *C = I2C_C_SEND;

    while (!(*S & I2C_S_DONE)) {
        while (count < dataToSendSize && *S & I2C_S_TXD) {
            *FIFO = writeBuffer[count++];
        }
    }

    uint32_t volatile const status = *S;

    if (status & I2C_S_ERR) {
        return I2C_NO_ACKNOWLEDGE;
    } else if (status & I2C_S_CLKT) {
        return I2C_CLOCK_STRETCH_TIMEOUT;
    } else if (count < dataToSendSize) {
        return I2C_DATA_LOSS;
    } else {
        return I2C_SUCCESS;
    }

}

static inline void receiveData (uint8_t slaveAddress, uint8_t dataToReceiveSize) {

    int volatile count = 0;

    *A = (uint8_t) slaveAddress;
    *DLEN = dataToReceiveSize;
    *S = I2C_S_CLEAR;
    *C = I2C_C_RECEIVE;

    while (!(*S & I2C_S_DONE)) {
        while (count < dataToReceiveSize && *S & I2C_S_RXD) {
            readBuffer[count++] = (jint) (*FIFO & 0x000000ff);
        }
    }

}

static inline I2C_STATUS receiveDataWithException (uint8_t slaveAddress, uint8_t dataToReceiveSize) {

    int volatile count = 0;

    *A = (uint8_t) slaveAddress;
    *DLEN = dataToReceiveSize;
    *S = I2C_S_CLEAR;
    *C = I2C_C_RECEIVE;

    while (!(*S & I2C_S_DONE)) {
        while (count < dataToReceiveSize && *S & I2C_S_RXD) {
            readBuffer[count++] = (jint) (*FIFO & 0x000000ff);
        }
    }

    uint32_t volatile const status = *S;

    if (status & I2C_S_ERR) {
        return I2C_NO_ACKNOWLEDGE;
    } else if (status & I2C_S_CLKT) {
        return I2C_CLOCK_STRETCH_TIMEOUT;
    } else if (count < dataToReceiveSize) {
        return I2C_DATA_LOSS;
    } else {
        return I2C_SUCCESS;
    }

}

void JNICALL Java_com_comert_gEmbedded_device_nativeinterface_I2CMasterDriver_sendData
        (JNIEnv *env, jclass I2CMasterDriver, jbyte registerSelector, jbyte slaveAddress, jint dataToSendSize) {

    sendData (slaveAddress, dataToSendSize);

}

void JNICALL Java_com_comert_gEmbedded_device_nativeinterface_I2CMasterDriver_sendDataWithException
        (JNIEnv *env, jclass I2CMasterDriver, jbyte registerSelector, jbyte slaveAddress, jint dataToSendSize) {

    I2C_STATUS status = sendDataWithException (slaveAddress, dataToSendSize);

    if (status == I2C_NO_ACKNOWLEDGE) {
        throwANewDeviceIOException (env, "slave send ack error");
        return;
    } else if (status == I2C_CLOCK_STRETCH_TIMEOUT) {
        throwANewDeviceIOException (env, "slave send timeout error");
        return;
    } else if (status == I2C_DATA_LOSS) {
        throwANewDeviceIOException (env, "slave send data loss error");
        return;
    }

}

void JNICALL Java_com_comert_gEmbedded_device_nativeinterface_I2CMasterDriver_receiveData
        (JNIEnv *env, jclass I2CMasterDriver, jbyte registerSelector, jbyte slaveAddress, jint dataToReceiveSize) {

    receiveData (slaveAddress, dataToReceiveSize);

}

void JNICALL Java_com_comert_gEmbedded_device_nativeinterface_I2CMasterDriver_receiveDataWithException
        (JNIEnv *env, jclass I2CMasterDriver, jbyte registerSelector, jbyte slaveAddress, jint dataToReceiveSize) {

    I2C_STATUS status = receiveDataWithException (slaveAddress, dataToReceiveSize);

    if (status == I2C_NO_ACKNOWLEDGE) {
        throwANewDeviceIOException (env, "slave receive ack error");
        return;
    } else if (status == I2C_CLOCK_STRETCH_TIMEOUT) {
        throwANewDeviceIOException (env, "slave receive timeout error");
        return;
    } else if (status == I2C_DATA_LOSS) {
        throwANewDeviceIOException (env, "slave receive data loss error");
        return;
    }

}

void JNICALL Java_com_comert_gEmbedded_device_nativeinterface_I2CMasterDriver_sendAndReceiveData
        (JNIEnv *env, jclass I2CMasterDriver, jbyte registerSelector, jbyte slaveAddress, jint dataToSendSize,
         jint dataToReceiveSize) {

    sendData (slaveAddress, dataToSendSize);
    receiveData (slaveAddress, dataToReceiveSize);

}

void JNICALL Java_com_comert_gEmbedded_device_nativeinterface_I2CMasterDriver_sendAndReceiveDataWithException
        (JNIEnv *env, jclass I2CMasterDriver, jbyte registerSelector, jbyte slaveAddress, jint dataToSendSize,
         jint dataToReceiveSize) {

    I2C_STATUS status;

    status = sendDataWithException (slaveAddress, dataToSendSize);

    if (status == I2C_NO_ACKNOWLEDGE) {
        throwANewDeviceIOException (env, "slave send ack error");
        return;
    } else if (status == I2C_CLOCK_STRETCH_TIMEOUT) {
        throwANewDeviceIOException (env, "slave send timeout error");
        return;
    } else if (status == I2C_DATA_LOSS) {
        throwANewDeviceIOException (env, "slave send data loss error");
        return;
    }

    status = receiveDataWithException (slaveAddress, dataToReceiveSize);

    if (status == I2C_NO_ACKNOWLEDGE) {
        throwANewDeviceIOException (env, "slave receive ack error");
        return;
    } else if (status == I2C_CLOCK_STRETCH_TIMEOUT) {
        throwANewDeviceIOException (env, "slave receive timeout error");
        return;
    } else if (status == I2C_DATA_LOSS) {
        throwANewDeviceIOException (env, "slave receive data loss error");
        return;
    }

}