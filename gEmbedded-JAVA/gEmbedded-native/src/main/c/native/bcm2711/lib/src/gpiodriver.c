#include "com_comert_gEmbedded_device_nativeinterface_GPIODriver.h"
#include "gpiodriver.h"

#include "jniutil.h"
#include "devicedriver.h"

#include <unistd.h>
#include <linux/gpio.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <sys/poll.h>

#define GPFSEL_OFFSET           (0x00 / 4)
#define GPSET_OFFSET            (0x1c / 4)
#define GPCLR_OFFSET            (0x28 / 4)
#define GPLEV_OFFSET            (0x34 / 4)
#define GPPUD_OFFSET            (0xe4 / 4)
#define MAX_LISTENER_PIN_SIZE   (4)

typedef enum {
    PIN_SUPPORTED = 0,
    PIN_NOT_SUPPORTED = 1
} PIN_VALIDATION;

typedef enum {
    PULLUPDOWN_NO_RESISTOR = 0b00,
    PULLUPDOWN_PULL_UP = 0b01,
    PULLUPDOWN_PULL_DOWN = 0b10,
} PULLUPDOWN;

typedef enum {
    PULLUPDOWN_SUPPORTED = 0,
    PULLUPDOWN_NOT_SUPPORTED = 1
} PULLUPDOWN_VALIDATION;

typedef enum {
    PIN_EVENT_SYNCHRONOUS_FALLING = 0b00,
    PIN_EVENT_SYNCHRONOUS_RISING = 0b10,
    PIN_EVENT_SYNCHRONOUS_BOTH = 0b11,
} PIN_EVENT;

typedef enum {
    PIN_EVENT_SUPPORTED = 0,
    PIN_EVENT_NOT_SUPPORTED = 1
} PIN_EVENT_VALIDATION;

struct GPIOEvent {
    uint8_t _pin;
    uint8_t registerSelector;
    int timeoutInMilSec;
    struct pollfd pollFd;
    jobject listenerCallBack;
};

struct GPIOEvent gpioEvents[MAX_LISTENER_PIN_SIZE]; // malloc and free

uintptr_t static volatile *GPFSEL = NULL;
uintptr_t static volatile *GPSET = NULL;
uintptr_t static volatile *GPCLR = NULL;
uintptr_t static volatile *GPLEV = NULL;
uintptr_t static volatile *GPPUD = NULL;

PIN_VALIDATION static validatePin (uint8_t _pin);

PULLUPDOWN_VALIDATION static
validatePullUpDownAndConvert (uint8_t _pin, uint8_t _pullUpDown, uint8_t *convertedPullUpDown);

PIN_STATUS static configurePullUpDown (uint8_t _pin, uint8_t convertedPullUpDown);

PIN_EVENT_VALIDATION static validatePinEventAndConvert (uint8_t _pin, uint8_t _event, uint8_t *convertedEvent);

PIN_STATUS static configurePinEvent (uint8_t _pin, uint8_t convertedEvent, struct pollfd *pollFd);

jbyte static getIOPinRegisterSelector (uint8_t pin);

jint static getIOPinBitField (uint8_t pin);

jmethodID static onFalling = NULL;
jmethodID static onRising = NULL;
jmethodID static onTimeout = NULL;
jmethodID static onError = NULL;

void callListenerCallBackOnRising (JNIEnv *env, jobject listenerCallBack, jlong timeStamp) {

    (*env)->CallVoidMethod (env, listenerCallBack, onRising, timeStamp);
    if ((*env)->ExceptionCheck (env) == JNI_TRUE) {
        throwANewRuntimeException (env, "onFalling could not be called");
        return;
    }

}

void callListenerCallBackOnFalling (JNIEnv *env, jobject listenerCallBack, jlong timeStamp) {

    (*env)->CallVoidMethod (env, listenerCallBack, onFalling, timeStamp);
    if ((*env)->ExceptionCheck (env) == JNI_TRUE) {
        throwANewRuntimeException (env, "onFalling could not be called");
        return;
    }
}

