#include "com_comert_gEmbedded_device_nativeinterface_PWMDriver.h"
#include "pwmdriver.h"

#include "jniutil.h"
#include "devicedriver.h"
#include "clockmanager.h"
#include "gpiodriver.h"

uintptr_t static volatile *CM_PWM_CTL = NULL;
uintptr_t static volatile *CM_PWM_DIV = NULL;

struct PWM_CTL_t static volatile *PWM_CTL = NULL;
uintptr_t volatile *PWM_STA = NULL;
uintptr_t volatile *PWM_DMAC = NULL;
uintptr_t volatile *PWM_RNG0 = NULL;
uintptr_t volatile *PWM_DAT0 = NULL;
uintptr_t volatile *PWM_FIF = NULL;
uintptr_t volatile *PWM_RNG1 = NULL;
uintptr_t volatile *PWM_DAT1 = NULL;

void JNICALL Java_com_comert_gEmbedded_device_nativeinterface_PWMDriver_setupPWMMDriver
        (JNIEnv *env, jclass PWMDriver) {

    uintptr_t *clockBase = (uintptr_t *) requestClockBase ();
    CM_PWM_CTL = clockBase + CM_PWM_CTL_OFFSET;
    CM_PWM_DIV = clockBase + CM_PWM_DIV_OFFSET;

    uintptr_t *pwmBase = (uintptr_t *) requestPWMBase ();

    PWM_CTL = (struct PWM_CTL_t *) (pwmBase + PWM_CTL_OFFSET);
    PWM_STA = pwmBase + PWM_STA_OFFSET;
    PWM_DMAC = pwmBase + PWM_DMAC_OFFSET;
    PWM_RNG0 = pwmBase + PWM_RNG0_OFFSET;
    PWM_DAT0 = pwmBase + PWM_DAT0_OFFSET;
    PWM_FIF = pwmBase + PWM_FIF_OFFSET;
    PWM_RNG1 = pwmBase + PWM_RNG1_OFFSET;
    PWM_DAT1 = pwmBase + PWM_DAT1_OFFSET;

    CLOCK_STATUS clockStatus;
    clockStatus = configureClock (CM_PWM_CTL, CM_PWM_DIV, 2500000);
    if (clockStatus != CLOCK_SUCCESS) {
        throwANewDeviceConfigurationException (env, "PWM clock configuration failed.");
        return;
    }

    clockStatus = enableClock (CM_PWM_CTL); // 1Mhz
    if (clockStatus != CLOCK_SUCCESS) {
        throwANewDeviceConfigurationException (env, "PWM clock enable failed.");
        return;
    }

}

void JNICALL Java_com_comert_gEmbedded_device_nativeinterface_PWMDriver_shutdownPWMDriver
        (JNIEnv *env, jclass PWMDriver) {

    CLOCK_STATUS clockStatus;

    clockStatus = disableClock (CM_PWM_CTL);
    if (clockStatus != CLOCK_SUCCESS) {
        throwANewDeviceConfigurationException (env, "PWM clock disable failed.");
        return;
    }

}

