package com.comert.gEmbedded.api.util;

public enum InstanceExceptionMessage implements InstanceMessage {

    ARGUMENT_INVALID("Argument is invalid"),
    OUT_OF_DESIRED_CLASS("Instance is not created. You must create it in the Factory");

    InstanceExceptionMessage(String message) {
        this.message = message;
    }

    private final String message;

    @Override
    public String getMessage() {
        return message;
    }

}