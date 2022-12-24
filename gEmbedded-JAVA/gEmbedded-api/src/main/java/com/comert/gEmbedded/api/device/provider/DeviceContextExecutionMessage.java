package com.comert.gEmbedded.api.device.provider;

import com.comert.gEmbedded.api.device.DeviceExecutionMessage;

 enum DeviceContextExecutionMessage implements DeviceExecutionMessage {

    ALREADY_SETUP("Device is already set up"),

    ALREADY_SHUTDOWN("Device is already shut down"),

    MUST_BE_SETUP("Device must be set up");


    DeviceContextExecutionMessage(String message) {
        this.message = message;
    }

    private final String message;

    @Override
    public String getMessage() {
        return message;
    }

}