void JNICALL Java_com_comert_gEmbedded_device_nativeinterface_PWMDriver_configurePWMPin
        (JNIEnv *env, jclass PWMDriver, jobject pin, jobject pwmMode, jobject pwmPolarity, jobject pwmSilence,
         jint range) {

    JNI_STATUS jniStatusPin, jniStatusPWMMode, jniStatusPWMPolarity, jniStatusPWMSilence;
    jbyte _pin, _pwmMode, _pwmPolarity, _pwmSilence;

    jniStatusPin = getEnumDigit (env, pin, &_pin);
    if (jniStatusPin != JNI_SUCCESS) {
        throwANewDeviceConfigurationException (env, "PWM pin configuration failed");
        return;
    }

    jniStatusPWMMode = getEnumDigit (env, pwmMode, &_pwmMode);
    if (jniStatusPWMMode != JNI_SUCCESS) {
        throwANewDeviceConfigurationException (env, "PWM mode configuration failed");
        return;
    }

    jniStatusPWMPolarity = getEnumDigit (env, pwmPolarity, &_pwmPolarity);
    if (jniStatusPWMPolarity != JNI_SUCCESS) {
        throwANewDeviceConfigurationException (env, "PWM polarity configuration failed");
        return;
    }

    jniStatusPWMSilence = getEnumDigit (env, pwmSilence, &_pwmSilence);
    if (jniStatusPWMSilence != JNI_SUCCESS) {
        throwANewDeviceConfigurationException (env, "PWM silence configuration failed");
        return;
    }

    if (_pin == 18) {
        switch (_pwmMode) {
            case 0: {
                PWM_CTL->mode0 = PWM_MODE_PWM;
                PWM_CTL->msen0 = PWM_MSEN_DEFAULT;
                break;
            }
            case 1: {
                PWM_CTL->mode0 = PWM_MODE_PWM;
                PWM_CTL->msen0 = PWM_MSEN_MS;
                break;
            }
            case 2: {
                PWM_CTL->mode0 = PWM_MODE_SERIALIZER;
                break;
            }
            default: {
                throwANewDeviceConfigurationException (env, "PWM mode is not supported");
                return;
            }
        }

        switch (_pwmPolarity) {
            case 0: {
                PWM_CTL->pola0 = PWM_POLA_LOWHIGH;
                break;
            }
            case 1: {
                PWM_CTL->pola0 = PWM_POLA_HIGHLOW;
                break;
            }
            default: {
                throwANewDeviceConfigurationException (env, "PWM polarity is not supported");
                return;
            }
        }

        switch (_pwmSilence) {
            case 0: {
                PWM_CTL->sbit0 = PWM_SBIT_LOW;
                break;
            }
            case 1: {
                PWM_CTL->sbit0 = PWM_SBIT_HIGH;
                break;
            }
            default: {
                throwANewDeviceConfigurationException (env, "PWM silence is not supported");
                return;
            }
        }

        PWM_CTL->usef0 = PWM_USEF_DATA;

        *PWM_RNG0 = range;
        *PWM_DAT0 = 0;
        configurePinFunction (_pin, PIN_FUNCTION_ALT_5);

    } else if (_pin == 19) {

        switch (_pwmMode) {
            case 0: {
                PWM_CTL->mode1 = PWM_MODE_PWM;
                PWM_CTL->msen1 = PWM_MSEN_DEFAULT;
                break;
            }
            case 1: {
                PWM_CTL->mode1 = PWM_MODE_PWM;
                PWM_CTL->msen1 = PWM_MSEN_MS;
                break;
            }
            case 2: {
                PWM_CTL->mode1 = PWM_MODE_SERIALIZER;
                break;
            }
            default: {
                throwANewDeviceConfigurationException (env, "PWM mode is not supported");
                return;
            }
        }

        switch (_pwmPolarity) {
            case 0: {
                PWM_CTL->pola1 = PWM_POLA_LOWHIGH;
                break;
            }
            case 1: {
                PWM_CTL->pola1 = PWM_POLA_HIGHLOW;
                break;
            }
            default: {
                throwANewDeviceConfigurationException (env, "PWM polarity is not supported");
                return;
            }
        }

        switch (_pwmSilence) {
            case 0: {
                PWM_CTL->sbit1 = PWM_SBIT_LOW;
                break;
            }
            case 1: {
                PWM_CTL->sbit1 = PWM_SBIT_HIGH;
                break;
            }
            default: {
                throwANewDeviceConfigurationException (env, "PWM silence is not supported");
                return;
            }
        }

        PWM_CTL->usef1 = PWM_USEF_DATA;

        *PWM_RNG1 = range;
        *PWM_DAT1 = 0;
        configurePinFunction (_pin, PIN_FUNCTION_ALT_5);

    } else {
        throwANewDeviceConfigurationException (env, "Pwm pin is not supported");
        return;
    }

}

jbyte JNICALL Java_com_comert_gEmbedded_device_nativeinterface_PWMDriver_getPWMPinRegisterSelector
        (JNIEnv *env, jclass PWMDriver, jbyte pin) {

    if (pin == 18) {
        return 0;
    } else {
        return 1;
    }

}

void JNICALL Java_com_comert_gEmbedded_device_nativeinterface_PWMDriver_enablePWMPin
        (JNIEnv *env, jclass PWMDriver, jbyte registerSelector) {


    if (registerSelector == 0) {
        PWM_CTL->pwen0 = PWM_PWEN_ENABLE;
    } else {
        PWM_CTL->pwen1 = PWM_PWEN_ENABLE;
    }

}

void JNICALL Java_com_comert_gEmbedded_device_nativeinterface_PWMDriver_disablePWMPin
        (JNIEnv *env, jclass PWMDriver, jbyte registerSelector) {


    if (registerSelector == 0) {
        PWM_CTL->pwen0 = PWM_PWEN_DISABLE;
    } else {
        PWM_CTL->pwen1 = PWM_PWEN_DISABLE;
    }

}

void JNICALL Java_com_comert_gEmbedded_device_nativeinterface_PWMDriver_writePWMPinData
        (JNIEnv *env, jclass PWMDriver, jbyte registerSelector, jint data) {

    if (registerSelector == 0) {
        *PWM_DAT0 = data;
    } else {
        *PWM_DAT1 = data;
    }


}

void JNICALL Java_com_comert_gEmbedded_device_nativeinterface_PWMDriver_writePWMPinDataWithException
        (JNIEnv *env, jclass PWMDriver, jbyte registerSelector, jint data) {

    if (registerSelector == 0) {
        *PWM_DAT0 = data;
    } else {
        *PWM_DAT1 = data;
    }

}
