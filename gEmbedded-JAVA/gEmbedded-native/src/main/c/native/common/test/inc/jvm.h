#ifndef JVM_H
#define JVM_H

#include <jni.h>

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define JNI_VERSION                                 (JNI_VERSION_10)
#define GEMBEDDED_API_JAR_CLASSPATH                 ("-Djava.class.path=./../../common/test/rsrc/gEmbedded-api-2022.10.16-SNAPSHOT.jar")
#define GEMBEDDED_API_JAR_VALIDATION_EXAMPLE_CLASS  ("com/comert/gEmbedded/api/device/DeviceContext")

void createJVM (void);

void getJNIEnv (JNIEnv **);

void destroyJVM (void);

#endif
