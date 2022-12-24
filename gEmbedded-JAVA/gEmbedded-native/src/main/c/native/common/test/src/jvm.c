#include "jvm.h"

JavaVM static *javaVm = NULL;
JNIEnv static *jniEnv = NULL;

void createJVM (void) {

    JavaVMInitArgs javaVmInitArgs;
    JavaVMOption javaVmOption[1];

    javaVmOption[0].optionString = GEMBEDDED_API_JAR_CLASSPATH;

    javaVmInitArgs.version = JNI_VERSION;
    javaVmInitArgs.options = javaVmOption;
    javaVmInitArgs.nOptions = 1;
    javaVmInitArgs.ignoreUnrecognized = JNI_FALSE;

    jint jvmCreated = JNI_CreateJavaVM (&javaVm, (void **) &jniEnv, &javaVmInitArgs);
    if (jvmCreated != JNI_OK) {
        printf ("FATAL ERROR file::jvm.c, function::createJVM(), message::JVM creation failed, error code::%d\n",
                jvmCreated);
        exit (EXIT_FAILURE);
    }

    if (jniEnv == NULL) {
        printf ("FATAL ERROR file::jvm.c, function::createJVM(), message::NULL jniEnv\n");
        exit (EXIT_FAILURE);
    } else {
        jint jniVersion = (*jniEnv)->GetVersion (jniEnv);
        if (jniVersion != JNI_VERSION) {
            printf ("FATAL ERROR file::jvm.c, function::createJVM(), message::invalid jniEnv\n");
            exit (EXIT_FAILURE);
        }
    }

    jclass const DeviceContextClass = (*jniEnv)->FindClass (jniEnv, GEMBEDDED_API_JAR_VALIDATION_EXAMPLE_CLASS);
    if ((DeviceContextClass == NULL) || ((*jniEnv)->ExceptionCheck (jniEnv) == JNI_TRUE)) {
        if ((*jniEnv)->ExceptionCheck (jniEnv) == JNI_TRUE) {
            (*jniEnv)->ExceptionDescribe (jniEnv);
            (*jniEnv)->ExceptionClear (jniEnv);
        }
        printf ("FATAL ERROR file::jvm.c, function::createJVM(), message::invalid gEmbedded-api-XXX.jar or validation example class\n");
        exit (EXIT_FAILURE);
    }

    printf ("JVM is successfully created\n");

}

void getJNIEnv (JNIEnv **pJniEnv) {

    if (pJniEnv == NULL) {
        printf ("FATAL ERROR file::jvm.c, function::getJNIEnv(JNIEnv **pJniEnv), message::NULL pJniEnv\n");
        exit (EXIT_FAILURE);
    }

    *pJniEnv = jniEnv;

}


void destroyJVM () {

    if (javaVm == NULL) {
        printf ("FATAL ERROR file::jvm.c, function::destroyJVM(), message::NULL javaVm\n");
        exit (EXIT_FAILURE);
    } else {
        jint jvmDestroyed = (*javaVm)->DestroyJavaVM (javaVm);
        if (jvmDestroyed != JNI_OK) {
            printf ("FATAL ERROR file::jvm.c, function::destroyJVM(), message::JVM removal failed, error code::%d\n",
                    jvmDestroyed);
            exit (EXIT_FAILURE);
        }
    }

    printf ("JVM is successfully destroyed\n");

}