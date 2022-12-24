package com.comert.gEmbedded.api.util;

public enum ProviderExceptionMessage implements ProviderMessage {

    ARGUMENT_INVALID("Argument is invalid"),

    NOT_IN_IMPL_PACKAGE("Provider could not be found in the implementation package"),

    NOT_A_SUBCLASS("Provider does not implement parent class"),

    NO_PUBLIC_DEFAULT_CONSTRUCTOR("Provider does not have a default constructor"),

    COULD_NOT_BE_CONSTRUCTED("Provider could not be constructed");

    ProviderExceptionMessage(String message) {
        this.message = message;
    }

    private final String message;

    @Override
    public String getMessage() {
        return message;
    }

}