void callListenerCallBackOnTimeout (JNIEnv *env, jobject listenerCallBack) {

    (*env)->CallVoidMethod (env, listenerCallBack, onTimeout);
    if ((*env)->ExceptionCheck (env) == JNI_TRUE) {
        throwANewRuntimeException (env, "onTimeout, could not be called");
    }
}

void callListenerCallBackOnError (JNIEnv *env, jobject listenerCallBack) {

    (*env)->CallVoidMethod (env, listenerCallBack, onError);
    if ((*env)->ExceptionCheck (env) == JNI_TRUE) {
        throwANewRuntimeException (env, "onError could not be called");
    }

}

void JNICALL Java_com_comert_gEmbedded_device_nativeinterface_GPIODriver_setupGPIODriver
        (JNIEnv *env, jclass GPIODriver) {

    uintptr_t *gpioBase = (uintptr_t *) requestGPIOOBase ();

    GPFSEL = gpioBase + GPFSEL_OFFSET;
    GPSET = gpioBase + GPSET_OFFSET;
    GPCLR = gpioBase + GPCLR_OFFSET;
    GPLEV = gpioBase + GPLEV_OFFSET;
    GPPUD = gpioBase + GPPUD_OFFSET;

    jclass ListenerCallBack = (*env)->FindClass (env, LISTENERCALLBACK_CLASS);
    if ((ListenerCallBack == NULL) || ((*env)->ExceptionCheck (env) == JNI_TRUE)) {
        throwANewRuntimeException (env,"XXX");
    }

    onRising = (*env)->GetMethodID (env, ListenerCallBack, ON_RISING_METHOD_NAME, ON_RISING_METHOD_SIGNATURE);
    if ((onRising == NULL) || ((*env)->ExceptionCheck (env) == JNI_TRUE)) {
        throwANewRuntimeException (env,"XXX");
    }

    onFalling = (*env)->GetMethodID (env, ListenerCallBack, ON_FALLING_METHOD_NAME, ON_FALLING_METHOD_SIGNATURE);
    if ((onFalling == NULL) || ((*env)->ExceptionCheck (env) == JNI_TRUE)) {
        throwANewRuntimeException (env,"XXX");
    }

    onTimeout = (*env)->GetMethodID (env, ListenerCallBack, ON_TIMEOUT_METHOD_NAME, ON_TIMEOUT_METHOD_SIGNATURE);
    if ((onTimeout == NULL) || ((*env)->ExceptionCheck (env) == JNI_TRUE)) {
        throwANewRuntimeException (env,"XXX");
    }

    onError = (*env)->GetMethodID (env, ListenerCallBack, ON_ERROR_METHOD_NAME, ON_ERROR_METHOD_SIGNATURE);
    if ((onError == NULL) || ((*env)->ExceptionCheck (env) == JNI_TRUE)) {
        throwANewRuntimeException (env,"XXX");
    }
}

void JNICALL Java_com_comert_gEmbedded_device_nativeinterface_GPIODriver_shutdownGPIODriver
        (JNIEnv *env, jclass GPIODriver) {

    // close files, delete global refs

}

