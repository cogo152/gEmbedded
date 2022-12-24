package com.comert.gEmbedded.api.device.provider;

import com.comert.gEmbedded.api.device.DeviceConfigurationException;

public class TestExceptionFactory {

    public static void throwANewDeviceConfigurationException() throws DeviceConfigurationException {
        throw new DeviceConfigurationException(TestDeviceExceptionMessage.TEST_CONFIGURATION, "Test");
    }

}
