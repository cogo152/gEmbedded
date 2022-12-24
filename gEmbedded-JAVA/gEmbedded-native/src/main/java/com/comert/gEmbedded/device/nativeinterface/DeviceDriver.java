package com.comert.gEmbedded.device.nativeinterface;

import com.comert.gEmbedded.api.device.DeviceConfigurationException;

public abstract class DeviceDriver {

    private DeviceDriver() {

    }

    static native void setupDeviceDriver() throws DeviceConfigurationException;

    static native void shutdownDeviceDriver() throws DeviceConfigurationException;

    public static native String getDeviceName();


}
