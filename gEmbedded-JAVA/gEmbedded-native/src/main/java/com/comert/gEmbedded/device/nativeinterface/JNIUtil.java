package com.comert.gEmbedded.device.nativeinterface;

abstract class JNIUtil {

    private JNIUtil() {

    }

    static native void setupJNIUtil() throws RuntimeException;

    static native void shutdownJNIUtil() throws RuntimeException;

}