void JNICALL Java_com_comert_gEmbedded_device_nativeinterface_GPIODriver_configureInputPin
        (JNIEnv *env, jclass GPIODriver, jobject pin, jobject pullUpDown) {

    JNI_STATUS jniStatusPin, jniStatusPullUpDown;
    jbyte _pin, _pullUpDown;

    jniStatusPin = getEnumDigit (env, pin, &_pin);
    jniStatusPullUpDown = getEnumDigit (env, pullUpDown, &_pullUpDown);
    if ((jniStatusPin != JNI_SUCCESS) || (jniStatusPullUpDown != JNI_SUCCESS)) {
        throwANewDeviceConfigurationException (env, "InputPin configuration failed");
        return;
    }

    PIN_VALIDATION pinValidation = validatePin (_pin);
    if (pinValidation != PIN_SUPPORTED) {
        throwANewDeviceConfigurationException (env, "Pin is not supported");
        return;
    }

    PIN_STATUS pinStatus;

    pinStatus = configurePinFunction (_pin, PIN_FUNCTION_INPUT);
    if (pinStatus != PIN_SUCCESS) {
        throwANewDeviceConfigurationException (env, "Pin function configuration failed");
        return;
    }


    uint8_t convertedPullUpDown;
    PULLUPDOWN_VALIDATION pullUpDownValidation = validatePullUpDownAndConvert (_pin, _pullUpDown, &convertedPullUpDown);
    if (pullUpDownValidation != PULLUPDOWN_SUPPORTED) {
        throwANewDeviceConfigurationException (env, "Pull-Up, Pull-Down is not supported");
        return;
    }

    pinStatus = configurePullUpDown (_pin, convertedPullUpDown);
    if (pinStatus != PIN_SUCCESS) {
        throwANewDeviceConfigurationException (env, "Pull-Up Pull-Down configuration failed");
        return;
    }


}

jbyte JNICALL Java_com_comert_gEmbedded_device_nativeinterface_GPIODriver_getInputPinRegisterSelector
        (JNIEnv *env, jclass GPIODriver, jbyte pin) {

    return getIOPinRegisterSelector (pin);

}


jint JNICALL Java_com_comert_gEmbedded_device_nativeinterface_GPIODriver_getInputPinBitField
        (JNIEnv *env, jclass GPIODriver, jbyte pin) {

    return getIOPinBitField (pin);

}

void JNICALL Java_com_comert_gEmbedded_device_nativeinterface_GPIODriver_configureListenerPin
        (JNIEnv *env, jclass GPIODriver, jobject pin, jobject event, jint timeoutInMilSec, jobject listenerCallBack) {

    static uint8_t counter = 0;

    if (counter == MAX_LISTENER_PIN_SIZE) {
        throwANewDeviceConfigurationException (env, "ListenerPin configuration failed. Thread size");
        return;
    }

    JNI_STATUS jniStatusPin, jniStatusEvent;
    jbyte _pin, _event;

    jniStatusPin = getEnumDigit (env, pin, &_pin);
    jniStatusEvent = getEnumDigit (env, event, &_event);
    if ((jniStatusPin != JNI_SUCCESS) || (jniStatusEvent != JNI_SUCCESS)) {
        throwANewDeviceConfigurationException (env, "ListenerPin configuration failed");
        return;
    }

    PIN_VALIDATION pinValidation = validatePin (_pin);
    if (pinValidation != PIN_SUPPORTED) {
        throwANewDeviceConfigurationException (env, "Pin is not supported");
        return;
    }

    uint8_t convertedEvent;
    PIN_EVENT_VALIDATION pinEventValidation = validatePinEventAndConvert (_pin, _event, &convertedEvent);
    if (pinEventValidation != PIN_EVENT_SUPPORTED) {
        throwANewDeviceConfigurationException (env, "Event is not supported");
        return;
    }

    struct pollfd pollFd;

    PIN_STATUS pinStatus;
    pinStatus = configurePinEvent (_pin, convertedEvent, &pollFd);
    if (pinStatus != PIN_SUCCESS) {
        throwANewDeviceConfigurationException (env, "Pin event configuration failed");
        return;
    }


    gpioEvents[counter]._pin = _pin;
    gpioEvents[counter].registerSelector = counter;
    gpioEvents[counter].timeoutInMilSec = timeoutInMilSec;
    gpioEvents[counter].pollFd = pollFd;
    gpioEvents[counter].listenerCallBack = (*env)->NewGlobalRef (env, listenerCallBack);

    counter++;

}

jbyte JNICALL Java_com_comert_gEmbedded_device_nativeinterface_GPIODriver_getListenerPinRegisterSelector
        (JNIEnv *env, jclass GPIODriver, jbyte pin) {

    jbyte registerSelector = 0;

    for (int i = 0; i < 4; ++i) {
        uint8_t _pin = gpioEvents[i]._pin;
        if (_pin == pin) {
            registerSelector = (jbyte) gpioEvents[i].registerSelector;
            break;
        }
    }

    return registerSelector;

}

