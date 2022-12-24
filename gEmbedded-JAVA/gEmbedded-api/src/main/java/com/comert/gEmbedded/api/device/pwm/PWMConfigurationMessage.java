package com.comert.gEmbedded.api.device.pwm;

import com.comert.gEmbedded.api.device.DeviceConfigurationMessage;

enum PWMConfigurationMessage implements DeviceConfigurationMessage {

    PIN_FIELD_IS_NOT_VALID("Pin field is not valid");

    PWMConfigurationMessage(String message) {
        this.message = message;
    }

    private final String message;

    @Override
    public String getMessage() {
        return message;
    }

}
