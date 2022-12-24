package com.comert.gEmbedded.device.nativeinterface;

import com.comert.gEmbedded.api.device.DeviceConfigurationMessage;

public enum ConfigurationMessage implements DeviceConfigurationMessage {

    PIN_IS_ALREADY_CONFIGURED("Pin is already configured"),

    I2C_BUS_IS_ALREADY_CONFIGURED("I2C bus is already configured");

    ConfigurationMessage(String message) {
        this.message = message;
    }

    private final String message;

    @Override
    public String getMessage() {
        return message;
    }

}