void JNICALL Java_com_comert_gEmbedded_device_nativeinterface_GPIODriver_configureOutputPin
        (JNIEnv *env, jclass GPIODriver, jobject pin) {

    JNI_STATUS jniStatusPin;
    jbyte _pin;

    jniStatusPin = getEnumDigit (env, pin, &_pin);
    if (jniStatusPin != JNI_SUCCESS) {
        throwANewDeviceConfigurationException (env, "OutputPin configuration failed");
        return;
    }

    PIN_VALIDATION pinValidation = validatePin (_pin);
    if (pinValidation != PIN_SUPPORTED) {
        throwANewDeviceConfigurationException (env, "Pin is not supported");
        return;
    }


    PIN_STATUS pinStatus = configurePinFunction (_pin, PIN_FUNCTION_OUTPUT);
    if (pinStatus != PIN_SUCCESS) {
        throwANewDeviceConfigurationException (env, "Pin function configuration failed");
        return;
    }

}

jbyte JNICALL Java_com_comert_gEmbedded_device_nativeinterface_GPIODriver_getOutputPinRegisterSelector
        (JNIEnv *env, jclass GPIODriver, jbyte pin) {

    return getIOPinRegisterSelector (pin);

}

jint JNICALL Java_com_comert_gEmbedded_device_nativeinterface_GPIODriver_getOutputPinBitField
        (JNIEnv *env, jclass GPIODriver, jbyte pin) {

    return getIOPinBitField (pin);

}

jboolean JNICALL Java_com_comert_gEmbedded_device_nativeinterface_GPIODriver_isPinHigh
        (JNIEnv *env, jclass GPIODriver, jbyte registerSelector, jint bitField) {

    uint32_t register registerState = GPLEV[registerSelector];
    registerState &= bitField;

    return (registerState != 0) ? JNI_TRUE : JNI_FALSE;

}

jboolean JNICALL Java_com_comert_gEmbedded_device_nativeinterface_GPIODriver_isPinLow
        (JNIEnv *env, jclass GPIODriver, jbyte registerSelector, jint bitField) {

    uint32_t register registerState = GPLEV[registerSelector];
    registerState &= bitField;

    return (registerState == 0) ? JNI_TRUE : JNI_FALSE;

}

void JNICALL Java_com_comert_gEmbedded_device_nativeinterface_GPIODriver_setPinHigh
        (JNIEnv *env, jclass GPIODriver, jbyte registerSelector, jint bitField) {

    GPSET[registerSelector] = bitField;

}

void JNICALL Java_com_comert_gEmbedded_device_nativeinterface_GPIODriver_setPinHighWithException
        (JNIEnv *env, jclass GPIODriver, jbyte registerSelector, jint bitField) {

    GPSET[registerSelector] = bitField;

}

void JNICALL Java_com_comert_gEmbedded_device_nativeinterface_GPIODriver_setPinLow
        (JNIEnv *env, jclass GPIODriver, jbyte registerSelector, jint bitField) {

    GPCLR[registerSelector] = bitField;

}

void JNICALL Java_com_comert_gEmbedded_device_nativeinterface_GPIODriver_setPinLowWithException
        (JNIEnv *env, jclass GPIODriver, jbyte registerSelector, jint bitField) {

    GPCLR[registerSelector] = bitField;

}

