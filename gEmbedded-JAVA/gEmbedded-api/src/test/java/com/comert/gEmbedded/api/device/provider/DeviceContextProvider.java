package com.comert.gEmbedded.api.device.provider;

import com.comert.gEmbedded.api.device.DeviceConfigurationException;
import org.junit.jupiter.api.Disabled;

@Disabled
public class DeviceContextProvider extends DeviceContextProviderParent {

    public DeviceContextProvider(){}


    @Override
    protected void _setupDevice() throws DeviceConfigurationException {
    }

    @Override
    protected void _shutdownDevice() throws DeviceConfigurationException {
    }

    @Override
    protected String getDeviceName() {
        return "Raspberrypi-4B";
    }

}
