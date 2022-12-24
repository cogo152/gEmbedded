package com.comert.gEmbedded.api.device.i2c;

import com.comert.gEmbedded.api.device.DeviceConfigurationMessage;

enum I2CBusConfigurationMessage implements DeviceConfigurationMessage {
    I2C_BUS_FIELD_IS_NOT_VALID("I2C bus field is not valid");

    I2CBusConfigurationMessage(String message) {
        this.message = message;
    }

    private final String message;

    @Override
    public String getMessage() {
        return message;
    }

}