void JNICALL Java_com_comert_gEmbedded_device_nativeinterface_GPIODriver_pollPin
        (JNIEnv *env, jclass GPIODriver, jbyte registerSelector) {

    struct gpioevent_data event;
    int rv;
    ssize_t rd;

    rv = poll (&gpioEvents[registerSelector].pollFd, 1, gpioEvents[registerSelector].timeoutInMilSec);

    switch (rv) {
        case -1: {
            callListenerCallBackOnError (env, gpioEvents[registerSelector].listenerCallBack);
            return;
        }
        case 0: {
            callListenerCallBackOnTimeout (env, gpioEvents[registerSelector].listenerCallBack);
            return;
        }
        default: {
            rd = read (gpioEvents[registerSelector].pollFd.fd, &event, sizeof (event));
            if (rd > 0) {
                jlong timeStamp = (jlong) event.timestamp;
                if (event.id == GPIOEVENT_REQUEST_RISING_EDGE) {
                    callListenerCallBackOnRising (env, gpioEvents[registerSelector].listenerCallBack, timeStamp);
                } else {
                    callListenerCallBackOnFalling (env, gpioEvents[registerSelector].listenerCallBack, timeStamp);
                }
            } else {
                callListenerCallBackOnError (env, gpioEvents[registerSelector].listenerCallBack);
            }
            return;
        }
    }

}


void JNICALL Java_com_comert_gEmbedded_device_nativeinterface_GPIODriver_releasePin
        (JNIEnv *env, jclass GPIODriver, jbyte registerSelector) {

    close (gpioEvents[registerSelector].pollFd.fd);
    (*env)->DeleteGlobalRef (env, gpioEvents[registerSelector].listenerCallBack);

}

PIN_VALIDATION static validatePin (uint8_t _pin) {
    if (_pin > 50) {
        return PIN_NOT_SUPPORTED;
    } else {
        return PIN_SUPPORTED;
    }
}

PIN_FUNCTION_VALIDATION
validatePinFunctionAndConvert (uint8_t _pin, uint8_t _pinFunction, uint8_t *convertedPinFunction) {

    switch (_pinFunction) {
        case 2: {
            *convertedPinFunction = PIN_FUNCTION_INPUT;
            return PIN_FUNCTION_SUPPORTED;
        }
        case 3: {
            *convertedPinFunction = PIN_FUNCTION_OUTPUT;
            return PIN_FUNCTION_SUPPORTED;
        }
        case 4: {
            *convertedPinFunction = PIN_FUNCTION_ALT_0;
            return PIN_FUNCTION_SUPPORTED;
        }
        case 5: {
            *convertedPinFunction = PIN_FUNCTION_ALT_1;
            return PIN_FUNCTION_SUPPORTED;
        }
        case 6: {
            *convertedPinFunction = PIN_FUNCTION_ALT_2;
            return PIN_FUNCTION_SUPPORTED;
        }
        case 7: {
            *convertedPinFunction = PIN_FUNCTION_ALT_3;
            return PIN_FUNCTION_SUPPORTED;
        }
        case 8: {
            *convertedPinFunction = PIN_FUNCTION_ALT_4;
            return PIN_FUNCTION_SUPPORTED;
        }
        case 9: {
            *convertedPinFunction = PIN_FUNCTION_ALT_5;
            return PIN_FUNCTION_SUPPORTED;
        }
        default: {
            return PIN_FUNCTION_NOT_SUPPORTED;
        }

    }

}

uint8_t static readPinFunction (uint8_t _pin) {

    uint8_t const registerSelector = _pin / 10;

    uint32_t registerLine = GPFSEL[registerSelector];
    uint32_t mask = (7 << ((_pin % 10) * 3));
    uint32_t pinFunction = registerLine & mask;
    pinFunction >>= ((_pin % 10) * 3);

    return pinFunction;

}

PIN_STATUS configurePinFunction (uint8_t _pin, uint8_t convertedPinFunction) {

    uint8_t const registerSelector = _pin / 10;

    GPFSEL[registerSelector] &= ~(7 << ((_pin % 10) * 3));
    GPFSEL[registerSelector] |= (convertedPinFunction << ((_pin % 10) * 3));

    if (convertedPinFunction == readPinFunction (_pin)) {
        return PIN_SUCCESS;
    } else {
        return PIN_ERROR;
    }

}

