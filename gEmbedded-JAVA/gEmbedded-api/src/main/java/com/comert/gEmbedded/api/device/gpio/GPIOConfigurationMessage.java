package com.comert.gEmbedded.api.device.gpio;

import com.comert.gEmbedded.api.device.DeviceConfigurationMessage;

enum GPIOConfigurationMessage implements DeviceConfigurationMessage {

    PIN_FIELD_IS_NOT_VALID("Pin field is not valid");

    GPIOConfigurationMessage(String message) {
        this.message = message;
    }

    private final String message;

    @Override
    public String getMessage() {
        return message;
    }

}