PULLUPDOWN_VALIDATION static
validatePullUpDownAndConvert (uint8_t _pin, uint8_t _pullUpDown, uint8_t *convertedPullUpDown) {

    switch (_pullUpDown) {
        case 0: {
            *convertedPullUpDown = PULLUPDOWN_NO_RESISTOR;
            return PULLUPDOWN_SUPPORTED;
        }
        case 1: {
            *convertedPullUpDown = PULLUPDOWN_PULL_UP;
            return PULLUPDOWN_SUPPORTED;
        }
        case 2: {
            *convertedPullUpDown = PULLUPDOWN_PULL_DOWN;
            return PULLUPDOWN_SUPPORTED;
        }
        default: {
            return PULLUPDOWN_NOT_SUPPORTED;
        }

    }

}

uint8_t static readPullUpDown (uint8_t _pin) {

    uint8_t const registerSelector = _pin / 16;

    uint32_t registerLine = GPPUD[registerSelector];
    uint32_t mask = (3 << ((_pin % 16) * 2));
    uint32_t pullUpDown = registerLine & mask;
    pullUpDown >>= ((_pin % 16) * 2);

    return pullUpDown;

}

PIN_STATUS static configurePullUpDown (uint8_t _pin, uint8_t convertedPullUpDown) {

    uint8_t const registerSelector = _pin / 16;

    GPPUD[registerSelector] &= ~(3 << ((_pin % 16) * 2));
    GPPUD[registerSelector] |= (convertedPullUpDown << ((_pin % 16) * 2));

    if (convertedPullUpDown == readPullUpDown (_pin)) {
        return PIN_SUCCESS;
    } else {
        return PIN_ERROR;
    }

}

PIN_EVENT_VALIDATION static validatePinEventAndConvert (uint8_t _pin, uint8_t _event, uint8_t *convertedEvent) {

    switch (_event) {
        case 0: {
            *convertedEvent = PIN_EVENT_SYNCHRONOUS_FALLING;
            return PIN_EVENT_SUPPORTED;
        }
        case 1: {
            *convertedEvent = PIN_EVENT_SYNCHRONOUS_RISING;
            return PIN_EVENT_SUPPORTED;
        }
        case 2: {
            *convertedEvent = PIN_EVENT_SYNCHRONOUS_BOTH;
            return PIN_EVENT_SUPPORTED;
        }
        default: {
            return PIN_EVENT_NOT_SUPPORTED;
        }
    }

}

// reserved for future
uint8_t static readPinEvent (uint8_t _pin) {

    return 0;

}

PIN_STATUS static configurePinEvent (uint8_t _pin, uint8_t convertedEvent, struct pollfd *pollFd) {

    int fileDescriptor = open ("/dev/gpiochip0", O_WRONLY);
    if (fileDescriptor < 0) {
        close (fileDescriptor);
        return PIN_ERROR;
    }

    struct gpioevent_request rq;

    rq.lineoffset = (__u32) _pin;
    rq.handleflags = GPIOHANDLE_REQUEST_INPUT;

    switch (convertedEvent) {
        case PIN_EVENT_SYNCHRONOUS_FALLING: {
            rq.eventflags = GPIOEVENT_REQUEST_FALLING_EDGE;
            break;
        }
        case PIN_EVENT_SYNCHRONOUS_RISING: {
            rq.eventflags = GPIOEVENT_REQUEST_RISING_EDGE;
            break;
        }
        default: {
            rq.eventflags = GPIOEVENT_REQUEST_BOTH_EDGES;
            break;
        }
    }

    /*
    char pinLabel[2];
    sprintf (pinLabel, "%d", _pin);
    strcpy (rq.consumer_label, pinLabel);
     */

    int result = ioctl (fileDescriptor, GPIO_GET_LINEEVENT_IOCTL, &rq);
    if (result < 0) {
        close (fileDescriptor);
        return PIN_ERROR;
    }

    close (fileDescriptor);

    pollFd->fd = rq.fd;
    pollFd->events = POLLIN | POLLPRI;

    return PIN_SUCCESS;

}

jbyte static getIOPinRegisterSelector (uint8_t pin) {

    return (jbyte) (pin / 32);

}

jint static getIOPinBitField (uint8_t pin) {

    return (1 << (pin % 32));

}